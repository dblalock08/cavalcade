// ShaderManager.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>

#include "D3DClass.h"

// Shader classes //
#include "ColorShader.h"
#include "AmbientColorShader.h"
//#include "FlatTextShader.h"

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	void RenderColorShader(ID3D11DeviceContext*, int, XMFLOAT4X4, XMFLOAT4X4, XMFLOAT4X4);
	void RenderAmbientColorShader(ID3D11DeviceContext*, int, XMFLOAT4X4, XMFLOAT4X4, XMFLOAT4X4, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4);
	//void RenderFlatTextShader(ID3D11DeviceContext*, int, XMFLOAT4X4, XMFLOAT4X4, XMFLOAT4X4, ID3D11ShaderResourceView*, XMFLOAT4);

private:
	ColorShader* m_ColorShader;
	AmbientColorShader* m_AmbientColorShader;
	//FlatTextShader* m_FlatTextShader;
};