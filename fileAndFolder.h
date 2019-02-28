#ifndef FILEANDFOLDER_H
#define FILEANDFOLDER_H

#include <iostream>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

//创建文件的结构体
typedef struct File
{
    string fCreateTime;
    string fAlterTime;
    string fileName;
    int fileSize;
    File *nextFile;
    string fContent;

    File()//初始化
    {
        fCreateTime="";
        fAlterTime="";
        fileSize=0;
        nextFile=NULL;
        fContent="";
    }
}File;

//创建文件夹的结构体
typedef struct Folder
{
    string folderCreateTime;
    string folderAlterTime;
    string folderName;
    int folderSize;
    Folder *nextFolder;
    Folder *preFolder;
    File *filePtr;
    Folder *folderPtr;

    Folder()//初始化
    {
        folderCreateTime = "";
        folderAlterTime = "";
        folderSize = 0;
        nextFolder = NULL;
        preFolder = NULL;
        filePtr = NULL;
        folderPtr = NULL;
    }
    
    Folder(string time,string name,int size,Folder *nextfolder,Folder *prefolder,File *fileptr,Folder *folderptr)//赋值
    {
        folderCreateTime = time;
        folderName = name;
        folderSize = size;
        nextFolder = nextfolder;
        preFolder = prefolder;
        filePtr = fileptr;
        folderPtr = folderptr;

    }

}Folder;
typedef struct Link
{

}Link;


#endif