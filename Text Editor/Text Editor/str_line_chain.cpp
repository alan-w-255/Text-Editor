#include "str_line_chain.h"

Str_Line_Chain::Str_Line_Chain()
{
	head = NULL;
	tail = NULL;
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

void Str_Line_Chain::write_file()
{
	ofp.open(file_name,ios::ate);
	ofp.clear();
	Str_Line*tmp = head;
	while (tmp != NULL)
	{
		ofp.write(tmp->to_string(),sizeof(tmp->to_string()));
	}
	ofp.close();
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

void Str_Line_Chain::set_cur(int num)
{
	cur_line = get_line(num);
}

void Str_Line_Chain::set_cur(Str_Line*sc)
{
	cur_line = sc;
}

Str_Line * Str_Line_Chain::del_line(int num)
{
	Str_Line*tmp = get_line(num);
	del_line(tmp);
	return get_line(num);
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
	target->next_line->pre_line = in_line;
	in_line->next_line = target;
	target->next_line = in_line;
	in_line->pre_line = target;
}

void Str_Line_Chain::clear_chain()
{
	while (head->next_line != tail)
	{
		del_line(head->next_line);
	}
}
