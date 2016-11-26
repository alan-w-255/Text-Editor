#pragma once
#ifndef _FILE_OPT_H_
#define _FILE_OPT_H_
#include<fileapi.h>
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
class File_Opt
{
public:
	File_Opt();
	~File_Opt();

private:
	FILE*f;
};

File_Opt::File_Opt()
{
}

File_Opt::~File_Opt()
{
}
#endif // !_FILE_OPT_H_
