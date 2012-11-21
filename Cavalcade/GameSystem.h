// GameSystem.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Input.h"
#include "Timer.h"
#include "Graphics.h"
#include "PostMaster.h"

#include "settings.h"

class GameSystem
{
public:
	GameSystem();
	~GameSystem();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	bool CreateNewObject(char* objectID);	// Returns success or failure; Planned to return a "handle" to the newly created object

private:
	bool Update();
	bool InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	Timer* m_SysTimer;
	Input* m_Input;
	Graphics* m_Graphics;
	PostMaster* m_PostMaster;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static GameSystem* ApplicationHandle = 0;