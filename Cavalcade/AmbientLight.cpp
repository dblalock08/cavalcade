/****************************************/
/* Ambient light object					*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "AmbientLight.h"

AmbientLight::AmbientLight()
{

}

AmbientLight::AmbientLight(const AmbientLight& other)
{

}

AmbientLight::~AmbientLight()
{

}

void AmbientLight::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void AmbientLight::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void AmbientLight::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
	return;
}

XMFLOAT4 AmbientLight::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 AmbientLight::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMFLOAT3 AmbientLight::GetDirection()
{
	return m_direction;
}