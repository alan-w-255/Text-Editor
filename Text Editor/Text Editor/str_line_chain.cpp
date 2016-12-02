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
	is_changed = false;
	ifp.open(file_name, ios::in);
	bool x = ifp.is_open();
	//创建新文件
	if (x == false)
	{
		ofstream ofp(file_name, ios::out);
		if (ofp.is_open())
		{
			is_changed = true;
			cout << "新文件" << endl;
			ofp.close();
			ifp.open(file_name, ios::in);
			head = new Str_Line();
			head->line_number = 1;
			tail = new Str_Line();
			tail->line_number = 2;
			head->next_line = tail;
			tail->pre_line = head;
		}
		else
		{
			cout << "创建新文件失败" << endl;
		}
	}
	// 文件已经存在；
	else
	{
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
			char*ch = new char[300];
			ifp.getline(ch, 300);
			if (ch != "")
			{
				Str_Line*tp = new Str_Line(ch);
				tp->pre_line = tail->pre_line;
				tp->next_line = tail;
				tail->pre_line->next_line = tp;
				tp->line_number = tail->line_number;
				tail->pre_line = tp;
				tail->line_number++;
			}
		}
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
	if (num >= tail->line_number)
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
	is_changed = true;
	if (num >= tail->line_number)//如果输入行号大于尾节点得行号，删除尾节点前一行，返回尾节点前一行。因为尾节点为空节点。
	{

		tail->line_number = tail->pre_line->line_number;
		Str_Line*tmp = tail->pre_line;
		tail->pre_line = tmp->pre_line;
		tmp->pre_line->next_line = tail;
		delete tmp;
		return tail->pre_line;
	}
	else if (num <= 1)//如果输入行号小于头节点行号，删除头节点，返回新得头节点。
	{
		head = head->next_line;
		delete head->pre_line;
		head->pre_line = NULL;
		Str_Line*tmp = head;
		while (tmp != NULL)
		{
			tmp->line_number--;
			tmp = tmp->next_line;
		}

		return head;
	}
	else
	{
		Str_Line*tmp = get_line(num);
		tmp->next_line->pre_line = tmp->pre_line;
		tmp->pre_line->next_line = tmp->next_line;
		while (tmp != NULL)
		{
			tmp->line_number--;
			tmp = tmp->next_line;
		}
		return get_line(num);
	}
}

Str_Line * Str_Line_Chain::del_line(Str_Line*dline)
{
	is_changed = true;
	if (dline == tail)//如果输入行号大于尾节点得行号，删除尾节点前一行，返回尾节点前一行。因为尾节点为空节点。
	{

		tail->line_number = tail->pre_line->line_number;
		Str_Line*tmp = tail->pre_line;
		tail->pre_line = tmp->pre_line;
		tmp->pre_line->next_line = tail;
		delete tmp;
		return tail->pre_line;
	}
	else if (dline == head)//如果输入行号小于头节点行号，删除头节点，返回新得头节点。
	{
		head = head->next_line;
		delete head->pre_line;
		head->pre_line = NULL;
		Str_Line*tmp = head;
		while (tmp != NULL)
		{
			tmp->line_number--;
			tmp = tmp->next_line;
		}
		return head;
	}
	else
	{
		Str_Line*tmp = dline;
		while (tmp != NULL)
		{
			tmp->line_number--;
			tmp = tmp->next_line;
		}
		tmp = dline;
		tmp->next_line->pre_line = tmp->pre_line;
		tmp->pre_line->next_line = tmp->next_line;
		dline = dline->pre_line;
		delete tmp;
		return dline;
	}
}

Str_Line * Str_Line_Chain::search_substr(char * substr,Str_Line*cur)
{
	char*ts = cur->s;
	Str_Line*tmp = cur;
	while (tmp != tail)
	{
		ts = tmp->s;
		if (is_substr(substr, ts))
		{
			return tmp;
		}
		else
		{
			tmp = tmp->next_line;

		}
	}
	return nullptr;
}

void Str_Line_Chain::insert_line(Str_Line * in_line, Str_Line*target)
{
	is_changed = true;
	in_line->line_number = target->line_number;
	Str_Line*tmp = target;
	//target节点后依次加一；
	while (tmp != NULL)
	{
		tmp->line_number++;
		tmp = tmp->next_line;
	}
	//如果插入的是头节点,插在头节点前,成为新的头节点；
	if (in_line->get_line_number() == 1)
	{
		in_line->next_line = target;
		target->pre_line = in_line;
		head = in_line;
	}
	//如果不是头节点，插在target节点之前
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
	is_changed = true;
	while (head->next_line != tail)
	{
		del_line(head->next_line);
	}
	head->clear();
}

bool Str_Line_Chain::is_modified()
{
	return is_changed;
}

void Str_Line_Chain::saved()
{
	is_changed = false;
}

bool Str_Line_Chain::is_substr(char * sstr, char * tstr)
{
	for (int i = 0; i < strlen(tstr)-strlen(sstr)+1; i++)
	{
		for (int j = 0; j < strlen(sstr); j++)
		{
			if (sstr[j] != tstr[i+j])
			{
				break;
			}
			if (j == strlen(sstr) - 1)
			{
				return true;
			}
		}
	}
	return false;
}
