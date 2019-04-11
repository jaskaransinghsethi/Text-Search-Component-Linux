//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// IFileMgr.h    : A component responsible for searching all files matching a given pattern in a given path		//
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
 * Interface to FileMgr component to hide details from the client
 *
 * Required File:
 * --------------
 * IFileMgr.h, FileMgr.h, FileMgr.cpp
 * FileSystem.h, FileSystem.cpp
 *
 * Maintenance History:
 * --------------------
 * -April 8th, 2019
 *  first release
 */

#pragma once
#include<string>
#include<vector>

class IFileMgr {
public:
	using File = std::string;
	using Files = std::vector<File>;
	virtual void getArgs(std::string path, std::vector<std::string> patterns) = 0;
	virtual bool findAllFiles() = 0;
	virtual void returnfiles(std::vector<std::string> &files_) = 0;
	virtual ~IFileMgr() { };
};

//Object factory for FileMgr
extern "C"{
	IFileMgr* createFileMgr();
}