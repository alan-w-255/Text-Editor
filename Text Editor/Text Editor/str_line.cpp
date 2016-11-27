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
Str_Line::Str_Line(char*ss)
{
	pre_line = NULL;
	next_line = NULL;
	strcat_s(s, 300, ss);
}