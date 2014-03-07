#ifndef Constr_Text_Editor_H
#define Constr_Text_Editor_H

#include <FL/Fl_Text_Editor.H>
#include <string>

typedef int(* Constr_Report_Handler)(std::string selection);


class ConstrTextEditor : public Fl_Text_Editor {
public:
	ConstrTextEditor(int X, int Y, int W, int H, const char* l = 0);
	void setClickHandler(Constr_Report_Handler h);
	void Editable(bool);
	void Editable();
	void filter_text(std::string filter_string);
	bool filter_set();
	void clear_filter();
private:
	virtual int handle(int e);
	Constr_Report_Handler report_handler;
	Fl_Text_Buffer *filterBuffer;
	Fl_Text_Buffer *orig_buffer;
	bool editable;
	std::string filter_string;
};

#endif