#pragma once
#ifndef _EDITOR_H_
#define _EDITOR_H_
#include<iostream>
#include<string.h>
#include<windows.h>
#include"str_line.h"
#include"str_line_chain.h"

using namespace std;

class Editor
{
public:
    Editor();
	Editor(char*filename);
    ~Editor();
	void change_line();//改变当前行的内容
	void save_file();
	void go_begin();
	void go_end(FILE*f);
	void go_line();
	void view_file();
	void show_help();
	void show_cur_line();
	void quit_editor();
	void run();
    void read_next_line();
    void read_pre_line();
	void insert_line();
	void del_line();
private:
	bool is_valid_opt(char ch);
	Str_Line_Chain*slc;//creat a Str_Line_Chain object.
	Str_Line*cur_line;
	char opts[14] = { 'R','I','D','F','C','Q','H','?','N','P','B','E','G','V' };
};


#endif 