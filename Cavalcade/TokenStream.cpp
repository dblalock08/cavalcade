/********************************************/
/* Adapted from:							*/
/* Beginning DirectX 11 Game Programming	*/
/* By Allen Sherrod and Wendy Jones			*/
/*											*/
/* TokenStream - Used to return blocks of	*/
/* text in a file.							*/
/********************************************/
#include "TokenStream.h"

bool IsValidIdentifier(char c)
{
	// ASCII from ! to ~
	if (static_cast<int>(c) > 32 && static_cast<int>(c) < 127)
		return true;

	return false;
}

bool IsValidIdentifier(char c, char* delimiters, int totalDelimiters)
{
	if (delimiters == 0 || totalDelimiters == 0)
		return IsValidIdentifier(c);

	for (int i = 0; i < totalDelimiters; ++i)
	{
		if (c == delimiters[i])
			return false;
	}

	return true;
}

TokenStream::TokenStream()
{

}

TokenStream::TokenStream(const TokenStream& other)
{

}

TokenStream::~TokenStream()
{

}

void TokenStream::ResetStream()
{
	m_startIndex = 0;
	m_endIndex = 0;

	return;
}

void TokenStream::SetTokenStream(char* data)
{
	ResetStream();
	m_data = data;

	return;
}

bool TokenStream::GetNextToken(string* buffer, char* delimiters, int totalDelimiters)
{
	m_startIndex = m_endIndex;

	bool isInString = false;
	int length = static_cast<int>(m_data.length());

	if (m_startIndex >= length - 1)
		return false;

	while (m_startIndex < length && IsValidIdentifier(m_data[m_startIndex], delimiters, totalDelimiters) == false)
	{
		m_startIndex++;
	}

	m_endIndex = m_startIndex + 1;

	if (m_data[m_startIndex] == '"')
		isInString = !isInString;

	if (m_startIndex < length)
	{
		while (m_endIndex < length && (IsValidIdentifier(m_data[m_endIndex], delimiters, totalDelimiters) || isInString == true))
		{
			if (m_data[m_endIndex] == '"')
				isInString = !isInString;

			m_endIndex++;
		}

		if (buffer != NULL)
		{
			int size = (m_endIndex - m_startIndex);
			int index = m_startIndex;

			buffer->reserve(size + 1);
			buffer->clear();

			for (int i = 0; i < size; ++i)
			{
				buffer->push_back(m_data[index++]);
			}
		}

		return true;
	}

	return true;
}

bool TokenStream::MoveToNextLine(string* buffer)
{
	int length = static_cast<int>(m_data.length());

	if (m_startIndex < length && m_endIndex < length)
	{
		m_endIndex = m_startIndex;

		while (m_endIndex < length && (IsValidIdentifier(m_data[m_endIndex]) || m_data[m_endIndex] == ' '))
		{
			m_endIndex++;
		}

		if ((m_endIndex - m_startIndex) == 0)
			return false;

		if ((m_endIndex - m_startIndex) >= length)
			return false;

		if (buffer != NULL)
		{
			int size = m_endIndex - m_startIndex;
			int index = m_startIndex;

			buffer->reserve(size + 1);
			buffer->clear();

			for (int i = 0; i < size; ++i)
			{
				buffer->push_back(m_data[index++]);
			}
		}
	}
	else
	{
		return false;
	}

	m_endIndex++;
	m_startIndex = m_endIndex + 1;

	return true;
}