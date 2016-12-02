#pragma once
#ifndef _STR_LINE_CHAIN_H_
#define _STR_LINE_CHAIN_H_
#include<iostream>
#include<fstream>
#include<istream>
#include"str_line.h"
using namespace std;

class Str_Line_Chain
{
public:
	Str_Line_Chain();
	Str_Line_Chain(char*c);
	~Str_Line_Chain();
	void read_file_to_buffer();
	Str_Line*get_head_line();
	Str_Line*get_tail_line();
	Str_Line*get_line(int num);
	Str_Line*get_next_line(Str_Line*cur);
	Str_Line*get_pre_line(Str_Line*cur);
	Str_Line*del_line(int num);
	Str_Line*del_line(Str_Line*line);//删除line指向的一行，返回下一行指针；
	Str_Line*search_substr(char*substr,Str_Line*cur);

	void insert_line(Str_Line*in_line,Str_Line*target);//在target前面插入新行 in_line;
	void clear_chain();
	bool is_modified();
	void saved();
private:
	ifstream ifp;//文件输入流。
	char*file_name;
	Str_Line*head;
	Str_Line*tail;
	bool is_changed;
	bool is_substr(char*sstr, char*tstr);
};

#endif // !_STR_LINE_CHAIN_H_

