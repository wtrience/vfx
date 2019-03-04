#include "command.h"
#include"fileSystem.h"
#include"fileAndFolder.h"
#include <windows.h>

Command::Command()
{

}

Command::~Command()
{

}

void Command::CommandWindows()
{
	FileSystem fs;
	Command command;
	string s;
	time_t t = time(0);
	char tmp[64];

	while (1) {
		fs.display();
		while (cin >> s)
		{
			if (s == "mkdir")
				fs.newFolder();
			else if (s == "cls")
				system("cls");
			else if (s == "dir")
				fs.showFolder();
			/*
			else if (s == "mk")
				fs.newFile();

			else if (s == "cd")
				fs.openFolder();
			
			else if (s == "back")
				fs.goback();
			else if (s == "exit")
				exit(0);

			else if (s == "rmdir")
				fs.deleteFolder();
			else if (s == "rm")
				fs.deleteFile();
			else if (s == "renamedir")
				fs.renameFolder();
			else if (s == "renamefile")
				fs.renameFile();
			else if (s == "copydir")
				fs.copyFolder();
			else if (s == "pastedir")
				fs.pasteFolder();
			else if (s == "copyfile")
				fs.copyFile();
			else if (s == "pastefile")
				fs.pasteFile();
					*/
			else  if (s == "help" || s == "h")
			{
				command.Help();
			}
			else
			{
				cout << "找不到对应命令，请参看\"help\"" << endl;
			}
		
			fs.display();
		}

	}


}

void Command::Help()
{
	cout<< "dir    | 列出当前目录下的目录和文件\n"
		<< "md     | 创建目录\n"
		<< "rd     |"
		<< "cd     |"
		<< "del    |"
		<< "copy   |"
		<< "ren    |"
		<< "move   |"
		<< "mklink |"
		<< "save   |"
		<< "load   |"
		<< "cls    |";

}

