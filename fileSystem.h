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
    Folder* goback();
    int deleteAllFolder(Folder *Folder);
    int deleteFileInFolder();


//文件
    int newFile();
    int deleteFile();
    // int readFile();
    // int writeFile();
    int renameFile();
    int copyFile();
    int pasteFile();
    int showFolder();
    void display();

private:
    Folder * root;
    Folder * currentFolder;
    File * tempfile;
    Folder * tempfolder;

};





#endif

