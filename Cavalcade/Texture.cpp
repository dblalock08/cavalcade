/****************************************/
/* Loading, unloading, and access of	*/
/* model texture(s)						*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Texture.h"

Texture::Texture() : m_texture(0)
{

}

Texture::Texture(const Texture& other)
{

}

Texture::~Texture()
{

}

bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_texture, NULL);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void Texture::Shutdown()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}

ID3D11ShaderResourceView* Texture::GetTexture()
{
	return m_texture;
}