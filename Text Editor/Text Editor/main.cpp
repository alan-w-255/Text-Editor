#include"str_line.h"
#include"str_line_chain.h"
#include"editor.h"
using namespace std;

int main()
{
	char*file_name = "I:\\DSexercise\\Text-Editor\\when.txt";
	Editor*E = new Editor(file_name);
	E->run();
	return 0;
}
