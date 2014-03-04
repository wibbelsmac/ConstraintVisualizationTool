#include "EditorBackEnd.h"
#include <sstream>
#include <iostream>
#include <fstream>


int loading = 0;
int            changed = 0;
char           filename[256] = "";
char           title[256] = "";
Fl_Text_Buffer *textbuf = 0;
Fl_Text_Buffer *report_textbuf = 0;
ConstrEditorUI *edui; 
static FILE* _readPipeFile;
static FILE* _writePipeFile;
static char* _setupFile;

void init (int argc, char **argv) {
  textbuf = new Fl_Text_Buffer(1024, 128);
  report_textbuf = new Fl_Text_Buffer(1024, 128);
  //fl_alert("Argument Count %d with", argc);
  if(argc > 1) {
    load_file(argv[1], 0);
	//Load in setup tcl script
    if(argc == 2)
    {
	_setupFile = argv[2];
    }
    
  }
  edui = new ConstrEditorUI;
  //textbuf->add_modify_callback(myCallback, NULL);
  edui->editor->buffer(textbuf);
  edui->editor->add_key_binding(114, FL_CTRL,my_key_fun); // code for ctrl + R
  edui->editor->setClickHandler(&report_handler);
  edui->constr_output->buffer(report_textbuf);
  //Initial global objects.
  edui->fileWindow->label("Mac and Willies DC Puppet");
  edui->outputWindow->label("Mac and Willies DC Puppet");  
  edui->find_box->when(FL_WHEN_CHANGED);
  Fl::visual(FL_DOUBLE|FL_INDEX);
  edui->show(argc, argv);

  
}

void addPipeFiles(FILE* readPipeFile, FILE* writePipeFile)
{
	_readPipeFile = readPipeFile;
	_writePipeFile = writePipeFile;
}

std::string SendShellCommand(const char* command, int commandCount)
{
	char buf [300];
	int first = 0;
	std::string resultString;
	if(strstr(command, "#"))
	   return "You clicked on a comment constraint";
	else if(strstr(command, ">>"))
	   return "You clicked on a output to file line";
	fprintf(_writePipeFile, "%s", command);
	fflush(_writePipeFile);
	fprintf(_writePipeFile, ".\n");
	fflush(_writePipeFile);
	
	
	while(fgets(buf, 1024, _readPipeFile))
	{	
		if(strstr(buf, "pt_shell>") && !first)
		{
			strncpy(buf, buf+10, strlen(buf));
			resultString += buf;
			commandCount--;
			printf("Count =%d", commandCount);
			if(commandCount == 0)
				first = 1;
			
		}
		else if(strstr(buf, "pt_shell>") && first)
		{
			first = 0;
			break;
		}
		else
		{
			resultString += buf;
		}	
		std::cout << buf;
	}
	return resultString;
}

void load_file(char *newfile, int ipos) {
  loading = 1;
  int insert = (ipos != -1);
  changed = insert;
  if (!insert) strcpy(filename, "");
  int r;
  if (!insert) {
      r = textbuf->loadfile(newfile);
  } else {
    r = textbuf->insertfile(newfile, ipos);
    // std::ifstream is (newfile, std::ifstream::binary);
    // if (is) {
    //   constr_file_text = std::string(is.beg, is.end);
    // }
    
  }
  if (r) {
    fl_alert("Error reading from file \'%s\':\n%s.", newfile, strerror(r));
  } else if (!insert) {
    strcpy(filename, newfile);
  }
  loading = 0;
  textbuf->call_modify_callbacks();
}

void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
  if ((nInserted || nDeleted) && !loading) changed = 1;
  ConstrEditorUI *w = (ConstrEditorUI *)v;
  set_title(w->fileWindow);
  if (loading) 
    w->editor->show_insert_position();
}

void open_cstr_cb(Fl_Widget*, void*) {
  if (!check_save()) return;

  char *newfile = fl_file_chooser("Open File?", "*", filename);
  if (newfile != NULL) load_file(newfile, -1);
}

void open_tcl_cb(Fl_Widget*, void*) {
  std::cout << "Not implemented";
}

void paste_cb(Fl_Widget*, void* v) {
  ConstrEditorUI* e = (ConstrEditorUI*)v;
  Fl_Text_Editor::kf_paste(0, e->editor);
}

void quit_cb(Fl_Widget*, void* v) {
  if (changed && !check_save())
    return;
  exit(0);
}
int check_save(void) {
  if (!changed) return 1;

  int r = fl_choice("The current file has not been saved.\n"
                    "Would you like to save it now?",
                    "Cancel", "Save", "Discard");

  if (r == 1) {
    save_cb(); // Save the file...
    return !changed;
  }

  return (r == 2) ? 1 : 0;
}

void set_title(Fl_Window* w) {
  if (filename[0] == '\0') strcpy(title, "Untitled");
  else {
    char *slash;
    slash = strrchr(filename, '/');
#ifdef WIN32
    if (slash == NULL) slash = strrchr(filename, '\\');
#endif
    if (slash != NULL) strcpy(title, slash + 1);
    else strcpy(title, filename);
  }

  if (changed) strcat(title, " (modified)");

  w->label(title);
}

void save_cb(void) {
  if (filename[0] == '\0') {
    // No filename - get one!
    saveas_cb();
    return;
  }
  else save_file(filename);
}
void save_file(char *newfile) {
  int errno;
  if ((errno = textbuf->savefile(newfile)))
    fl_alert("Error writing to file \'%s\':\n%s.", newfile, strerror(errno));
  else
    strcpy(filename, newfile);
  changed = 0;
  textbuf->call_modify_callbacks();
}
void saveas_cb(void) {
  char *newfile;

  newfile = fl_file_chooser("Save File As?", "*", filename);
  if (newfile != NULL) save_file(newfile);
}
void search_box_callback(Fl_Widget *, void *) {

  std::cout << "in callback" << std::endl;
  for(int i = 0; i <= textbuf->length(); i++) {
    char* line_text = textbuf->line_text(i);
    
    if(strstr(line_text, edui->find_box->value())) {
      std::cout << "line Text: " << line_text << std::endl;  
    } else {
      textbuf->skip_displayed_characters(i, strlen(line_text));
      textbuf->call_modify_callbacks ();
    }
    i += strlen(line_text) + 1;
  }
}

void myCallback(int pos, int nInserted, int nDeleted,
      int nRestyled, const char* deletedText,
      void* cbArg) {
  //if(edui->editor->event_clicks() != 0) {
    int linenum = textbuf->count_lines(0, pos);
    std::cout << "NEW Selection on line %d" << linenum << "\n";
   // std::cout << "Key Pressed" <<Fl::event_key();
  //}
}
int my_key_fun (int key, Fl_Text_Editor *editor) {
  return 1;
}

void add_cstr_cb(Fl_Widget *add_butt, void *data) {
  // if(edui->constr_add_window->minORmax == 1) {
  //   std:: cout << "setmaxdelay -from" << edui->from_pin_box->value() << " -to " << edui->to_pin_box->value() << "\n";
  // } else {
  //   std:: cout << "setmindelay -from" << edui->from_pin_box->value() << " -to " << edui->to_pin_box->value() << "\n";
  // }
  std::cout << "NOT FULLy IMPLEMENTED";
}
int report_handler(std::string selection){

    //remove comment lines
    
    std::istringstream iss;
    iss.str(selection);
    std::string line;
    std::string commandString = "";
    int commandCount = 0;
    while(std::getline(iss, line))
    {
	if(line.find("#") == std::string::npos && line != "")
	{
		commandString += line;
		commandString += "\n";
		commandCount++;
	}
    }
    if(commandString == "")
    {
	commandString = "#";
    }
    //integrated with pt_shell
    std::string report_text_str = SendShellCommand(commandString.c_str(), commandCount);
    report_textbuf->text(report_text_str.c_str());
  return 0;
}


