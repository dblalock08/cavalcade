// Input.h
#pragma once

class Input
{
public:
	Input();
	~Input();

	bool Initialize();
	void Shutdown();

	void Update();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};