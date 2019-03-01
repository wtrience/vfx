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

    while(1){
        fs.display();
        		while (cin >> s)
		{
			if (s == "mkdir")
				fs.newFolder();
			else if (s == "mk")
				fs.newFile();
			else if (s == "ls")
				fs.showFolder();
			else if (s == "cd")
				fs.openFolder();
			else if (s == "cls")
				system("cls");
			else if (s == "back")
				fs.goback();
			else if (s == "exit")
				exit(0);
            else  if (s == "help" || s == "h")
			{
				//输出帮助文档
				command.Help();
				//menu.FunctionMenu();
			}
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


			//各指令使用方式
			else if (s == "mkdir+?")
				cout << "mkdir: mkdir [dirname] (ex:madir dir)" << endl;
			else if (s == "mk+?")
				cout << "mk: [filename] (ex:mk file)" << endl;
			else if (s == "ls+?")
				cout << "ls: ls " << endl;
			else if (s == "cd+?")
				cout << "cd: cd [dirname] (ex:cd dir)" << endl;
			else if (s == "cls+?")
				cout << "cls: cls" << endl;
			//else if (s == "logout+?")
				//cout << "注 销(返回欢迎界面): logout " << endl;
			else if (s == "back+?")
				cout << "back: back" << endl;
			else if (s == "exit+?")
				cout << "exit: exit" << endl;
			//else if (s == "back+?")
				//cout << "返回上级菜单: back " << endl;
			else if (s == "help+?")
				cout << "help: help/h" << endl;
			else if (s == "rmdir+?")
				cout << "rmdir: rmdir [dirname] (ex:rmdir dir)" << endl;
			else if (s == "rm+?")
				cout << "rm: rm [filename] (ex:rm file)" << endl;
			else if (s == "renamedir+?")
				cout << "renamedir: renamedir [olddiranme] [newdirname] (ex:renamedir odir ndir)" << endl;
			else if (s == "renamefile+?")
				cout << "renamefile: renamefile [oldfile] [newfile] (ex:renamefile ofile nfile)" << endl;

			else if (s == "read+?")
				cout << "read: read [filename] (ex:read file)" << endl;
			else if (s == "vi+?")
				cout << "vi: vi [filename] [content] (ex:vi file content)" << endl;

			else if (s == "copydir+?")
				cout << "copydir: copydir [dirname] (ex:copydir dir)" << endl;
			else if (s == "pastedir+?")
				cout << "pastedir: pastedir " << endl;
			else if (s == "copyfile+?")
				cout << "copyfile: copyfile [filename] (ex:copyfile file)" << endl;
			else if (s == "pastfile+?")
				cout << "pastfile: pastfile " << endl;
			else if (s == "alterfile+?")
				cout << "alterfile: alterfile [filename]  (ex:alterfile file)" << endl;
			else
			{
				cout << "找不到对应指令,请重新输入" << endl;
			}
			fs.display();
        }

    }
    

}

void Command::Help()
{
    cout <<"dir | 列出当前目录下的目录和文件\n"
    <<"md | 创建目录\n"
    <<"rd |"
    <<"cd |"
    <<"del |"
    <<"copy |"
    <<"ren |"
    <<"move |"
    <<"mklink |"
    <<"save |"
    <<"load |"
    <<"cls |";

}

