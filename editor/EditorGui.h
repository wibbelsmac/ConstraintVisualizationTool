// generated by Fast Light User Interface Designer (fluid) version 1.0302

#ifndef EditorGui_h
#define EditorGui_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "EditorBackEnd.h"
#include "Constr_Text_Editor.h"
#include "PTShellInput.h"
#include <FL/Fl_Input.H>
extern void search_box_callback(Fl_Input*, void*);
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
extern void open_cstr_cb(Fl_Menu_*, void*);
extern void open_tcl_cb(Fl_Menu_*, void*);
#include <FL/Fl_Text_Display.H>
extern void add_cstr_cb(Fl_Button*, void*);
#include <FL/Fl_Browser.H>

class ConstrEditorUI {
public:
  ConstrEditorUI();
  Fl_Double_Window *fileWindow;
  ConstrTextEditor *editor;
  Fl_Input *find_box;
  Fl_Menu_Bar *menuBar;
  static Fl_Menu_Item menu_menuBar[];
private:
  inline void cb_Save_i(Fl_Menu_*, void*);
  static void cb_Save(Fl_Menu_*, void*);
  inline void cb_SaveAs_i(Fl_Menu_*, void*);
  static void cb_SaveAs(Fl_Menu_*, void*);
public:
  Fl_Double_Window *outputWindow;
  Fl_Text_Display *constr_output;
  Fl_Double_Window *constr_add_window;
  Fl_Input *from_pin_box;
  Fl_Input *to_pin_box;
  Fl_Input *delay_box;
  Fl_Browser *output_browser;
  void show(int argc, char **argv);
};
#endif
