#include "editor.h"
Editor::Editor()
{
	slc = NULL;
	cur_line = NULL;
}
Editor::~Editor()
{
	slc->clear_chain();
	delete in_file_name;
	delete out_file_name;
	delete slc;
}
void Editor::change_line()
{
	cout << "输入改变的内容" << endl;
	char*src_line = new char[300];
	cin.get();
	cin.getline(src_line, 300);
	Str_Line*sl = new Str_Line(src_line);
	slc->insert_line(sl, cur_line);
	cur_line = slc->del_line(cur_line);
	cout << "改变成功" << endl;
}

void Editor::save_file()
{
	slc->saved();
	cout << "请输入保存得文件名" << endl;
	cout << "请输入完整路径" << endl;
	out_file_name = new char[300];
	cin.get();
	cin.getline(out_file_name,300);
	ofstream outfile(out_file_name,ios::out);
	if (outfile.is_open())
	{
		outfile.clear();
		Str_Line*tmp = slc->get_head_line();
		while (tmp != slc->get_tail_line() && tmp->to_string() != NULL && tmp->to_string() != "")
		{
			outfile << tmp->to_string() << endl;
			//追加行到文件
			tmp = slc->get_next_line(tmp);
		}
		outfile.close();
		cout << "文件保存成功" << endl;
	}
	else
	{
		cout << "未能写入文件" << endl;
	}
}

void Editor::begin()
{
	//已经打开其他文件
	if (slc != NULL)
	{
		if (slc->is_modified()== true)
		{
			cout << "文件已经修改，但还未保存，确认打开新文件？(y/n),输入 w 保存" << endl;
			char tmp;
			cin >> tmp;
			if (tmp == 'y')
			{
				slc->clear_chain();
				cout << "请输入你要打开得文件（请写全路径）" << endl;
				cout << "文件输入格式示例：" << endl;
				cout << "C:\\\\filepath\\\\file" << endl;
				cin.get();
				cin.getline(in_file_name, 300);
				slc = new Str_Line_Chain(in_file_name);
				cur_line = slc->get_head_line();
				cout << cur_line->to_string() << endl;

			}
			else if (tmp == 'n')
			{
				;
			}
			//保存原文件
			else if (tmp == 'w')
			{
				save_file();
			}
			//非法输入
			else
			{
				cout << "请输入 y 或者 n" << endl;
			}
		}
		//文件未修改
		else
		{
			slc->clear_chain();
			cout << "请输入你要打开得文件（请写全路径）" << endl;
			cout << "文件输入格式示例：" << endl;
			cout << "C:\\\\filepath\\\\file" << endl;
			cin.get();
			cin.getline(in_file_name, 300);
			slc = new Str_Line_Chain(in_file_name);
			cur_line = slc->get_head_line();
			cout << cur_line->to_string() << endl;
		}
	}
	//第一次打开文件
	else
	{
		cout << "请输入你要打开得文件（请写全路径）" << endl;
		cout << "文件输入格式示例：" << endl;
		cout << "C:\\filepath\\file" << endl;
		cin.getline(in_file_name, 300);
		slc = new Str_Line_Chain(in_file_name);
		cur_line = slc->get_head_line();
		if (cur_line->to_string() == NULL)
		{
			;
		}
		else
		{
			cout << cur_line->to_string() << endl;
		}
	}
}

void Editor::go_B()
{
	cur_line = slc->get_head_line();
	cout << cur_line->to_string();
}

void Editor::go_end()
{
	Str_Line*tmp = slc->get_tail_line();
	cur_line =slc->get_pre_line(tmp);
	cout << cur_line->to_string()<<endl;
	cout << "已经到达文件尾部" << endl;
}

void Editor::go_line()
{
	int num;
	cout << "输入你要显示的行号" << endl;
	cin >> num;
	cur_line = slc->get_line(num);
	cout << cur_line->to_string() << endl;
}

void Editor::view_file()
{
	Str_Line*tmp = slc->get_head_line();
	if (tmp->to_string() == NULL)
	{
		;
	}
	else
	{
		do
		{
			cout << tmp->get_line_number() << ": " << tmp->to_string() << endl;
			tmp = slc->get_next_line(tmp);
		} while (tmp != slc->get_tail_line());
	}
}

void Editor::show_help()
{
	cout << "help:" << endl;
	cout << "输入 i 插入" << endl;
	cout << "输入 v 浏览整个文件" << endl;
	cout << "输入 w 保存文件" << endl;
	cout << "输入 q 退出" << endl;
	cout << "输入 n 浏览下一行" << endl;
	cout << "输入 p 浏览前一行" << endl;
	cout << "输入 s 显示当前行" << endl;
	cout << "输入 f 查找" << endl;
	cout << "输入 r 打开新文件" << endl;
	cout << "输入 b 到文件开头" << endl;
	cout << "输入 e 到文件末尾" << endl;
	cout << "输入 c 修改当前行" << endl;
	cout << "输入 d 删除行" << endl;
	cout << "输入 g 到某一行" << endl;
}

void Editor::show_cur_line()
{
	cout << cur_line->to_string() << endl;
}

void Editor::quit_editor()
{
	if (slc->is_modified())
	{
		cout << "文件已经修改,是否保存修改？(y/n)" << endl;
		char ch;
		cin >> ch;
		if (ch == 'y')
		{
			save_file();
			delete slc;
		}
		else if (ch == 'n')
		{
			delete slc;
		}
		else
		{
			cout << "输入错误，请输入 y 或者 n" << endl;
			quit_editor();
		}
	}
	else
	{
			delete slc;
	}
	exit(1);
}

void Editor::run()
{
	char opt='H';
	show_help();
	char*get_input = new char[20];
	begin();
	while (opt !='Q')
	{
		cout << "请输入指令" << endl;
		cin >> opt;
		opt=toupper(opt);
		if (is_valid_opt(opt))//判断是否是合法指令
		{
			switch (opt)
			{
				case 'R':begin(); break;//打开文件，显示第一行
				case 'I':insert_line();//插入一行
					 break;
				case 'W':save_file();
					break;
				case 'D':del_line();//删除一行；
					 break;
				case 'F':search_substr();
					 break;
				case 'C':change_line();
					 break;
				case 'Q':quit_editor();
					 break;
				case 'H':show_help();
					 break;
				case '?':show_help();
					break;
				case 'N':read_next_line();
					 break;
				case 'P':read_pre_line();
					 break;
				case 'B':go_B();
					 break;
				case 'E':go_end();
					 break;
				case 'G':go_line();
					break;
				case 'V':view_file();
					break;
				case 'S':show_cur_line();
				default:
					break;
			}
		}
		else
		{
			cout << "输入指令不正确，请重新输入" << endl;
			show_help();
		}
	}
}

void Editor::read_next_line()
{
	cur_line = slc->get_next_line(cur_line);
	cout << cur_line->to_string() << endl;
}

void Editor::read_pre_line()
{
	cur_line = slc->get_pre_line(cur_line);
	cout << cur_line->to_string() << endl;
}

void Editor::insert_line()
{
	int num_line = 0;
	cout << "输入你要插入的行号" << endl;
	cin >> num_line;
	if (slc->get_head_line()->to_string() == NULL)
	{
		cout << "你将插入第一行" << endl;
		cout << "请输入你要插入的内容" << endl;
		char*ch = new char[300];
		cin.get();
		cin.get(ch, 300);
		cur_line = slc->get_head_line();
		slc->get_head_line()->set_string(ch);
		cout << "插入行成功" << endl;
	}
	else if (num_line <= 1)
	{
		cout << "你将在第一行前插入： " << slc->get_line(1)->to_string() << endl;
		cout << "请输入你要插入的内容" << endl;
		char*ch = new char[300];
		cin.get();
		cin.get(ch, 300);
		Str_Line*ins_line = new Str_Line(ch);
		Str_Line*tmp = slc->get_line(num_line);
		slc->insert_line(ins_line, tmp);
		cur_line = ins_line;
		cout << "插入行成功" << endl;
	}
	else if (num_line < slc->get_tail_line()->get_line_number())
	{
		cout << "你将在此行后插入： " << slc->get_line(num_line - 1)->to_string() << endl;
		cout << "请输入你要插入的内容" << endl;
		char*ch = new char[300];
		cin.get();
		cin.get(ch, 300);
		Str_Line*ins_line = new Str_Line(ch);
		Str_Line*tmp = slc->get_line(num_line);
		slc->insert_line(ins_line, tmp);
		cur_line = ins_line;
		cout << "插入行成功" << endl;
	}
	else if (num_line >= slc->get_tail_line()->get_line_number())
	{
		cout << "你将插入最后一行"<<endl;
		cout << "请输入你要插入的内容" << endl;
		char*ch = new char[300];
		cin.get();
		cin.get(ch, 300);
		Str_Line*ins_line = new Str_Line(ch);
		slc->insert_line(ins_line, slc->get_tail_line());
		cur_line = ins_line;
		cout << "插入行成功" << endl;
	}
}

void Editor::del_line()
{
	cout << "输入你要删除的行号" << endl;
	int num;
	cin >> num;
	if (num < 0)
	{
		cout << num << "行不存在" << endl;
	}
	else if (num >= slc->get_tail_line()->get_line_number())
	{
		cout << num << "行不存在" << endl;
	}
	else
	{
		cur_line = slc->del_line(num);
		cout << "删除成功" << endl;
	}
}

void Editor::search_substr()
{
	cout << "请输入你要查找的字符" << endl;
	char*ss = new char[300];
	cin.get();
	cin.getline(ss, 300);
	Str_Line*tmp = slc->search_substr(ss, cur_line);
	if (tmp == nullptr)
	{
		cout << "从头开始找" << endl;
		tmp = slc->search_substr(ss, slc->get_head_line());
		if (tmp == NULL)
		{
			cout << "未找到" << ss << endl;
		}
		else
		{
			cur_line = tmp;
			cout << "找到该行:"<<endl<<cur_line->get_line_number() << ": "<<cur_line->to_string() << endl;
		}
	}
	else
	{
		cur_line = slc->search_substr(ss, slc->get_head_line());
		cout << "找到该行:"<<cur_line->get_line_number() << ": "<<cur_line->to_string() << endl;
	}
}

bool Editor::is_valid_opt(char ch)
{
	bool flag = false;
	for (int i = 0; i < sizeof(opts); i++)
	{
		if (ch == opts[i])
		{
			flag = true;
		}
	}
	return flag;
}
