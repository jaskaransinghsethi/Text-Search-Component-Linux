//////////////////////////////////////////////////////////////////////////////////////////////////////////
// ITextSearch.h  : A component responsible for searching of a given regex in a set of files			//
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

#pragma once
#include <vector>
#include<string>
#include<unordered_map>
#include "IFileMgr.h"

class ITextSearchComp {
public:
	using ListLC = std::vector<int>;
	using File = std::string;
	using Files = std::vector<File>;
	using Locations = std::unordered_map<File, ListLC>;

	virtual void searchText(std::vector<std::string> files, std::string regularExp) = 0;
	virtual Locations returnLocations() = 0;
	virtual void textSearchHelper(std::string regularExp) = 0;
	virtual void getpToFileMgr(IFileMgr *iFile) = 0;
	virtual ~ITextSearchComp() { };
};

//Object factory to create TextSearch component
extern "C"{
	ITextSearchComp* createTextSearch();
}