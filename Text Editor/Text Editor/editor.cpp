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