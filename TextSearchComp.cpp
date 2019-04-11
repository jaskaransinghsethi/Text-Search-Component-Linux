//////////////////////////////////////////////////////////////////////////////////////////////////////////
// TextSearch.cpp : A component responsible for searching of a given regex in a set of files			//
// ver 1.0																								//	
// Application    : CSE-775 Project 1																	//
// Platform       : Visual Studio Code for Linux														//
//                  Ubuntu18041 64 bit, Acer Aspire R5-571TG										    //
// Author         : Jaskaran Singh, EECS Department, Syracuse University								//
//                  315-925-9941, jsingh09@syr.edu														//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TextSearchComp.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace std;

//Default Constructor
TextSearchComp::TextSearchComp()
{
}

//Default Destructor
TextSearchComp::~TextSearchComp()
{
}

//A function which searches for a given regular expreession in a given file, If found adds it to the hash map
void TextSearchComp::handleRegularExp(std::string regularExp, std::string text, size_t lineno, File file) {
	smatch match;
	regex expr(regularExp);

	if (regex_search(text, match, expr)) {
		auto findFile = locations_.find(file);
		if (findFile == locations_.end())
		{
			std::vector<int> temp;
			temp.push_back(lineno);
			locations_.insert(std::pair<std::string, std::vector<int>>(file, temp));
		}
		else
		{
			findFile->second.push_back(lineno);
		}
	}

}

//A function to open set of given files using ifstream and searches for a given regular expression
void TextSearchComp::searchText(std::vector<std::string> files, std::string regularExp)
{
	ifstream in;
	string line;
	size_t lineno;
	for (size_t i = 0; i < files.size(); i++) {
		lineno = 0;
		in.open(files[i]);
		if (!in.good()) {
			cout << "\n in.good = false for file:" << files[i];
			continue;
		}

		while (getline(in, line)) {
			lineno++;
			handleRegularExp(regularExp, line, lineno, files[i]);
		}
		in.close();
	}
}

//A helper function which gets files from FileMgr
void TextSearchComp::textSearchHelper(std::string regularExp) {
	if (!iFile_->findAllFiles()) {
		std::cout << "\n Error occurred in reading file";
	}
	iFile_->returnfiles(files_);
	searchText(files_, regularExp);
} 

//A function which returns the set of location found where regular expression is found
TextSearchComp::Locations TextSearchComp::returnLocations()
{
	if (locations_.size() == 0)
		return Locations();
	else
		return locations_;
}

//A function which gets pointer to FileMgr
void TextSearchComp::getpToFileMgr(IFileMgr * iFile)
{
	iFile_ = iFile;
}

//Object factory to create TextSearch component
ITextSearchComp* createTextSearch() {
	return new TextSearchComp;
}

//Test stub for TextSearch component
#define TEST_TEXTSEARCHCOMP
#ifdef TEST_TEXTSEARCHCOMP
int main() {
	std::vector<std::string> files;
	std::vector<std::string> patterns;
	patterns.push_back("*.*");
	IFileMgr *ptoIFile = createFileMgr();
	ptoIFile->getArgs("./", patterns);
	std::string regularExp = "namespace";

	ITextSearchComp *instance = createTextSearch();
	instance->getpToFileMgr(ptoIFile);
	instance->textSearchHelper(regularExp);
	//ptoIFile->findAllFiles();
	//ptoIFile->returnfiles(files);
	TextSearchComp::Locations locations_ = instance->returnLocations();
	auto iter = locations_.begin();
	while (iter != locations_.end()) {
		cout << "\n" << iter->first;
		cout << "\n" << iter->second[0];
		iter++;
	}
	cout << "\n";
	getchar();
}
#endif

