/****************************************/
/* Designed to parse tokens from chunks */
/* of data.								*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "FileParser.h"

/*
bool IsValidIdentifier(char identifier)
{
	if (identifier == '#')
		return false;
	else
		return true;
}
*/

bool IsValidIdentifier(char identifier, char* delimiters, int totalDelimiters)
{
	if (delimiters == 0 || totalDelimiters == 0)
		return false;

	for (int i = 0; i < totalDelimiters; ++i)
	{
		if (identifier == delimiters[i])
			return false;
	}

	return true;
}

FileParser::FileParser()
{

}

FileParser::FileParser(const FileParser& other)
{

}

FileParser::~FileParser()
{

}

void FileParser::Reset()
{
	m_startIndex = 0;
	m_endIndex = 0;

	return;
}

void FileParser::SetStream(char* data)
{
	Reset();
	m_data = data;

	return;
}

bool FileParser::GetNextToken(string* buffer, char* delimiters, int totalDelimiters)
{
	bool inString = false;

	m_startIndex = m_endIndex;
	int length = static_cast<int>(m_data.length());


	if (m_startIndex >= length - 1)
		return false;

	// Find beginning of valid data
	// If identifier is invalid, move to the next line
	while (m_startIndex < length && IsValidIdentifier(m_data[m_startIndex], delimiters, totalDelimiters) == false)
	{
		m_startIndex++;
	}

	m_endIndex = m_startIndex + 1;

	if (m_data[m_startIndex] == '"')
		

	return true;
}

bool FileParser::NextLine(string* buffer)
{
	char temp;
	while (m_data[temp] != '\n')
	{
		
	}

	//int length = static_cast<int>(m_data.length());

	/*
	if (m_startIndex < length && m_endIndex < length)
	{
		m_endIndex = m_startIndex;

		while (m_endIndex < length && (IsValidIdentifier(m_data[m_endIndex]
	}
	*/

	return true;
}