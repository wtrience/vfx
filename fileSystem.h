#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "fileAndFolder.h"

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	//目录
	Folder* newFolder();
	int deleteFolder();
	Folder* openFolder();
	int renameFolder();
	int copyFolder();
	int pasteFolder();
	int subPasteFolder(Folder *folder1, Folder *folder2);
	Folder* goback();
	int deleteFileInFolder(Folder *Folder);
	int delete_Folder(Folder *Folder);

	//文件
	int newFile();
	int deleteFile();
	// int readFile();
	// int writeFile();
	int renameFile();
	int copyFile();
	int pasteFile();
	int pasteFileInFolder(File file, Folder *folder);
	int showFolder();
	void display();

private:
	Folder * root;
	Folder * currentFolder;
	File * tempfile;
	Folder * tempfolder;

};

#endif

