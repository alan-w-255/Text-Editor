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
	//�������ļ�
	if (x == false)
	{
		ofstream ofp(file_name, ios::out);
		if (ofp.is_open())
		{
			is_changed = true;
			cout << "���ļ�" << endl;
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
			cout << "�������ļ�ʧ��" << endl;
		}
	}
	// �ļ��Ѿ����ڣ�
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
	if (num >= tail->line_number)//��������кŴ���β�ڵ���кţ�ɾ��β�ڵ�ǰһ�У�����β�ڵ�ǰһ�С���Ϊβ�ڵ�Ϊ�սڵ㡣
	{

		tail->line_number = tail->pre_line->line_number;
		Str_Line*tmp = tail->pre_line;
		tail->pre_line = tmp->pre_line;
		tmp->pre_line->next_line = tail;
		delete tmp;
		return tail->pre_line;
	}
	else if (num <= 1)//��������к�С��ͷ�ڵ��кţ�ɾ��ͷ�ڵ㣬�����µ�ͷ�ڵ㡣
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
	if (dline == tail)//��������кŴ���β�ڵ���кţ�ɾ��β�ڵ�ǰһ�У�����β�ڵ�ǰһ�С���Ϊβ�ڵ�Ϊ�սڵ㡣
	{

		tail->line_number = tail->pre_line->line_number;
		Str_Line*tmp = tail->pre_line;
		tail->pre_line = tmp->pre_line;
		tmp->pre_line->next_line = tail;
		delete tmp;
		return tail->pre_line;
	}
	else if (dline == head)//��������к�С��ͷ�ڵ��кţ�ɾ��ͷ�ڵ㣬�����µ�ͷ�ڵ㡣
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
	//target�ڵ�����μ�һ��
	while (tmp != NULL)
	{
		tmp->line_number++;
		tmp = tmp->next_line;
	}
	//����������ͷ�ڵ�,����ͷ�ڵ�ǰ,��Ϊ�µ�ͷ�ڵ㣻
	if (in_line->get_line_number() == 1)
	{
		in_line->next_line = target;
		target->pre_line = in_line;
		head = in_line;
	}
	//�������ͷ�ڵ㣬����target�ڵ�֮ǰ
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
