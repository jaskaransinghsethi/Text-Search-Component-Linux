//////////////////////////////////////////////////////////////////////////////////
// Client.cpp     : To demonstrate all the requirements of this project         //
// ver 1.0																		//
//																				//
// Application    : CSE-775 Project 1					                        //
// Platform       : Visual Studio Code for Linux		                        //
//                  Ubuntu18041 64 bit, Acer Aspire R5-571TG				    //
// Author         : Jaskaran Singh, EECS Department, Syracuse University        //
//                  315-925-9941, jsingh09@syr.edu							    //
//////////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This package demonstrates all the functionalities of this project.
 *
 * Required File:
 * --------------
 * IFileMgr.h								//FileMgr header file created by ATL Libraries
 * ITextSearchComp.h						//TextSearch header file created by ATL Libraries
 * CodeUtilities.h, CodeUtilities.cpp		//Helper class to process command line arguments
 * StringUtilities.h, StringUtilities.cpp	//Helper class for string convertions
 *
 * Maintenance History:
 * --------------------
 * -April 7th, 2019
 *  first release
 */

#include "CodeUtilities.h"
#include "StringUtilities.h"
#include "ITextSearchComp.h"
#include "IFileMgr.h"
#include <iostream>
#include <string>
#include <dlfcn.h>
#include <vector>
#include <unordered_map>

using namespace Utilities;

//A function which is invoked in case user pass invalid commandline arguments
std::string customUsage(){
	std::string usage;
	usage += "\n  Command Line: path [/pattern]* [/Regex for String]";
	usage += "\n    path is relative or absolute path where processing begins";
	usage += "\n    [pattern]* are one or more pattern strings of the form:";
	usage += "\n      *.h *.cpp *.cs *.txt or *.*";
	usage += "\n    [/Regex] is a string to be search in the set of given files";
	usage += "\n";
	return usage;
}

//A function to process commandline arguments and to display them on the console
void processCmdLine(ProcessCmdLine &pcl) {

	pcl.usage(customUsage());

	preface("Command Line:   "); pcl.showCmdLine();
	preface("path:           "); pcl.showPath();
	preface("Patterns:       "); pcl.showPatterns();
	preface("Regexes:        "); pcl.showRegexes();
	std::cout << "\n";
	putline();
}

//A function to display the output on to the console
void parseOutput(std::unordered_map<std::string, std::vector<int>> locations_) {
	auto iter = locations_.begin();
	while (iter != locations_.end()) {
		std::string name = iter->first;
		name += ":-";
		std::cout << "\n" << name;
		std::string lines = "";
		for (size_t i = 0; i < iter->second.size(); i++) {
			size_t lineno = iter->second[i];
			std::cout << " " << lineno;
		}
		iter++;
	}
}

//Main function to show the functionalities of the project
int main(int argc, char** argv) {
	std::cout << "\n================= Client Demonstration ======================";
	ProcessCmdLine cmdargs(argc, argv);
	cmdargs.usage(customUsage());
	if (cmdargs.parseError())
	{
		std::cout << "\n Command line parse error";
		cmdargs.usage();
		std::cout << "\n\n";
		getchar();
		return -1;
	}
	processCmdLine(cmdargs);
	
	void* hToFileMgr = dlopen("./FileMgr.so", RTLD_LAZY);
	if (!hToFileMgr)
	{
		std::cout << "\n  Failed to load FileMgr.so\n\n";
		return 1;
	}

	typedef IFileMgr*(*pToFMgr)();
  	pToFMgr pToFMgr_ = (pToFMgr)dlsym(hToFileMgr, "createFileMgr");
	if (!pToFMgr_)
	{
		std::cout << "\n  Failed to create FileMgr object\n\n";
		return 1;
	}

	IFileMgr* ptoFileMgr = pToFMgr_();
	ptoFileMgr->getArgs(cmdargs.path(), cmdargs.patterns());

	void* hToTextSearch = dlopen("./TextSearchComp.so", RTLD_LAZY);
	if (!hToTextSearch)
	{
		std::cout << "\n  Failed to load TextSearchComp\n\n";
		return 1;
	}
	typedef ITextSearchComp*(*ofITextSearch)();
	ofITextSearch pToIText = (ofITextSearch)dlsym(hToTextSearch, "createTextSearch");
	if (!pToIText)
	{
		std::cout << "\n  Failed to create TextSearch object\n\n";
		return 1;
	}
	std::string rExp = cmdargs.regexes()[0];
	ITextSearchComp *pToITextSearch = pToIText();
	pToITextSearch->getpToFileMgr(ptoFileMgr);
	pToITextSearch->textSearchHelper(rExp);
	std::unordered_map<std::string, std::vector<int>> locations = pToITextSearch->returnLocations();
	parseOutput(locations);
	dlclose(hToTextSearch);
	dlclose(hToFileMgr);
	std::cout << "\n\n";
}