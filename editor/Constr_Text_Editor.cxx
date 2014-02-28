#include "Constr_Text_Editor.h"
#include <iostream>
#include <FL/Fl.H>



ConstrTextEditor::ConstrTextEditor(int X, int Y, int W, int H, const char* l)
: Fl_Text_Editor(X,Y,W,H, l) {
	report_handler = 0;
}


void ConstrTextEditor::setClickHandler(Constr_Report_Handler h) {
	report_handler = h;
}

int ConstrTextEditor::handle(int e) {
	int return_val =  Fl_Text_Editor::handle(e);
	char* text = NULL;
	if(e == FL_RELEASE && Fl::event_button() == FL_RIGHT_MOUSE) {
		Fl_Text_Buffer* temp_buf = Fl_Text_Editor::buffer();
		if(temp_buf->selected()) {
			text = temp_buf->highlight_text();
		} else {
			text = temp_buf->line_text(Fl_Text_Editor::insert_position());
			int start = temp_buf->line_start(Fl_Text_Editor::insert_position());
			int end = temp_buf->line_end(Fl_Text_Editor::insert_position());
			temp_buf->highlight(start, end);
			temp_buf->call_modify_callbacks();
			std::cout << "Start: " << start << " End: " << end << "\n";
		}
	}

	if(report_handler != NULL && text != NULL){
		std::string temp_str(text);
		std::cout << "Sending: " << temp_str << "\n";
		(*report_handler)(temp_str);
	}
	return return_val;
}
