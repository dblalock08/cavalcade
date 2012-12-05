// Graphics.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>

#include "D3DClass.h"
#include "CameraClass.h"
#include "ShaderManager.h"
#include "AmbientLight.h"
#include "Model.h"
#include "TextClass.h"

#include "settings.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(HWND, HINSTANCE, int, int);
	void Shutdown();

	bool Update();		// One frame of graphics
	void Render();		// Render the scene

	void MoveCamera(bool, bool, bool, bool, bool, bool);	// forward, back, left, right, up, down
	void RotateCamera(float x, float y, float z);

	bool CreateObjectFromFile(char* filename);

private:
	D3DClass* m_D3D;
	
	ShaderManager* m_ShaderManager;
	
	AmbientLight* m_AmbientLight;

	CameraClass* m_Camera;
	Model* m_Model;
	//TextClass* m_Text;
};