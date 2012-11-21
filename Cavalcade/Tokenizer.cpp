/****************************************/
/* Splits input into tokens for parsing */
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Tokenizer.h"

bool IsValidIdentifier(char c)
{
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

Tokenizer::Tokenizer()
{
	
}

Tokenizer::Tokenizer(const Tokenizer& other)
{

}

Tokenizer::~Tokenizer()
{

}

void Tokenizer::SetStream(char* data)
{
	ResetStream();
	m_data = data;

	return;
}

void Tokenizer::ResetStream()
{
	m_start = 0;
	m_end = 0;

	return;
}

bool Tokenizer::GetNextToken(string* tokenBuffer, char* delimiters, int totalDelimiters)
{
	m_start = m_end;

	bool isInString = false;
	int length = static_cast<int>(m_data.length());

	if (m_start >= length - 1)
		return false;

	// Find the first valid identifier in the data
	while (m_start < length && IsValidIdentifier(m_data[m_start], delimiters, totalDelimiters) == false)
	{
		m_start++;
	}

	m_end = m_start + 1;

	if (m_data[m_start] == '"')
		isInString = !isInString;

	if (m_start < length)
	{
		// Find the last valid character before a delimiter
		while (m_end < length && (IsValidIdentifier(m_data[m_end], delimiters, totalDelimiters)) || isInString == true)
		{
			if (m_data[m_end] == '"')
				isInString = !isInString;

			m_end++;
		}

		if (tokenBuffer != NULL)
		{
			// Load the buffer with the token
			int size = m_end - m_start;
			int index = m_start;

			tokenBuffer->reserve(size + 1);
			tokenBuffer->clear();

			for (int i = 0; i < size; ++i)
			{
				tokenBuffer->push_back(m_data[index++]);
			}
		}
		
		return true;
	}

	return true;
}

bool Tokenizer::MoveToNextLine(string* buffer)
{
	int length = static_cast<int>(m_data.length());

	if (m_start < length && m_end < length)
	{
		m_end = m_start;

		while (m_end < length && (IsValidIdentifier(m_data[m_end]) || m_data[m_end] == ' '))
		{
			m_end++;
		}

		if ((m_end - m_start) == 0)
			return false;

		if ((m_end - m_start) >= length)
			return false;

		if (buffer != NULL)
		{
			int size = m_end - m_start;
			int index = m_start;

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

	m_end++;
	m_start = m_end + 1;

	return true;
}