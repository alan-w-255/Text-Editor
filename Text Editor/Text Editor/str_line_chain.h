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
	void read_file_to_buffer(ifstream*f);
	Str_Line*get_head_line();
	Str_Line*get_tail_line();
	Str_Line*get_line(int num);
	Str_Line*get_cur_line();
	Str_Line*get_next_line(Str_Line*cur);
	Str_Line*get_pre_line(Str_Line*cur);
	Str_Line*del_line(Str_Line*line);//ɾ��lineָ���һ�У�������һ��ָ�룻
	void clear_chain();
private:
	ifstream*fp;//�ļ���������
	Str_Line*head;
	Str_Line*tail;
	Str_Line*cur_line;

};

#endif // !_STR_LINE_CHAIN_H_

