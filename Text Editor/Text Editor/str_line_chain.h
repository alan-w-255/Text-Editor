#pragma once
#ifndef _STR_LINE_CHAIN_H_
#define _STR_LINE_CHAIN_H_
#include"str_line.h"
#include<iostream>
#include<fstream>
#include<istream>
using namespace std;

class Str_Line_Chain
{
public:
	Str_Line_Chain();
	Str_Line_Chain(char*c);
	~Str_Line_Chain();
	Str_Line*read_file_to_buffer(ifstream*f);
	Str_Line*get_head_line();
	Str_Line*get_tail_line();
private:
	ifstream*fp;//文件输入流。
	Str_Line*head;
	Str_Line*tail;

};

#endif // !_STR_LINE_CHAIN_H_

