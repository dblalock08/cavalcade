// TokenStream.h
#pragma once

#include <string>
using namespace std;

class TokenStream
{
public:
	TokenStream();
	TokenStream(const TokenStream& other);
	~TokenStream();

	void ResetStream();

	void SetTokenStream(char* data);
	bool GetNextToken(string* buffer, char* delimiters, int totalDelimiters);
	bool MoveToNextLine(string* buffer);

private:
	int m_startIndex, m_endIndex;
	string m_data;
};