#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>
#include <D3D11.h>
#include <D3DX11async.h>	// Remove in production; shaders will be compiled offline

#include <fstream>

using namespace std;

class FlatTextShader
{
private:
#pragma pack(push, 1)
	struct ConstantBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct PixelBufferType
	{
		XMFLOAT4 pixelColor;
	};
#pragma pack(pop)

public:
	FlatTextShader();
	FlatTextShader(const FlatTextShader&);
	~FlatTextShader();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	void Render(ID3D11DeviceContext*, int, XMFLOAT4X4, XMFLOAT4X4, XMFLOAT4X4, ID3D11ShaderResourceView*, XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*);		// Shaders are combined in one .hlsl file
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, XMFLOAT4X4, ID3D11ShaderResourceView*, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_samplerState;
	
	ID3D11Buffer* m_constantBuffer;
	ID3D11Buffer* m_pixelBuffer;
};