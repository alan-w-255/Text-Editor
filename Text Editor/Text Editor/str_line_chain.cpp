#include "str_line_chain.h"

Str_Line_Chain::Str_Line_Chain()
{
	head = NULL;
	tail = NULL;
	file_name = NULL;
}

Str_Line_Chain::Str_Line_Chain(char * c)
{
	head = NULL;
	tail = NULL;
	file_name = c;
	read_file_to_buffer();
}

Str_Line_Chain::~Str_Line_Chain()
{
	clear_chain();
	delete head;
	delete tail;
}

void Str_Line_Chain::read_file_to_buffer()
{
	ifp.open(file_name, ios::in | ios::out);
	bool x = ifp.is_open();
	char*tmp = new char[300];
	ifp.getline(tmp, 300);
	head = new Str_Line(tmp);
	tail = new Str_Line();
	head->next_line = tail;
	head->line_number = 1;
	tail->pre_line = head;
	tail->line_number = 2;

	while (!ifp.eof())
	{
		char*ch=new char[300];
		ifp.getline(ch, 300);
		Str_Line*tp = new Str_Line(ch);
		tp->pre_line = tail->pre_line;
		tp->next_line = tail;
		tail->pre_line->next_line = tp;
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
		return tail->pre_line;
	}
	else if (num < head->line_number)
	{
		return head;
	}
	else
	{
		Str_Line*tmp = head;
		while (num != tmp->line_number)
		{
			tmp= tmp->next_line;
		}
		return tmp;
	}
}


Str_Line * Str_Line_Chain::get_next_line(Str_Line * cur)
{
	return cur->next_line;
}

Str_Line * Str_Line_Chain::get_pre_line(Str_Line * cur)
{
	return cur->pre_line;
}

Str_Line * Str_Line_Chain::del_line(int num)
{
	if (num >= tail->line_number)//如果输入行号大于尾节点得行号，删除尾节点前一行，返回尾节点前一行。因为尾节点为空节点。
	{
		del_line(tail->pre_line);
		return tail->pre_line;
	}
	else if (num <= 0)
	{
		head = head->next_line;
		del_line(head->pre_line);
		return head;
	}
	else
	{
		Str_Line*tmp = get_line(num);
		del_line(tmp);
		return get_line(num);
	}
}

Str_Line * Str_Line_Chain::del_line(Str_Line * line)
{
	Str_Line*tmp = line->next_line;
	while (tmp != NULL)
	{
		tmp->line_number--;
		tmp = tmp->next_line;
	}
	line->pre_line->next_line = line->next_line;
	line->next_line->pre_line = line->pre_line;
	tmp = line->next_line;
	delete line;
	return tmp;
}

void Str_Line_Chain::insert_line(Str_Line * in_line, Str_Line*target)
{
	in_line->line_number = target->line_number;
	Str_Line*tmp = target;
	while (tmp != NULL)
	{
		tmp->line_number++;
		tmp = tmp->next_line;
	}
	if (in_line->get_line_number() == 1)
	{
		in_line->next_line = target;
		target->pre_line = in_line;
		head = in_line;
	}
	else
	{
		target->pre_line->next_line = in_line;
		in_line->pre_line = target->pre_line;
		in_line->next_line = target;
		target->pre_line = in_line;
	}
}

void Str_Line_Chain::clear_chain()
{
	while (head->next_line != tail)
	{
		del_line(head->next_line);
	}
}
