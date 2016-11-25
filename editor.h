#ifndef _EDITOR_H_
#define _EDITOR_H_
#include<iostream>
#include<string.h>
#include"line.h"
using namespace std;

class Editor
{
public:
    Editor();
    ~Editor();
    string read_line();
    void save_file();
    void del_line();
    string read_next_line();
    string read_pre_line();
private:
    Line * cur_line;

    
};

#endif