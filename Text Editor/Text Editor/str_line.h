#pragma once
#ifndef _STR_LINE_H_
#define _STR_LINE_H_
#include<iostream>
#include<string.h>

using namespace std;
class Str_Line
{
public:
	Str_Line();
	Str_Line(char* ss);
	~Str_Line();
	char*to_string();
	void clear();
	void set_string(char*ch);
	int get_line_number();
	friend class Str_Line_Chain;
private:
	int line_number;
	char*s ;
	Str_Line*pre_line;
	Str_Line*next_line;
};

#endif // !_STR_LINE_H_

