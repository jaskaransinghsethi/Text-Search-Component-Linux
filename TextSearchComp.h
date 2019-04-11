//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TextSearch.h   : A component responsible for searching of a given regex in a set of files			//
// ver 1.0																								//	
// Application    : CSE-775 Project 1																	//
// Platform       : Visual Studio Code for Linux														//
//                  Ubuntu18041 64 bit, Acer Aspire R5-571TG										    //
// Author         : Jaskaran Singh, EECS Department, Syracuse University								//
//                  315-925-9941, jsingh09@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * -------------------
 * This componenet is responsible for opening a given set of files by creating an instance of
 * ifstream. It then reads line by line and searches for given
 * regex. If found, adds it to the hash map.
 *
 * Public Interface:
 * -----------------
 * ITextSearchComp* pTextSearch = createTextSearch();		//Creating a pointer of ITextSearchComp type pointing to TextSearch component
 * pTextSearch->getpToFileMgr(pFileMgr);					//Getting pointer to FileMgr component
 * pTextSearch->textSearchHelper(regex_);					//Function to search for a given regular expression in a given set of files
 * pTextSearch->returnLocations();							//Function to return a map which contains the location where the regular
															  expression is found.
 *
 * Required File:
 * --------------
 * ITextSearchComp.h, TextSearchComp.h, TextSearchComp.cpp
 * FileMgr.h, FileMgr.cpp
 *
 * Maintenance History:
 * --------------------
 * -April 9th, 2019
 *  first release
 */

#ifndef TEXTSEARCHCOMP_H
#define TEXTSEARCHCOMP_H

#include "ITextSearchComp.h"
#include<vector>
#include<string>
#include<unordered_map>

class TextSearchComp : public ITextSearchComp
{
public:
	TextSearchComp();
	~TextSearchComp() override;
	void handleRegularExp(std::string regularExp, std::string text, size_t lineno, File file);
	void searchText(std::vector<std::string> files, std::string regularExp) override;
	void textSearchHelper(std::string regularExp) override;
	Locations returnLocations() override;
	void getpToFileMgr(IFileMgr *iFile) override;

private:
	Locations locations_;
	std::vector<std::string> files_;
	IFileMgr* iFile_;
};
#endif