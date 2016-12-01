#include"str_line.h"
Str_Line::Str_Line()
{
	pre_line = NULL;
	next_line = NULL;
}

Str_Line::~Str_Line()
{
	delete s;
}
char * Str_Line::to_string()
{
	return s;
}
void Str_Line::set_string(char*ch)
{
	s = ch;
}
int Str_Line::get_line_number()
{
	return line_number;
}
Str_Line::Str_Line(char*ss)
{
	pre_line = NULL;
	next_line = NULL;
	s = ss;
}