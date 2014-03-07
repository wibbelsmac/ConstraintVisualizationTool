#include "Constr_Text_Editor.h"
#include <iostream>
#include <FL/Fl.H>



ConstrTextEditor::ConstrTextEditor(int X, int Y, int W, int H, const char* l)
: Fl_Text_Editor(X,Y,W,H, l) {
	report_handler = 0;
	editable = true;
	filterBuffer = new Fl_Text_Buffer(1024, 128);
}


void ConstrTextEditor::setClickHandler(Constr_Report_Handler h) {
	report_handler = h;
}

int ConstrTextEditor::handle(int e) {
	if(!editable && ((e == FL_KEYDOWN) ||
					(e == FL_PASTE))) {
		return 0;
	}
		
	static int select_start = -1;
	int return_val =  Fl_Text_Editor::handle(e);
	char* text = NULL;
	if(e == FL_PUSH && Fl::event_button() == FL_RIGHT_MOUSE) {
		select_start = Fl_Text_Editor::insert_position();
	} else if(e == FL_RELEASE && Fl::event_button() == FL_RIGHT_MOUSE) {
		int select_end = Fl_Text_Editor::insert_position();
		Fl_Text_Buffer* temp_buf = Fl_Text_Editor::buffer();
		const Fl_Text_Selection* temp_select = temp_buf->highlight_selection();
		if(select_start != -1 && select_start != select_end ) { // if drag event detected
			if(select_start < select_end) {
				select_start = temp_buf->line_start(select_start);
				select_end = temp_buf->line_end(select_end);
			} else {
				int select_temp = select_start;
				select_start = temp_buf->line_start(select_end);
				select_end = temp_buf->line_end(select_temp);
			}

			std::cout << "temp_select Start: " << select_start << " temp_select End: " << select_end << "\n";
			text = temp_buf->text_range(select_start, select_end);
			std::cout << "Highligt: " << text << "\n";
			temp_buf->highlight(select_start, select_end);
		} else { // if single right click and no drag
			text = temp_buf->line_text(Fl_Text_Editor::insert_position());
			int start = temp_buf->line_start(Fl_Text_Editor::insert_position());
			int end = temp_buf->line_end(Fl_Text_Editor::insert_position());
			temp_buf->highlight(start, end);
			temp_buf->call_modify_callbacks();
			std::cout << "Start: " << start << " End: " << end << "\n";
		}
			select_start = -1;
	}

	if(report_handler != NULL && text != NULL){
		std::string temp_str(text);
		std::cout << "Sending: " << temp_str << "\n";
		(*report_handler)(temp_str);
	}
	return return_val;
}

void ConstrTextEditor::Editable(bool b){
	editable = b;
}
bool ConstrTextEditor::Editable() {
	return editable;
}

void ConstrTextEditor::filter_text(std::string filter_box_string) {
  
  std::cout << "in callback" << std::endl;

  if(filter_set() == false) {
  		std::cout << "New Filter" << std::endl;
		orig_buffer = Fl_Text_Editor::buffer();
  } else {
  	std::cout << "Modified Filter" << std::endl;
  	filterBuffer->text("");
  }
  for(int i = 0; i <= orig_buffer->length(); i++) {
    char* line_text = orig_buffer->line_text(i);
    if(strstr(line_text, filter_box_string.c_str())) {
      filterBuffer->append(line_text);
      filterBuffer->append("\n");
      std::cout << "Line: " << line_text << std::endl;
    } else {
  	}
    i += strlen(line_text) + 1;
  }
  Fl_Text_Editor::buffer(filterBuffer);
  editable = false;
  std::cout << "buffer" << filterBuffer->text() << std::endl;
}

bool ConstrTextEditor::filter_set() {
	return !editable;
}
void ConstrTextEditor::clear_filter() {
	if(orig_buffer != NULL)
		Fl_Text_Editor::buffer(orig_buffer);
	editable = true;
}

