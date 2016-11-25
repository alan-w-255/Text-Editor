#ifdef _LINE_H_
#define _LINE_H_
#include<iostream>
#include<string.h> 
using namespace std;

class Str_Line
{
public:
    Str_Line();
    ~Str_Line();
    Line*pre_line;
    Line*next_line;
    void replace(string r,Line*l);

private: 
    string s;
};


#endif // !1