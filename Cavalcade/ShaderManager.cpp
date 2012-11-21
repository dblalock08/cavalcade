#include "ShaderManager.h"

ShaderManager::ShaderManager() : m_ColorShader(0)
{

}

ShaderManager::ShaderManager(const ShaderManager& other)
{

}

ShaderManager::~ShaderManager()
{

}

// Initialize //
bool ShaderManager::Initialize(ID3D11Device* device, HWND hwnd)
{
	bool result;

	m_ColorShader = new ColorShader;
	if (!m_ColorShader)
		return false;

	m_AmbientColorShader = new AmbientColorShader;
	if (!m_AmbientColorShader)
		return false;

	result = m_AmbientColorShader->Initialize(device, hwnd);
	if (!result)
		return false;

	return true;
}

void ShaderManager::Shutdown()
{
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	if (m_AmbientColorShader)
	{
		m_AmbientColorShader->Shutdown();
		delete m_AmbientColorShader;
		m_AmbientColorShader = 0;
	}

	return;
}

void ShaderManager::RenderColorShader(ID3D11DeviceContext* deviceContext, int indexCount,
									  XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix)
{
	m_ColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix);

	return;
}

void ShaderManager::RenderAmbientColorShader(ID3D11DeviceContext* deviceContext, int indexCount, XMFLOAT4X4 worldMatrix,
											 XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ID3D11ShaderResourceView* texture,
											 XMFLOAT3 lightDirection, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor)
{
	m_AmbientColorShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection, ambientColor, diffuseColor);

	return;
}
/*
void ShaderManager::RenderFlatTextShader(ID3D11DeviceContext* deviceContext, int indexCount, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 viewMatrix,
										 XMFLOAT4X4 projectionMatrix, ID3D11ShaderResourceView* texture, XMFLOAT4 color)
{
	m_FlatTextShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, color);
	
	return;
}
*/