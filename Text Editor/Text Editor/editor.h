#pragma once
#ifndef _EDITOR_H_
#define _EDITOR_H_
#include<iostream>
#include<string.h>
#include"str_line.h"

using namespace std;

class Editor
{
public:
    Editor();
	Editor(char*filename);
    ~Editor();
	void change_line(char*src_line,int target_line_number);
	void go_begin();
	void go_end(FILE*f);
	void go_line(int num);
	void view_file();
	void show_help();
	void quit_editor();
	void run();
    char*read_next_line();
    char*read_pre_line();
private:
	Str_Line_Chain*slc;//creat a Str_Line_Chain object.
};


#endif 