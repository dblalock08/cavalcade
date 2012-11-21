// CameraClass.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass& other);
	~CameraClass();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void MoveCamera(float x, float y, float z);
	void MoveCameraFwd();
	void MoveCameraBack();
	void MoveCameraLeft();
	void MoveCameraRight();
	void MoveCameraUp();
	void MoveCameraDown();
	void RotateCamera(float x, float y, float z);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void UpdateView();	// Updates the view matrix
	void GetViewMatrix(XMFLOAT4X4& viewMatrix);

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	bool m_movement[6];

	XMFLOAT4X4 m_viewMatrix;
};