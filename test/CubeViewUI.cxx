// generated by Fast Light User Interface Designer (fluid) version 1.0302

#include "CubeViewUI.h"

CubeViewUI::CubeViewUI() {
  { myWindow = new Fl_Double_Window(777, 395, "myWindow");
    myWindow->user_data((void*)(this));
    { Fl_Roller* o = new Fl_Roller(130, 255, 105, 15, "hrot");
      o->type(1);
    } // Fl_Roller* o
    { new Fl_Roller(0, 65, 15, 145, "vrot");
    } // Fl_Roller* o
    { Fl_Slider* o = new Fl_Slider(90, 235, 185, 20, "xpan");
      o->type(1);
    } // Fl_Slider* o
    { new Fl_Slider(15, 45, 20, 200, "vpan");
    } // Fl_Slider* o
    { Fl_Value_Slider* o = new Fl_Value_Slider(50, 0, 235, 20, "zoom");
      o->type(1);
      o->textsize(14);
    } // Fl_Value_Slider* o
    { new Fl_Box(35, 19, 280, 196, "cframe");
    } // Fl_Box* o
    { Fl_Group* o = new Fl_Group(25, 25, 15, 15);
      o->end();
    } // Fl_Group* o
    { cube = new CubeView(40, 39, 255, 192, "This is the cube_view");
      cube->box(FL_NO_BOX);
      cube->color(FL_BACKGROUND_COLOR);
      cube->selection_color(FL_BACKGROUND_COLOR);
      cube->labeltype(FL_NORMAL_LABEL);
      cube->labelfont(0);
      cube->labelsize(14);
      cube->labelcolor(FL_FOREGROUND_COLOR);
      cube->align(Fl_Align(FL_ALIGN_CENTER));
      cube->when(FL_WHEN_RELEASE);
    } // CubeView* cube
    myWindow->end();
    myWindow->resizable(myWindow);
  } // Fl_Double_Window* myWindow
}

void CubeViewUI::show(int argc, char **argv) {
  myWindow->show(argc, argv);
}
