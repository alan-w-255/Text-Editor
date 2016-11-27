#include"str_line.h"
#include"str_line_chain.h"
#include"editor.h"
using namespace std;

int main()
{
	Editor*E = new Editor("hello.txt");
	E->run();
	return 0;
}
