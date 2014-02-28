#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifndef EditorBackEnd_h
#define EditorBackEnd_h

#include <FL/Fl.H>
#include <FL/x.H>
#include "EditorGui.h"
#include <FL/fl_ask.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_File_Chooser.H>
#include <string>

	
void load_file(char *newfile, int ipos);
void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v);
void open_cb(Fl_Widget*, void*);
void paste_cb(Fl_Widget*, void* v);
void quit_cb(Fl_Widget*, void* v);
int check_save(void);
void set_title(Fl_Window* w);
void save_cb(void);
void save_file(char *newfile);
void saveas_cb(void);
void init (int argc, char **argv);
void myCallback(int pos, int nInserted, int nDeleted,
      int nRestyled, const char* deletedText,
      void* cbArg);
int my_key_fun (int key, Fl_Text_Editor *editor);
void add_cstr_cb(Fl_Widget *add_butt, void *data);
void open_cstr_cb(Fl_Widget*, void*);
void open_tcl_cb(Fl_Widget*, void*);
int clck_handler (int event);
int report_handler(std::string selection);

#endif
