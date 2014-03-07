// generated by Fast Light User Interface Designer (fluid) version 1.0109

#include "EditorGui.h"

void ConstrEditorUI::cb_Save_i(Fl_Menu_*, void*) {
  save_cb();
}
void ConstrEditorUI::cb_Save(Fl_Menu_* o, void* v) {
  ((ConstrEditorUI*)(o->parent()->user_data()))->cb_Save_i(o,v);
}

void ConstrEditorUI::cb_SaveAs_i(Fl_Menu_*, void*) {
  saveas_cb();
}
void ConstrEditorUI::cb_SaveAs(Fl_Menu_* o, void* v) {
  ((ConstrEditorUI*)(o->parent()->user_data()))->cb_SaveAs_i(o,v);
}

Fl_Menu_Item ConstrEditorUI::menu_menuBar[] = {
 {"File", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {"Open .cstr", 0,  (Fl_Callback*)open_cstr_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Open .tcl", 0,  (Fl_Callback*)open_tcl_cb, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"Save", 0,  (Fl_Callback*)ConstrEditorUI::cb_Save, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {"SaveAs", 0,  (Fl_Callback*)ConstrEditorUI::cb_SaveAs, 0, 0, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Help", 0,  0, 0, 64, FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

ConstrEditorUI::ConstrEditorUI() {
  { fileWindow = new Fl_Double_Window(740, 775);
    fileWindow->labelfont(4);
    fileWindow->user_data((void*)(this));
    { editor = new ConstrTextEditor(20, 60, 710, 645);
      editor->box(FL_DOWN_FRAME);
      editor->color((Fl_Color)34);
      editor->selection_color(FL_SELECTION_COLOR);
      editor->labeltype(FL_NORMAL_LABEL);
      editor->labelfont(4);
      editor->labelsize(14);
      editor->labelcolor(FL_FOREGROUND_COLOR);
      editor->textfont(4);
      editor->textcolor(71);
      editor->align(FL_ALIGN_TOP);
      editor->when(FL_WHEN_RELEASE);
    } // ConstrTextEditor* editor
    { find_box = new Fl_Input(355, 26, 290, 24, "Filter:");
      find_box->callback((Fl_Callback*)search_box_callback);
    } // Fl_Input* find_box
    { Fl_Button* o = new Fl_Button(655, 30, 63, 20, "Clear");
      o->callback((Fl_Callback*)clear_cb);
    } // Fl_Button* o
    { menuBar = new Fl_Menu_Bar(0, 0, 740, 20, "menuBar");
      menuBar->menu(menu_menuBar);
    } // Fl_Menu_Bar* menuBar
    { pt_shell_input = new PTShell_Input(20, 715, 715, 60);
      pt_shell_input->box(FL_DOWN_FRAME);
      pt_shell_input->color(FL_BACKGROUND2_COLOR);
      pt_shell_input->selection_color(FL_SELECTION_COLOR);
      pt_shell_input->labeltype(FL_NORMAL_LABEL);
      pt_shell_input->labelfont(0);
      pt_shell_input->labelsize(14);
      pt_shell_input->labelcolor(FL_FOREGROUND_COLOR);
      pt_shell_input->align(FL_ALIGN_TOP);
      pt_shell_input->when(FL_WHEN_RELEASE);
    } // PTShell_Input* pt_shell_input
    fileWindow->end();
  } // Fl_Double_Window* fileWindow
  { outputWindow = new Fl_Double_Window(535, 775);
    outputWindow->labelfont(4);
    outputWindow->user_data((void*)(this));
    { constr_output = new Fl_Text_Display(15, 5, 510, 845);
      constr_output->labelfont(4);
      constr_output->textfont(5);
      Fl_Group::current()->resizable(constr_output);
      constr_output->window()->hotspot(constr_output);
    } // Fl_Text_Display* constr_output
    outputWindow->end();
  } // Fl_Double_Window* outputWindow
}

void ConstrEditorUI::show(int argc, char **argv) {
  fileWindow->show(argc, argv);
outputWindow->show(argc, argv);
}
