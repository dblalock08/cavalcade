// FileParser.h
#pragma once

#include <string>
using namespace std;

class FileParser
{
public:
	FileParser();
	FileParser(const FileParser&);
	~FileParser();

	void Reset();	// Resets the parser

	void SetStream(char* stream);	// Load the parser with text to be parsed
	bool GetNextToken(string* buffer, char* delimiters, int totalDelimiters);
	bool NextLine(string* buffer);

private:
	int m_startIndex;
	int m_endIndex;
	string m_data;
};