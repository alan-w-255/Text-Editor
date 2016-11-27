#include "editor.h"
Editor::Editor()
{
	slc = NULL;
}
Editor::Editor(char*filename)
{
	slc = new Str_Line_Chain(filename);
}
Editor::~Editor()
{
	delete slc;
}
void Editor::change_line(char*src_line, int target_line_number)
{

}

void Editor::go_begin()
{
	cur_line = slc->get_head_line();
}

void Editor::go_end(FILE * f)
{
	cur_line = slc->get_tail_line;
}

void Editor::go_line(int num)
{
	cur_line = slc->get_line(num);
}

void Editor::view_file()
{
	Str_Line*tmp = slc->get_head_line();
	while (tmp != slc->get_tail_line())
	{
		cout << endl;
		cout << tmp->to_string()<<endl;
	}
}

void Editor::show_help()
{
	cout << "help" << endl;
}

void Editor::quit_editor()
{
	delete slc;
	//关闭文件
	//释放内存
}

void Editor::run()
{
	char opt;
	cout << "请输入指令" << endl;
	show_help();
	cin >> opt;
	opt=toupper(opt);
	switch (opt)
	{
	case 'R':go_begin(); break;
	case 'I':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'D':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'F':insert_line(cur_line);
		cout << "请输入指令" << endl; break;
	case 'C':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'Q':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'H':show_help();
		cout<<"请输入指令"<<endl; break;
	case 'N':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'P':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'B':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'E':insert_line(cur_line);
		cout<<"请输入指令"<<endl; break;
	case 'G':insert_line(cur_line);
		cout << "请输入指令" << endl; break;
	case 'V':view_file(); break;
	default:
		break;
	}
}

void Editor::read_next_line()
{
	cur_line = slc->get_cur_line();
	cur_line = slc->get_next_line(cur_line);
	cout << cur_line->to_string;
}

void Editor::read_pre_line()
{
	cur_line = slc->get_cur_line();
	cur_line = slc->get_pre_line(cur_line);
	cout << cur_line->to_string;
}

