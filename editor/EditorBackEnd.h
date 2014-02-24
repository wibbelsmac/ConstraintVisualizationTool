#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#ifndef EditorBackEnd_h
#define EditorBackEnd_h

#include <FL/Fl.h>
#include <FL/x.h>
#include "editorgui.h"
#include <FL/fl_ask.H>
#include <FL/Fl_Text_Editor.h>
#include <FL/Fl_File_Chooser.H>

	
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

#endif