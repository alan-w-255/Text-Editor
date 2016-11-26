#include "str_line_chain.h"

Str_Line_Chain::Str_Line_Chain()
{
	fp = NULL;
	head = NULL;
	tail = NULL;
}

Str_Line_Chain::Str_Line_Chain(char * c)
{
	fp->open(c, ios::in);
	head = NULL;
	tail = NULL;
}

Str_Line_Chain::~Str_Line_Chain()
{
	fp->close();
}

Str_Line * Str_Line_Chain::read_file_to_buffer(ifstream*f)
{
	char*tmp;
	f->getline(tmp, 300);
	head = new Str_Line(tmp);
	head->next_line = tail;
	tail->pre_line = head;
	while (!f->eof())
	{
		f->getline(tmp, 300);
		Str_Line*tp = new Str_Line(tmp);
		tp->pre_line = tail->pre_line;
		tp->next_line = tail;
		tail->pre_line = tp;
	}
	return nullptr;
}

Str_Line * Str_Line_Chain::get_head_line()
{
	return head;
}

Str_Line * Str_Line_Chain::get_tail_line()
{
	return tail;
}
