// Tokenizer.h
#pragma once

#include <string>
using namespace std;

class Tokenizer
{
public:
	Tokenizer();
	Tokenizer(const Tokenizer&);
	~Tokenizer();

	void SetStream(char* data);
	void ResetStream();

	bool GetNextToken(string* tokenBuffer, char* delimiters, int totalDelimiters);
	bool MoveToNextLine(string* buffer);
	
private:
	int m_start, m_end;
	string m_data;
};