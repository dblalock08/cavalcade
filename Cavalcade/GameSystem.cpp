/****************************************/
/* Cavalcade							*/
/* David Blalock 2012					*/
/****************************************/
#include "GameSystem.h"

GameSystem::GameSystem() : m_SysTimer(0), m_Input(0), m_Graphics(0)
{

}

GameSystem::~GameSystem()
{

}

bool GameSystem::Initialize()
{
	int screenWidth, screenHeight;
	bool result;
	
	screenWidth = 0;
	screenHeight = 0;

	result = InitializeWindows(screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Message passing system //
	m_PostMaster = new PostMaster;
	if (!m_PostMaster)
	{
		MessageBox(m_hwnd, L"Messaging system could not be created.", L"Error", MB_OK);
		return false;
	}
	else
	{
		result = m_PostMaster->Initialize();
		if (!result)
		{
			MessageBox(m_hwnd, L"Messaging system could not be initialized.", L"Error", MB_OK);
			return false;
		}
	}

	// Input system //
	m_Input = new Input;
	if (!m_Input)
	{
		MessageBox(m_hwnd, L"Input system could not be created.", L"Critical Error", MB_OK);
		return false;
	}
	else
	{
		result = m_Input->Initialize();
		if (!result)
		{
			MessageBox(m_hwnd, L"Input system could not be initialized.", L"Critical Error", MB_OK);
			return false;
		}
	}

	// Main system timer //
	m_SysTimer = new Timer;
	if (!m_SysTimer)
	{
		MessageBox(m_hwnd, L"System timer could not be created.", L"Error", MB_OK);
		return false;
	}
	else
	{
		result = m_SysTimer->Initialize();
		if (!result)
		{
			MessageBox(m_hwnd, L"System timer could not be initialized.", L"Error", MB_OK);
			return false;
		}
	}

	// Graphics system //
	m_Graphics = new Graphics;
	if (!m_Graphics)
	{
		MessageBox(m_hwnd, L"Graphics system could not be created.", L"Error", MB_OK);
		return false;
	}
	else
	{
		result = m_Graphics->Initialize(m_hwnd, m_hInstance, screenWidth, screenHeight);
		if (!result)
		{
			MessageBox(m_hwnd, L"Graphics system could not be initialized.", L"Error", MB_OK);
			return false;
		}
	}

	return true;
}

void GameSystem::Shutdown()
{
	if (m_Graphics)
	{
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	if (m_SysTimer)
	{
		delete m_SysTimer;
		m_SysTimer = 0;
	}

	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	if (m_PostMaster)
	{
		m_PostMaster->Shutdown();
		delete m_PostMaster;
		m_PostMaster = 0;
	}

	ShutdownWindows();

	return;
}

void GameSystem::Run()
{
	MSG msg;
	bool done, result;

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while (!done)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			result = Update();
			if (!result)
			{
				MessageBox(m_hwnd, L"Game system update failed.", L"Critical Error!", MB_OK);
				done = true;
			}
		}
	}

	return;
}

// Game logic //
bool GameSystem::Update()
{
	bool result;
	float frameDelta = 0.0f;

	// Update system timer
	m_SysTimer->Update();
	frameDelta = m_SysTimer->GetTime();

	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// Shift modifier //
	if (m_Input->IsKeyDown(VK_SHIFT))
	{
		if (m_Input->IsKeyDown(VK_UP))
		{
			// Pitch camera up
			m_Graphics->RotateCamera(-0.05f, 0.0f, 0.0f);
		}
		if (m_Input->IsKeyDown(VK_DOWN))
		{
			// Pitch camera down
			m_Graphics->RotateCamera(0.05f, 0.0f, 0.0f);
		}
		if (m_Input->IsKeyDown(VK_LEFT))
		{
			// Rotate camera counter clockwise
			m_Graphics->RotateCamera(0.0f, 0.0f, 0.05f);
		}
		if (m_Input->IsKeyDown(VK_RIGHT))
		{
			// Rotate camera clockwise
			m_Graphics->RotateCamera(0.0f, 0.0f, -0.05f);
		}
	}
	else
	{
		if (m_Input->IsKeyDown(VK_UP))
		{
			// Move camera up
			m_Graphics->MoveCamera(false, false, false, false, true, false);
		}
		if (m_Input->IsKeyDown(VK_DOWN))
		{
			// Move camera down
			m_Graphics->MoveCamera(false, false, false, false, false, true);
		}
		if (m_Input->IsKeyDown(VK_LEFT))
		{
			// Pan camera left
			m_Graphics->RotateCamera(0.0f, -0.05f, 0.0f);
		}
		if (m_Input->IsKeyDown(VK_RIGHT))
		{
			// Pan camera right
			m_Graphics->RotateCamera(0.0f, 0.05f, 0.0f);
		}
		if (m_Input->IsKeyDown((int)0x41))
		{
			// Move camera left
			m_Graphics->MoveCamera(false, false, true, false, false, false);
		}
		if (m_Input->IsKeyDown((int)0x44))
		{
			// Move camera right
			m_Graphics->MoveCamera(false, false, false, true, false, false);
		}
		if (m_Input->IsKeyDown((int)0x57))
		{
			// Move camera forward
			m_Graphics->MoveCamera(true, false, false, false, false, false);
		}
		if (m_Input->IsKeyDown((int)0x53))
		{
			// Move camera back
			m_Graphics->MoveCamera(false, true, false, false, false, false);
		}
	}
	
	// Render scene
	result = m_Graphics->Update();
	if (!result)
		return false;

	return true;
}

LRESULT CALLBACK GameSystem::MessageHandler(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_KEYDOWN:
			m_Input->KeyDown((unsigned int)wParam);
			break;

		case WM_KEYUP:
			m_Input->KeyUp((unsigned int)wParam);
			break;
			
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

bool GameSystem::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wndClass = { 0 };
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;
	m_hInstance = GetModuleHandle(NULL);
	m_applicationName = L"Cavalcade";

	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hIconSm = wndClass.hIcon;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = 0;
	wndClass.lpszClassName = m_applicationName;
	wndClass.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wndClass);

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	//RECT rc;
	if (FULLSCREEN_ENABLED)
	{
		/*
		rc.top = 0;
		rc.left = 0;
		rc.right = screenWidth;
		rc.bottom = screenHeight;

		AdjustWindowRect(&rc, WS_EX_APPWINDOW, FALSE);

		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
								WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
								CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight,
								NULL, NULL, m_hInstance, NULL);
		*/

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		//ZeroMemory(&dmScreenSettings, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		//dmScreenSettings.dmPosition = dmPos;		// Use for multi-monitor support
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		posX = 0;
		posY = 0;
	}
	else
	{
		/*
		rc.top = 0;
		rc.left = 0;
		rc.right = 800;
		rc.bottom = 600;
		
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		m_hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, m_applicationName, m_applicationName,
								WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
								CW_USEDEFAULT, CW_USEDEFAULT, rc.right, rc.bottom,
								NULL, NULL, m_hInstance, NULL);
		*/

		screenWidth = 800;
		screenHeight = 600;
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
								WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
								posX, posY, screenWidth, screenHeight,
								NULL, NULL, m_hInstance, NULL);
	if (!m_hwnd)
	{
		MessageBox(m_hwnd, L"Error creating window.\n", L"Error", MB_OK);
		return false;
	}

	// Register raw input devices immediately after creating the window
	RAWINPUTDEVICE rid[2];

	// Keyboard
	rid[0].usUsagePage = 1;
	rid[0].usUsage = 6;
	rid[0].dwFlags = 0;		// Change to RIDEV_NOLEGACY when ESC supported
	rid[0].hwndTarget = NULL;

	// Mouse
	rid[1].usUsagePage = 1;
	rid[1].usUsage = 2;
	rid[1].dwFlags = RIDEV_NOLEGACY;
	rid[1].hwndTarget = NULL;

	if (RegisterRawInputDevices(rid,2,sizeof(RAWINPUTDEVICE))==FALSE)
	{
		return false;
		// Handle error; call GetLastError for details
	}

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	
	SetCapture(m_hwnd);
	ShowCursor(true);

	return true;
}

void GameSystem::ShutdownWindows()
{
	if (FULLSCREEN_ENABLED)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	DestroyWindow(m_hwnd);
	m_hwnd = 0;

	UnregisterClass(m_applicationName, m_hInstance);
	m_hInstance = 0;

	ApplicationHandle = 0;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}


bool GameSystem::CreateNewObject(char* objectID)
{
	// Perform operations required to create a new object in the game world
	

	return true;
}