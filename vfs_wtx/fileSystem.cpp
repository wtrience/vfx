#include "fileSystem.h"
#include "fileAndFolder.h"
#include "command.h"

#include<fstream>

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

//�½�Ŀ¼
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
		else//��Ŀ¼��Ŀ¼����ָ�벻Ϊ��
		{
			//��ָ�����ڱ���
			Folder *q;
			q = currentFolder->folderPtr;
			while (q->nextFolder != NULL)
			{
				if (!strcmp(p->folderName.c_str(), q->folderName.c_str()))//�ļ���ͬ��
				{
					cout << "ͬ��Ŀ¼����������" << endl;
					cout << "ͬ��Ŀ¼��������999��" << endl;
					return 0;
				}

				q = q->nextFolder;
			}
			if (!strcmp(p->folderName.c_str(), q->folderName.c_str()))
			{
				cout << "ͬ��Ŀ¼����������" << endl;
				return 0;
			}
			q->nextFolder = p;
			p->preFolder = currentFolder;
			p->folderCreateTime = tmp;
			p->folderAlterTime = tmp;
		}
		cout << "Ŀ¼�����ɹ���" << endl;
	}
	else
	{
		cout << "�����ڿ�Ŀ¼�´����ļ�!��" << endl;
	}
	return currentFolder;

}

//�½��ļ�
int FileSystem::newFile()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d %X", localtime(&t));

	File *p = new File();
	cin >> p->fileName;
	if (currentFolder != NULL)
	{
		//�������ͬ��
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
					cout<<"���ļ��Ѵ������������´���"<<endl;
					return 0;
				}
				q = q->nextFile;
			}
			if (!strcmp(p->fileName.c_str(), q->fileName.c_str()))
			{
				cout << "���ļ��Ѵ������������´���" << endl;
				return 0;
			}
			q->nextFile = p;
			p->fileCreateTime = tmp;
			p->fileAlterTime = tmp;
		}
		cout<<"�ļ������ɹ�"<<endl;
	}
	else
	{
		cout<<"��Ŀ¼�²��ܴ����ļ�"<<endl;
	}
	return 1;

	
}
//��ʾ��ǰĿ¼���ļ�
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
		cout << "��Ŀ¼" << endl;
		return 0;
	}
	Folder *d1 = new Folder();
	File *d2 = new File();

	//������ǰĿ¼
	//cout << endl;
	//cout << endl;
	while (d!=NULL)
	{
		d1 = d->folderPtr;
		d2 = d->filePtr;
		while (d1!=NULL)
		{
			//Ŀ¼����
			folderSize++;
			d1 = d1->nextFolder;
		}
		while (d2!=NULL)
		{
			//�ļ�����
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
	//cout << " �ļ�����      " << "�ļ���С         " << "�ļ�����           " << "����ʱ��           " << "�ļ�����";
	//cout << endl;

	while (f!=NULL)
	{
		itoa(f->fileSize, buf, 10);
		str = buf;
		if (f->rw)
			cout << f->fileCreateTime.substr(0, 10) << "  " << f->fileCreateTime.substr(11, 5) << "         " << string(10 - str.length(), ' ') << f->fileSize << " " << f->fileName << string(14 - (f->fileName.length()), ' ') << endl;
			//cout << "    " << f->fileName << string(15 - (f->fileName.length()), ' ') << f->fileSize << string(18 - f->fileContent.length(), ' ') << f->fileContent << string(10 - str.length(), ' ') << f->fileCreateTime << "     ֻ��" << endl;
		else
			cout << f->fileCreateTime.substr(0, 10) << "  " << f->fileCreateTime.substr(11, 5) << "         " << string(10 - str.length(), ' ') << f->fileSize << " " << f->fileName << string(14 - (f->fileName.length()), ' ') << endl;
			//cout << "    " << f->fileName << string(15 - (f->fileName.length()), ' ') << f->fileSize << string(18 - f->fileContent.length(), ' ') << f->fileContent << string(10 - str.length(), ' ') << f->fileCreateTime << "    �ɶ���д" << endl;
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
			cout << "ϵͳ�Ҳ���ָ��·����" << endl;
		}
		else
		{
			if (currentFolder->folderPtr == NULL)
			{
				cout << "ϵͳ�Ҳ���ָ��·����" << endl;
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
					cout << "ϵͳ�Ҳ���ָ��·����" << endl;
				}
			}
		}
		return currentFolder;
	}

	
}

//������һ��
Folder* FileSystem::goback()
{
	int flag = 0;
	if (currentFolder != NULL)
	{
		if (currentFolder==root)
		{
			cout<<"��Ŀ¼����"<<endl;
		}
		else
		{
			currentFolder = currentFolder->preFolder;
		}
	}
	else
	{
		cout<<"��Ŀ¼����"<<endl;
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
//Ŀ¼������
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
		cout << "��ǰ·���²�����Ŀ¼!" << endl;
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
			cout << "������ָ��Ҫ��������Ŀ¼!" << endl;
		if (flag)
		{
			if (flag1)
				cout << "����һ�������ļ���" << endl;
			else
				cout << "Ŀ¼�������ɹ���" << endl;
		}
	}
	return 1;
}

//ɾ��Ŀ¼
int FileSystem::deleteFolder()
{
	Folder *p = new Folder();
	cin >> p->folderName;
	int flag = 0;
	if (currentFolder->folderPtr == NULL)
	{
		cout<<"��ǰĿ¼�²�����Ŀ¼"<<endl;
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
					//ɾ���ļ�
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
		//��һ��Ŀ¼��Ϊ��
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
			cout<<"Ŀ¼ɾ���ɹ���"<<endl;
		}
		else 
		{
			cout<<"Ŀ¼�����ڣ�"<<endl;
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

//ɾ���ļ�
int FileSystem::deleteFile()
{
	File *p = new File();
	cin >> p->fileName;
	int flag = 0;
	if (currentFolder->filePtr==NULL)
	{
		cout<<"��ǰĿ¼�²������ļ�"<<endl;
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
			cout << "�ļ�ɾ���ɹ�" << endl;
		else
			cout<<"�����ڸ��ļ�"<<endl;
	}
	return 1;
}
//�ļ�������
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
		cout<<"�Ҳ���ָ���ļ�"<<endl;
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
				cout<< "�ļ�������ʧ��" <<endl;
			}
			else
			{
				cout<<"�ļ��������ɹ�"<<endl;
			}
		}
		else
		{
			cout << "�������ļ�������" << endl;
		}
	}

	return 1;
}
//�����ļ�
int FileSystem::copyFile()
{
	File *p = new File();
	cin >> p->fileName;
	int flag = 0;
	tempfile = new File();
	if (currentFolder->filePtr == NULL)
		cout << "��ǰ·���²������ļ�!" << endl;
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
			cout << "�ļ����Ƴɹ���" << endl;
		else
			cout << "������ָ��Ҫ���Ƶ��ļ�!" << endl;
	}

	return 1;

}
//ճ���ļ�
int FileSystem::pasteFile()
{
	int flag = 0;
	if (tempfile == NULL)
	{
		cout << "�����ļ������ڣ�ճ��ʧ��!" << endl;
		return 0;
	}
	//1.������ 2.��ǰfileptr�յģ�ֱ��paste����
	if (currentFolder->filePtr == NULL)
	{
		currentFolder->filePtr = new File();
		currentFolder->filePtr->fileCreateTime = tempfile->fileCreateTime;
		currentFolder->filePtr->fileContent = tempfile->fileContent;
		currentFolder->filePtr->fileName = tempfile->fileName;
		currentFolder->filePtr->fileSize = tempfile->fileSize;
		cout << "ճ���ļ��ɹ�!" << endl;
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
			//���� ��flag
			if (q->nextFile == NULL && q->fileName == tempfile->fileName)
			{
				flag++;
			}
		}
		//�ж������һ���ļ��Ƿ���Ҫճ����ͬ��
		if (currentFolder->filePtr->fileName == tempfile->fileName)
		{
			flag++;
		}

		if (!flag)
		{
			//���ڵ㽻��temp
			q->nextFile = new File();
			q->nextFile->fileCreateTime = tempfile->fileCreateTime;
			q->nextFile->fileContent = tempfile->fileContent;
			q->nextFile->fileName = tempfile->fileName;
			q->nextFile->fileSize = tempfile->fileSize;
			cout << "�ļ�ճ���ɹ���" << endl;

		}
		else
			cout << "��ǰ�ļ��Ѵ���!" << endl;
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

		//����Ŀ¼
		while (d != NULL)
		{
			out << "dir"<<buf<< d->folderName <<buf<< d->folderCreateTime <<"\n";
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

int FileSystem::loadCmd()
{
	char tmp[64];
	cin >> tmp;
	ifstream in(tmp);

	string line;
	vector<string> v;

	char buffer[256];
	if (!in.is_open())
	{
		cout << "Error opening file"; exit(1);
	}
	while (!in.eof())
	{
		while (getline(in,line))
		{
			cout << line << endl;
		}





		//in.getline(buffer, 100);
		//cout << buffer << endl;
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

