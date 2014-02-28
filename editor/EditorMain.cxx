//
// "$Id: CubeMain.cxx 8864 2011-07-19 04:49:30Z greg.ercolano $"
//
// CubeView class .
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <cstring>
#include <unistd.h>

#include "EditorBackEnd.h"
using namespace std;

string SendShellCommand(FILE* inputPipe, FILE* outputPipe, char* command)
{
	char buf [300];
	int first = 0;
	string resultString;
	fprintf(inputPipe, "%s\n", command);
	fflush(inputPipe);
	fprintf(inputPipe, ".\n");
	fflush(inputPipe);
	
	
	while(fgets(buf, 1024, outputPipe))
	{	
		if(strstr(buf, "pt_shell>") && !first)
		{
			first = 1;
			strncpy(buf, buf+10, strlen(buf));
			resultString += buf;
		
		}
		else if(strstr(buf, "pt_shell>") && first)
		{
			first = 0;
			break;
		}
		else
		{
			resultString += buf;
		}			
	}
	return resultString;
}


int main(int argc, char **argv) {

	int wpipe[2];
	int rpipe[2];
	pid_t pid;
	pipe(wpipe);
	pipe(rpipe);
	pid = fork();
	
	
    if (pid == -1) 
    {
        printf("\n-E- Error creating fork to execute new process");
        return 1;
    }

    if (pid) 
    {
	//Parent
	/*  wait till integration to uncomment and integrate
	FILE* inputFile = fdopen(wpipe[1], "w");
	FILE* outputFile = fdopen(rpipe[0], "r");
	char buf [1024];
	char command[100];
	close(wpipe[0]);
	close(rpipe[1]);
	for(int start = 0; start < 10; start++)
	{
		fgets(buf, 1024, outputFile);
	}
	//TODO: Change the run loop function under
	while(1)
	{
		cin.getline(command,100);
		printf("Output:%s", SendShellCommand(inputFile, outputFile, command).c_str());	
	}	
	*/
	init(argc, argv);
	return Fl::run();
    } 
    else 
    {
	close(wpipe[1]);
   	close(rpipe[0]);
  	dup2(wpipe[0], STDIN_FILENO);
  	dup2(rpipe[1], STDOUT_FILENO);
	/*****************************************************************************/
	//TODO: Update the shell here
	/*****************************************************************************/
		
	if(execl("/uusoc/facility/cad_common/Synopsys/PTS-S13/amd64/syn/bin/pt_shell", "pt_shell", NULL) == -1)
	{
		printf("\n-E- Error executing synthesis");
	}
    }

    return 0;
}
/*
int main(int argc, char **argv) {

    init(argc, argv);
    return Fl::run();
}
*/
