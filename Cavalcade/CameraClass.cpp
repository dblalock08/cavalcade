#include "CameraClass.h"

CameraClass::CameraClass()
{
	m_position.x = 0;
	m_position.y = 0;
	m_position.z = 0;

	m_rotation.x = 0;
	m_rotation.y = 0;
	m_rotation.z = 0;

	m_movement[0] = false;
	m_movement[1] = false;
	m_movement[2] = false;
	m_movement[3] = false;
}

CameraClass::CameraClass(const CameraClass& other)
{

}

CameraClass::~CameraClass()
{

}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	return;
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;

	return;
}

void CameraClass::MoveCamera(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;

	return;
}

void CameraClass::MoveCameraFwd()
{
	m_movement[0] = true;
	
	return;
}

void CameraClass::MoveCameraBack()
{
	m_movement[1] = true;

	return;
}

void CameraClass::MoveCameraLeft()
{
	m_movement[2] = true;

	return;
}

void CameraClass::MoveCameraRight()
{
	m_movement[3] = true;

	return;
}

void CameraClass::MoveCameraUp()
{
	m_movement[4] = true;

	return;
}

void CameraClass::MoveCameraDown()
{
	m_movement[5] = true;

	return;
}

void CameraClass::RotateCamera(float x, float y, float z)
{
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;
}

XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}

XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

void CameraClass::UpdateView()
{
	XMFLOAT3 up;
	XMFLOAT3 position;
	XMFLOAT3 lookAt;
	float yaw, pitch, roll;
	
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	if (m_movement[0] == true)
	{
		m_position.z += 0.05f;
	}
	if (m_movement[1] == true)
	{
		m_position.z += -0.05f;
	}
	if (m_movement[2] == true)
	{
		m_position.x += -0.05f;
	}
	if (m_movement[3] == true)
	{
		m_position.x += 0.05f;
	}
	if (m_movement[4] == true)
	{
		m_position.y += 0.05f;
	}
	if (m_movement[5] == true)
	{
		m_position.y += -0.05f;
	}

	for (int i = 0; i < 6; ++i)
	{
		m_movement[i] = false;
	}

	position.x = m_position.x;
	position.y = m_position.y;
	position.z = m_position.z;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	XMVECTOR upVector = XMLoadFloat3(&up);
	XMVECTOR positionVector = XMLoadFloat3(&position);
	XMVECTOR lookVector = XMLoadFloat3(&lookAt);

	lookVector = XMVector3TransformCoord(lookVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	lookVector = positionVector + lookVector;

	XMMATRIX view = XMMatrixLookAtLH(positionVector, lookVector, upVector);
	XMStoreFloat4x4(&m_viewMatrix, view);

	return;
}

void CameraClass::GetViewMatrix(XMFLOAT4X4& viewMatrix)
{
	viewMatrix = m_viewMatrix;

	return;
}