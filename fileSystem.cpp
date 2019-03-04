#include "fileSystem.h"
#include "fileAndFolder.h"
#include "command.h"

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
//
//
////新建文件
//int FileSystem::newFile()
//{
//
//}
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
	cout << endl;
	cout << d->folderName<<"的目录" << endl;
	cout << endl;
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
	cout << endl;
	cout << " 文件名称      " << "文件大小         " << "文件内容           " << "创建时间           " << "文件属性";
	cout << endl;

	while (f!=NULL)
	{
		itoa(f->fileSize, buf, 10);
		str = buf;
		if (f->rw)
			cout << "    " << f->fileName << string(15 - (f->fileName.length()), ' ') << f->fileSize << string(18 - f->fileContent.length(), ' ') << f->fileContent << string(10 - str.length(), ' ') << f->fileCreateTime << "     只读" << endl;
		else
			cout << "    " << f->fileName << string(15 - (f->fileName.length()), ' ') << f->fileSize << string(18 - f->fileContent.length(), ' ') << f->fileContent << string(10 - str.length(), ' ') << f->fileCreateTime << "    可读可写" << endl;
		f = f->nextFile;
	}
	return 1;


}
////
//Folder* FileSystem::openFolder()
//{
//
//}
////
//Folder* FileSystem::goback()
//{
//
//}

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
		cout << "\nf:" << p->folderName;
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
/*
//
int FileSystem::deleteFolder()
{

}
//
int FileSystem::deleteFileInFolder()
{

}

//
int FileSystem::deleteFile()
{

}
//
int FileSystem::renameFile()
{

}

int FileSystem::renameFolder()
{

}

int FileSystem::copyFile()
{

}

int FileSystem::pasteFile()
{

}

int FileSystem::copyFolder()
{

}

int FileSystem::pasteFolder()
{

}

int FileSystem::subPasteFolder(Folder *folder1, Folder *folder2)
{

}

int FileSystem::pasteFileInFolder(File file, Folder *folder)
{

}

*/

