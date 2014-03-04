#ifndef PT_SHELL_INPUT_H
#define PT_SHELL_INPUT_H

#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Editor.H>
#include <string>

typedef int(* Pt_shell_exec_cb)(std::string command);


class PTShell_Input : public Fl_Text_Editor {
public:
	PTShell_Input(int X, int Y, int W, int H, const char* l = 0);
	void set_exec_cb(Pt_shell_exec_cb h);
	void append(const char*s);
	void RunCommand(const char *command);
private:
	virtual int handle(int e);
	Pt_shell_exec_cb exec_handler;
	Fl_Text_Buffer *buff;
    char cmd[1024];
};

#endif