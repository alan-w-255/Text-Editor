#include "editor.h"
Editor::Editor()
{
	slc = NULL;
}
Editor::Editor(char*filename)
{
	slc = new Str_Line_Chain(filename);
	cur_line = slc->get_head_line();
}
Editor::~Editor()
{
	delete slc;
}
void Editor::change_line()
{
	cout << "输入改变的内容" << endl;
	char*src_line = new char[300];
	cin.getline(src_line, 300);
	Str_Line*sl = new Str_Line(src_line);
	slc->insert_line(sl, cur_line);
	slc->del_line(cur_line);
}

void Editor::save_file()
{
}

void Editor::go_begin()
{
	cur_line = slc->get_head_line();
	cout << cur_line->to_string() << endl;
}

void Editor::go_end(FILE * f)
{
	cur_line = slc->get_tail_line();
	cout << cur_line->to_string();
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
	do
	{
		cout << tmp->get_line_number() << ": " << tmp->to_string() << endl;
		tmp = slc->get_next_line(tmp);
	} while (tmp != slc->get_tail_line());
}

void Editor::show_help()
{
	cout << "help:" << endl;
	cout << "输入 i 插入，输入 v 浏览整个文件,,,, " << endl;
}

void Editor::show_cur_line()
{
	cout << cur_line->to_string() << endl;
}

void Editor::quit_editor()
{
	delete slc;
	//关闭文件
	//释放内存
}

void Editor::run()
{
	char opt = 'R';
	go_begin();
	while (opt !='Q')
	{
		opt = 'R';//默认指令为R
		cout << "请输入指令" << endl;
		cin >> opt;
		opt=toupper(opt);
		if (is_valid_opt(opt))//判断是否是合法指令
		{
			switch (opt)
			{
				case 'R':go_begin(); break;//打开文件，显示第一行
				case 'I':insert_line();//插入一行
					; break;
			//	case 'D':del_line();//删除一行；
					 break;
			//	case 'F':insert_line();
					 break;
			//	case 'C':change_line();
					 break;
			//	case 'Q':quit_editor();
					 break;
				case 'H':show_help();
					 break;
			//	case '?':show_help();
					break;
			//	case 'N':read_next_line();
					 break;
			//	case 'P':read_pre_line();
					 break;
			//	case 'B':read_pre_line();
					 break;
			//	case 'E':insert_line();
					 break;
				case 'G':go_line();
					 break;
				case 'V':view_file(); break;
				default:
					break;
			}
		}
		else
		{
			cout << "输入指令不正确，请重新输入" << endl;
		}
	}
}

void Editor::read_next_line()
{
	cur_line = slc->get_next_line(cur_line);
	cout << cur_line->to_string();
}

void Editor::read_pre_line()
{
	cur_line = slc->get_pre_line(cur_line);
	cout << cur_line->to_string();
}

void Editor::insert_line()
{
	int num_line = 0;
	cout << "输入你要插入的行号" << endl;
	cin >> num_line;
	cout <<"你将在此行后插入： "<< slc->get_line(num_line-1)->to_string() << endl;
	cout << "请输入你要插入的内容" << endl;
	char*ch = new char[300];
	cin.get();
	cin.get(ch, 300);
	Str_Line*ins_line = new Str_Line(ch);
	Str_Line*tmp = slc->get_line(num_line);
	slc->insert_line(ins_line, tmp);
	cur_line = ins_line;
	cout << "插入行成功" << endl;
	cout << cur_line->to_string() << endl;
	cout << "hello " << endl;

}

void Editor::del_line()
{
	cout << "输入你要删除的行号" << endl;
	int num;
	cin >> num;
	slc->del_line(num);
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


