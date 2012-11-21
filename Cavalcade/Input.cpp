/****************************************/
/* Game input handler					*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Input.h"

Input::Input()
{

}

Input::~Input()
{

}

bool Input::Initialize()
{
	for (int i = 0; i < 256; ++i)
	{
		m_keys[i] = false;
	}

	return true;
}

void Input::Update()
{

}

void Input::KeyDown(unsigned int key)
{
	m_keys[key] = true;

	return;
}

void Input::KeyUp(unsigned int key)
{
	m_keys[key] = false;

	return;
}

bool Input::IsKeyDown(unsigned int key)
{
	if (m_keys[key] == true)
	{
		return true;
	}
	
	return false;
}