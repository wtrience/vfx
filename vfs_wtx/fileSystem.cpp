#include "fileSystem.h"
#include "fileAndFolder.h"
#include "command.h"

#include<fstream>

#include<vector>
#include<string>

using namespace std;

#pragma warning( disable : 4996 )

FileSystem::FileSystem()
{
	root = new Folder();
	root->folderName = "";
	currentFolder = root;
	tempfile = 0;
	tempfolder = 0;
}

FileSystem::~FileSystem()
{
	delete currentFolder;
	delete root;
	delete tempfile;
	delete tempfolder;
}

//新建目录
Folder* FileSystem::newFolder()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	Folder *p = new Folder();
	cin >> p->folderName;
	if (currentFolder != NULL)
	{
		if (currentFolder->folderPtr == NULL)
		{
			currentFolder->folderPtr = p;
			p->preFolder = currentFolder;
			
			p->folderCreateTime = tmp;
			p->folderAlterTime = tmp;
		}
		else//该目录下目录链表指针不为空
		{
			//该指针用于遍历
			Folder *q;
			q = currentFolder->folderPtr;
			while (q->nextFolder != NULL)
			{
				if (!strcmp(p->folderName.c_str(), q->folderName.c_str()))//文件夹同名
				{
					cout << "同级目录不能重名！" << endl;
					cout << "同级目录不能重名999！" << endl;
					return 0;
				}

				q = q->nextFolder;
			}
			if (!strcmp(p->folderName.c_str(), q->folderName.c_str()))
			{
				cout << "同级目录不能重名！" << endl;
				return 0;
			}
			q->nextFolder = p;
			p->preFolder = currentFolder;
			p->folderCreateTime = tmp;
			p->folderAlterTime = tmp;
		}
		cout << "目录创建成功！" << endl;
	}
	else
	{
		cout << "不能在空目录下创建文件!！" << endl;
	}
	return currentFolder;

}

//新建文件
int FileSystem::newFile()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	File *p = new File();
	cin >> p->fileName;
	if (currentFolder != NULL)
	{
		//检查有无同名
		if (currentFolder->filePtr==NULL)
		{
			currentFolder->filePtr = p;
			p->fileCreateTime = tmp;
			p->fileAlterTime = tmp;
		}
		else
		{
			File *q = new File();
			q = currentFolder->filePtr;
			while (q->nextFile!=NULL)
			{
				if (!strcmp(p->fileName.c_str(),q->fileName.c_str()))
				{
					cout<<"该文件已创建，无需重新创建"<<endl;
					return 0;
				}
				q = q->nextFile;
			}
			if (!strcmp(p->fileName.c_str(), q->fileName.c_str()))
			{
				cout << "该文件已创建，无需重新创建" << endl;
				return 0;
			}
			q->nextFile = p;
			p->fileCreateTime = tmp;
			p->fileAlterTime = tmp;
		}
		cout<<"文件创建成功"<<endl;
	}
	else
	{
		cout<<"空目录下不能创建文件"<<endl;
	}
	return 1;

	
}
//显示当前目录的文件
int FileSystem::showFolder()
{
	int folderSize = 0, fileSize = 0;
	Folder *d = new Folder();
	d = currentFolder->folderPtr;
	File *f = new File();
	f = currentFolder->filePtr;
	char buf[10];
	string str;
	if (d == NULL && f == NULL)
	{
		cout << "空目录" << endl;
		return 0;
	}
	Folder *d1 = new Folder();
	File *d2 = new File();

	//遍历当前目录
	while (d!=NULL)
	{
		d1 = d->folderPtr;
		d2 = d->filePtr;
		while (d1!=NULL)
		{
			//目录个数
			folderSize++;
			d1 = d1->nextFolder;
		}
		while (d2!=NULL)
		{
			//文件个数
			fileSize++;
			d2 = d2->nextFile;
		}
		d->folderSize = (folderSize + fileSize);
		itoa(d->folderSize, buf, 10);
		str = buf;
		cout << d->folderCreateTime.substr(0,10)<<"  "<<d->folderCreateTime.substr(11, 5) << "    <DIR>" << string(10 - str.length(), ' ') << d->folderSize <<" "<< d->folderName << string(14 - (d->folderName.length()), ' ')<< endl;
		d = d->nextFolder;
		folderSize = 0;
		fileSize = 0;

	}
	//cout << endl;
	//cout << " 文件名称      " << "文件大小         " << "文件内容           " << "创建时间           " << "文件属性";
	//cout << endl;

	while (f!=NULL)
	{
		itoa(f->fileSize, buf, 10);
		str = buf;
		if (f->rw)
			cout << f->fileCreateTime.substr(0, 10) << "  " << f->fileCreateTime.substr(11, 5) << "         " << string(10 - str.length(), ' ') << f->fileSize << " " << f->fileName << string(14 - (f->fileName.length()), ' ') << endl;
			//cout << "    " << f->fileName << string(15 - (f->fileName.length()), ' ') << f->fileSize << string(18 - f->fileContent.length(), ' ') << f->fileContent << string(10 - str.length(), ' ') << f->fileCreateTime << "     只读" << endl;
		else
			cout << f->fileCreateTime.substr(0, 10) << "  " << f->fileCreateTime.substr(11, 5) << "         " << string(10 - str.length(), ' ') << f->fileSize << " " << f->fileName << string(14 - (f->fileName.length()), ' ') << endl;
			//cout << "    " << f->fileName << string(15 - (f->fileName.length()), ' ') << f->fileSize << string(18 - f->fileContent.length(), ' ') << f->fileContent << string(10 - str.length(), ' ') << f->fileCreateTime << "    可读可写" << endl;
		f = f->nextFile;
	}
	return 1;


}
//
Folder* FileSystem::openFolder()
{
	Folder *d = new Folder();
	cin >> d->folderName;
	int flag = 0;
	//FileSystem *fs = new FileSystem;

	if (d->folderName=="..")
	{
		goback();
	}
	else
	{
		if (currentFolder == NULL)
		{
			cout << "系统找不到指定路径。" << endl;
		}
		else
		{
			if (currentFolder->folderPtr == NULL)
			{
				cout << "系统找不到指定路径。" << endl;
			}
			else
			{
				Folder *q = new Folder();
				q = currentFolder->folderPtr;
				while (q != NULL)
				{
					if (!strcmp(d->folderName.c_str(), q->folderName.c_str()))
					{
						currentFolder = q;
						flag++;
						break;
					}
					q = q->nextFolder;
				}

				if (!flag)
				{
					cout << "系统找不到指定路径。" << endl;
				}
			}
		}
		return currentFolder;
	}

	
}

//返回上一层
Folder* FileSystem::goback()
{
	int flag = 0;
	if (currentFolder != NULL)
	{
		if (currentFolder==root)
		{
			cout<<"无目录返回"<<endl;
		}
		else
		{
			currentFolder = currentFolder->preFolder;
		}
	}
	else
	{
		cout<<"无目录返回"<<endl;
	}
	return currentFolder;
}

//
void FileSystem::display()
{
	vector<Folder*> v;
	int flag = 0;

	Folder *p = new Folder();
	p = root;
	if (p == currentFolder)
	{
		cout << "\nH:\\" << p->folderName << ">";
	}
	else
	{
		cout << "\nH:" << p->folderName;
		Folder *q = new Folder();
		q = currentFolder;
		while (q != NULL)
		{
			v.push_back(q);
			q = q->preFolder;
		}
		for (int i = 0; i < v.size(); i++)
		{
			if (i == 0) cout << v[v.size() - 1 - i]->folderName;
			else cout << "\\" << v[v.size() - 1 - i]->folderName;
		}
		cout << ">";

	}
	v.clear();

}
//目录重命名
int FileSystem::renameFolder()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	Folder *p = new Folder();
	cin >> p->folderName;
	Folder *q = new Folder();
	cin >> q->folderName;
	int flag = 0, flag1 = 0;
	if (currentFolder->folderPtr == NULL)
		cout << "当前路径下不存在目录!" << endl;
	else
	{
		Folder *ptr = new Folder();
		ptr = currentFolder->folderPtr;
		Folder *ptr1 = new Folder();
		ptr1 = currentFolder->folderPtr;
		while (ptr != NULL)
		{
			if (ptr->folderName == p->folderName)
			{
				flag++;
				while (ptr1 != NULL)
				{
					if (ptr1->folderName == q->folderName)
					{
						flag1++;
						break;
					}
					ptr1 = ptr1->nextFolder;
				}
				if (!flag1)
				{
					ptr->folderName = q->folderName;
					ptr->folderAlterTime = tmp;
				}
				break;
			}

			ptr = ptr->nextFolder;
		}

		if (!flag)
			cout << "不存在指定要重命名的目录!" << endl;
		if (flag)
		{
			if (flag1)
				cout << "存在一个重名文件。" << endl;
			else
				cout << "目录重命名成功！" << endl;
		}
	}
	return 1;
}

//删除目录
int FileSystem::deleteFolder()
{
	Folder *p = new Folder();
	cin >> p->folderName;
	int flag = 0;
	if (currentFolder->folderPtr == NULL)
	{
		cout<<"当前目录下不存在目录"<<endl;
	}
	else
	{
		Folder *q = new Folder();
		q = currentFolder->folderPtr;
		if (q->nextFolder == NULL)
		{
			if (q->folderName == p->folderName)
			{
				if (q->folderPtr == NULL)
				{
					//删除文件
					deleteFileInFolder(q);
					currentFolder->folderPtr = NULL;
				}
				else
				{
					deleteFileInFolder(q);
					delete_Folder(q->folderPtr);
					q->folderPtr = NULL;
					currentFolder->folderPtr = NULL;
				}
				flag++;
			}
		}
		//下一个目录不为空
		else
		{
			if (q->folderName == p->folderName)
			{
				flag++;

				if (q->folderPtr == NULL)
				{
					deleteFileInFolder(q);
					currentFolder->folderPtr = q->nextFolder;
				}
				else
				{
					deleteFileInFolder(q);
					delete_Folder(q->folderPtr);
					q->folderPtr = NULL;
					currentFolder->folderPtr = q->nextFolder;
				}
			}
			else
			{
				while (q->nextFolder!=NULL)
				{
					if (q->nextFolder->folderName == p->folderName)
					{
						if (q->nextFolder->folderPtr == NULL)
						{
							deleteFileInFolder(q->nextFolder);
							q->nextFolder = q->nextFolder->nextFolder;
						}
						else
						{
							deleteFileInFolder(q->nextFolder);
							delete_Folder(q->nextFolder->folderPtr);
							q->nextFolder->folderPtr = NULL;
							q->nextFolder = q->nextFolder->nextFolder;
						}
						flag++;
						break;
					}
					q = q->nextFolder;
				}
			}
		}
		if (flag)
		{
			cout<<"目录删除成功！"<<endl;
		}
		else 
		{
			cout<<"目录不存在！"<<endl;
		}
	}
	return 1;
}
int FileSystem::deleteFileInFolder(Folder *Folder)
{
	if (Folder->filePtr != NULL)
	{
		Folder->filePtr = NULL;
	}
	return 1;
}
int FileSystem::delete_Folder(Folder *Folder)
{
	if (Folder->folderPtr!=NULL)
	{
		delete_Folder(Folder->folderPtr);
	}
	if (Folder->nextFolder!=NULL)
	{
		delete_Folder(Folder->nextFolder);
	}
	delete Folder;
	return 1;
}

//删除文件
int FileSystem::deleteFile()
{
	File *p = new File();
	cin >> p->fileName;
	int flag = 0;
	if (currentFolder->filePtr==NULL)
	{
		cout<<"当前目录下不存在文件"<<endl;
	}
	else
	{
		File *q = new File();
		q = currentFolder->filePtr;
		if (q->nextFile==NULL)
		{
			if (q->fileName == p->fileName)
			{
				currentFolder->filePtr = NULL;
				flag++;
			}
		}
		else
		{
			if (q->fileName==p->fileName)
			{
				currentFolder->filePtr = q->nextFile;
				flag++;
			}
			else
			{
				while (q->nextFile!=NULL)
				{
					if (q->nextFile->fileName == p->fileName)
					{
						q->nextFile = q->nextFile->nextFile;
						flag++;
						break;
					}
					q = q->nextFile;
				}
			}
		}
		if (flag)
			cout << "文件删除成功" << endl;
		else
			cout<<"不存在该文件"<<endl;
	}
	return 1;
}
//文件重命名
int FileSystem::renameFile()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	File *p = new File();
	cin >> p->fileName;
	File *q = new File();
	cin >> q->fileName;

	int flag = 0, flag1 = 0;
	if (currentFolder->filePtr == NULL)
		cout<<"找不到指定文件"<<endl;
	else
	{
		File *ptr = new File();
		ptr = currentFolder->filePtr;
		File *ptr1 = new File();
		ptr1 = currentFolder->filePtr;
		while (ptr!=NULL)
		{
			if (ptr->fileName==p->fileName)
			{
				flag++;
				while (ptr1!=NULL)
				{
					if (ptr1->fileName==q->fileName)
					{
						flag1++;
						break;
					}
					ptr1 = ptr->nextFile;
				}
				if (!flag1)
				{
					ptr->fileName = q->fileName;
					ptr->fileAlterTime = tmp;
				}
				break;
			}
			ptr = ptr->nextFile;
		}
		
		if (flag)
		{
			if (flag1)
			{
				cout<< "文件重命名失败" <<endl;
			}
			else
			{
				cout<<"文件重命名成功"<<endl;
			}
		}
		else
		{
			cout << "重命名文件不存在" << endl;
		}
	}

	return 1;
}
//拷贝文件
int FileSystem::copyFile()
{
	File *p = new File();
	cin >> p->fileName;
	int flag = 0;
	tempfile = new File();
	if (currentFolder->filePtr == NULL)
		cout << "当前路径下不存在文件!" << endl;
	else
	{
		File *q = new File();
		q = currentFolder->filePtr;

		while (q->nextFile != NULL)
		{
			if (q->nextFile->fileName == p->fileName)
			{
				tempfile = q->nextFile;

				flag++;
				break;
			}
			else {}
			q = q->nextFile;
		}
		if (currentFolder->filePtr->fileName == p->fileName)
		{
			tempfile = currentFolder->filePtr;
			flag++;
		}
		if (flag)
			cout << "文件复制成功！" << endl;
		else
			cout << "不存在指定要复制的文件!" << endl;
	}

	return 1;

}
//粘贴文件
int FileSystem::pasteFile()
{
	int flag = 0;
	if (tempfile == NULL)
	{
		cout << "复制文件不存在，粘贴失败!" << endl;
		return 0;
	}
	//1.复制了 2.当前fileptr空的，直接paste进来
	if (currentFolder->filePtr == NULL)
	{
		currentFolder->filePtr = new File();
		currentFolder->filePtr->fileCreateTime = tempfile->fileCreateTime;
		currentFolder->filePtr->fileContent = tempfile->fileContent;
		currentFolder->filePtr->fileName = tempfile->fileName;
		currentFolder->filePtr->fileSize = tempfile->fileSize;
		cout << "粘贴文件成功!" << endl;
	}
	else
	{

		File *q = new File();
		q = currentFolder->filePtr;

		while (q->nextFile != NULL)
		{
			if (q->fileName == tempfile->fileName)
			{
				flag++;
				break;
			}
			q = q->nextFile;
			//检验 给flag
			if (q->nextFile == NULL && q->fileName == tempfile->fileName)
			{
				flag++;
			}
		}
		//判断链表第一个文件是否与要粘贴的同名
		if (currentFolder->filePtr->fileName == tempfile->fileName)
		{
			flag++;
		}

		if (!flag)
		{
			//最后节点交给temp
			q->nextFile = new File();
			q->nextFile->fileCreateTime = tempfile->fileCreateTime;
			q->nextFile->fileContent = tempfile->fileContent;
			q->nextFile->fileName = tempfile->fileName;
			q->nextFile->fileSize = tempfile->fileSize;
			cout << "文件粘贴成功！" << endl;

		}
		else
			cout << "当前文件已存在!" << endl;
	}


	return 1;

}

int FileSystem::saveCmd()
{
	char tmp[64];
	cin >> tmp;
	ofstream out(tmp);

	if (out.is_open())
	{
		int folderSize = 0, fileSize = 0;
		Folder *d = new Folder();
		d = root->folderPtr;
		File *f = new File();
		f = root->filePtr;
		char buf[10]="___";

		//遍历目录
		while (d != NULL)
		{
			out << "dir"<<buf<<"folderName"<< d->folderName <<buf<< d->folderCreateTime <<"\n";
			d = d->nextFolder;
		}
		while (f != NULL)
		{
			out << "file"<<buf<< f->fileName <<buf<< f->fileCreateTime<<buf<< f->fileContent<< "\n";
			f = f->nextFile;
		}
		out.close();
	}
	return 1;

}


vector<string> splitStr(string& str, string& delimiter)
{
	vector<string> v;

	size_t pos = 0;
	std::string token;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		v.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	v.push_back(str);
	return v;
}

int FileSystem::loadCmd()
{
	string tmp;
	cin >> tmp;
	ifstream in(tmp);


	string split="___";
	string line;
	vector<string> v;

	char buffer[256];
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!in.eof())
	{
		while (getline(in, line))
		{
			vector<string> v = splitStr(line, split);
			Folder *p = new Folder();
			p->folderName = v[1];
			p->folderCreateTime = v[2];
			p->folderAlterTime = v[2];
			p->preFolder=currentFolder;
			


			cout << line << endl;

			//in.getline(buffer, 100);
			//cout << buffer << endl;
		}
	}
	in.close();
	return 1;
}

//
//int FileSystem::copyFolder()
//{
//
//}
//
//int FileSystem::pasteFolder()
//{
//
//}
//
//int FileSystem::subPasteFolder(Folder *folder1, Folder *folder2)
//{
//
//}
//
//int FileSystem::pasteFileInFolder(File file, Folder *folder)
//{
//
//}
