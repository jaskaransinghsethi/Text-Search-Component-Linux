//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FileMgr.cpp    : A component responsible for searching all files matching a given pattern in a given path	//
// ver 1.0																										//
// Application    : CSE-775 Project 1																	        //
// Platform       : Visual Studio Code for Linux															    //
//                  Ubuntu18041 64 bit, Acer Aspire R5-571TG												    //
// Author         : Jaskaran Singh, EECS Department, Syracuse University									    //
//                  315-925-9941, jsingh09@syr.edu																//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FileMgr.h"

using namespace FileSystem;

//Default Constructor
FileMgr::FileMgr()
{
}

//Default Destructor
FileMgr::~FileMgr()
{
}

//A function to set a given path and a pattern in a FileMgr component
void FileMgr::getArgs(std::string path, std::vector<std::string> patterns)
{
	path_ = path;
	for (std::string p : patterns)
		patterns_.push_back(p);
}

//A function which finds all the files in a given path matching a given pattern
bool FileMgr::findAllFiles() {
	std::string fpath = FileSystem::Path::getFullFileSpec(path_);

	for (auto patt : patterns_)
	{
		std::vector<std::string> ffiles = FileSystem::Directory::getFiles(fpath, patt);
		for (auto f : ffiles)
		{
			files.push_back(fpath + f);
		}
	}

	std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
	for (auto d : dirs)
	{
		if (d == ".vscode" || d == "..")
			continue;
		path_ = fpath + d;
		findAllFiles();   // recurse into subdirectories

	}

	return true;
}

//A function which returns all files in a given path matching a given pattern
void FileMgr::returnfiles(std::vector<std::string> &files_)
{
	for (std::string f : files)
		files_.push_back(f);
}

//Object factory which creates an instance of FileMgr
IFileMgr* createFileMgr()
{
	return new FileMgr;
}

//Test stub for FileMgr
//#define TEST_FILEMGR
#ifdef TEST_FILEMGR
int main() {
	std::vector<std::string> patterns;
	patterns.push_back("*.*");
	std::string path = "../../";
	IFileMgr *instance = createFileMgr();
	instance->getArgs(path, patterns);
	instance->findAllFiles();
	std::vector<std::string> files;
	instance->returnfiles(files);
	getchar();
	return 0;
}
#endif