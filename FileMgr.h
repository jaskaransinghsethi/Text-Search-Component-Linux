//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileMgr.h      : A component responsible for searching all files matching a given pattern in a given path	//
// ver 1.0																										//
// Application    : CSE-775 Project 1																	        //
// Platform       : Visual Studio Code for Linux															    //
//                  Ubuntu18041 64 bit, Acer Aspire R5-571TG												    //
// Author         : Jaskaran Singh, EECS Department, Syracuse University									    //
//                  315-925-9941, jsingh09@syr.edu																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This componenet is responsible for searching all files matching a given pattern in a given path.
 *
 * Public Interface:
 * -----------------
 * IFileMgr *pFileMgr = createFileMgr();					//Creating a pointer of IFileMgr type which points to FileMgr component
 * pFileMgr->getArguments(path_, patterns_);				//A function to set a given path and a pattern in a FileMgr component
 * pFileMgr->findAllFiles();								//A function which finds all the files in a given path matching a given pattern
 * ptrIFile->returnFiles(&files_);							//A function which returns all files in a given path matching a given pattern
 *
 * Required File:
 * --------------
 * IFileMgr.h, FileMgr.h, FileMgr.cpp
 * dllmain.h, dllmain.cpp
 * FileSystem.h, FileSystem.cpp
 *
 * Maintenance History:
 * --------------------
 * -April 8th, 2019
 *  first release
 */

#ifndef FILEMGR_H
#define FILEMGR_H

#include "IFileMgr.h"
#include <string>
#include <vector>
#include "FileSystem.h"
#include <algorithm>

class FileMgr : public IFileMgr
{
public:
	FileMgr();
	~FileMgr();
	void getArgs(std::string path, std::vector<std::string> patterns) override;
	bool findAllFiles() override;
	void returnfiles(std::vector<std::string> &files_) override;
private:
	Files files;
	std::string path_;
	std::vector<std::string> patterns_;
};
#endif
