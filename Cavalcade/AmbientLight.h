// AmbientLight.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(const AmbientLight&);
	~AmbientLight();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMFLOAT3 GetDirection();

private:
	XMFLOAT4 m_ambientColor;
	XMFLOAT4 m_diffuseColor;
	XMFLOAT3 m_direction;
};