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
	clear_chain();
	delete head;
	delete tail;
	fp->close();
}

void Str_Line_Chain::read_file_to_buffer(ifstream*f)
{
	char*tmp;
	f->getline(tmp, 300);
	head = new Str_Line(tmp);
	tail = new Str_Line();
	head->next_line = tail;
	head->line_number = 1;
	tail->pre_line = head;
	tail->line_number = 2;

	while (!f->eof())
	{
		f->getline(tmp, 300);
		Str_Line*tp = new Str_Line(tmp);
		tp->pre_line = tail->pre_line;
		tp->next_line = tail;
		tp->line_number = tail->line_number;
		tail->pre_line = tp;
		tail->line_number++;
	}
}

Str_Line * Str_Line_Chain::get_head_line()
{
	return head;
}

Str_Line * Str_Line_Chain::get_tail_line()
{
	return tail;
}

Str_Line * Str_Line_Chain::get_line(int num)
{
	if (num > tail->line_number)
	{
		cur_line = tail;
		return cur_line;
	}
	else if (num < head->line_number)
	{
		cur_line = head;
		return cur_line;
	}
	else if (num > cur_line->line_number)
	{
		while (num != cur_line->line_number)
		{
			cur_line = cur_line->next_line;
		}
		return cur_line;
	}
	else if (num < cur_line->line_number)
	{
		while (num != cur_line->line_number)
		{
			cur_line = cur_line->pre_line;
		}
		return cur_line;
	}
	else
	{
	return nullptr;
	}
}

Str_Line * Str_Line_Chain::get_cur_line()
{
	return cur_line;
}

Str_Line * Str_Line_Chain::get_next_line(Str_Line * cur)
{
	cur_line = cur->next_line;
	return cur_line;
}

Str_Line * Str_Line_Chain::get_pre_line(Str_Line * cur)
{
	cur_line = cur->pre_line;
	return cur_line;
}

Str_Line * Str_Line_Chain::del_line(Str_Line * line)
{
	line->pre_line->next_line = line->next_line;
	line->next_line->pre_line = line->pre_line;
	Str_Line*tmp = line->next_line;
	delete line;
	return tmp;
}

void Str_Line_Chain::clear_chain()
{
	while (head->next_line != tail)
	{
		del_line(head->next_line);
	}
}
