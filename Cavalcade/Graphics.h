// Graphics.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>

#include "D3DClass.h"
#include "CameraClass.h"
#include "ShaderManager.h"
#include "Model.h"

// Lighting //
#include "AmbientLight.h"

#include "settings.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	bool Initialize(HWND, HINSTANCE);
	void Shutdown();

	bool Update();		// One frame of graphics
	void Render();		// Render the scene

	void MoveCamera(bool, bool, bool, bool, bool, bool);	// forward, back, left, right, up, down
	void RotateCamera(float x, float y, float z);

	bool CreateObjectFromFile(char* filename);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ShaderManager* m_ShaderManager;

	Model* m_Model;

	AmbientLight* m_AmbientLight;
};