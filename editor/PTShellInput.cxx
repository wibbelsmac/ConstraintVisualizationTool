#include "PTShellInput.h"
#include <iostream>
#include <FL/Fl.H>



PTShell_Input::PTShell_Input(int X, int Y, int W, int H, const char* l)
: Fl_Text_Editor(X,Y,W,H, l) {
	exec_handler = 0;
	buff = new Fl_Text_Buffer();
    buffer(buff);
    buff->append("dc_shell> ");
    buff->call_modify_callbacks();
    //textfont(FL_COURIER);
    //textsize(12);
    cmd[0] = 0;
}


void PTShell_Input::set_exec_cb(Pt_shell_exec_cb h) {
	exec_handler = h;
}
    // Append to buffer, keep cursor at end
    void PTShell_Input::append(const char*s) {
        buff->append(s);
        // Go to end of line
        insert_position(buffer()->length());
        scroll(count_lines(0, buffer()->length(), 1), 0);
    }
    // Run the specified command in the shell, append output to terminal
    void PTShell_Input::RunCommand(const char *command) {
       
    }
    // Handle events in the Fl_Text_Editor
    int PTShell_Input::handle(int e) {
        switch (e) {
            case FL_KEYUP: {
                int key = Fl::event_key();
                if ( key == FL_Enter ) return(1);              // hide Enter from editor
                if ( key == FL_BackSpace && cmd[0] == 0 ) return(0);
                break;
            }
            case FL_PASTE: {
            	strncat(cmd, Fl::event_text(), sizeof(cmd)-1); // adds text to command after paste event
            	cmd[sizeof(cmd)-1] = 0;
            	break;
            }
            case FL_KEYDOWN: {
                int key = Fl::event_key();
                // Enter key? Execute the command, clear command buffer
                if ( key == FL_Enter ) {
                    // Execute commands here
                    std::cout << cmd << std::endl;
                    cmd[0] = 0;
                    append("\ndc_shell> ");
                    return(1);                          // hide 'Enter' from text widget
                }
                if ( key == FL_BackSpace ) {
                    // Remove a character from end of command buffer
                    if ( cmd[0] ) {
                        cmd[strlen(cmd)-1] = 0;
                        break;
                    } else {
                        return(0);
                    }
                } else {
                    // Append text to cmd buffer
                    strncat(cmd, Fl::event_text(), sizeof(cmd)-1);
                    cmd[sizeof(cmd)-1] = 0;
                }
                break;
            }
        }
        return(Fl_Text_Editor::handle(e));
    }
