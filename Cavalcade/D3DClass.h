// D3DClass.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>
#include <D3D11.h>
//#include <D3DX11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>

#include "settings.h"

class D3DClass
{
public:
	D3DClass();
	~D3DClass();

	bool Initialize(HWND, HINSTANCE);
	void Shutdown();

	void BeginScene();
	void EndScene();

	ID3D11Device* GetDevice() { return m_device; }
	ID3D11DeviceContext* GetDeviceContext() { return m_deviceContext; }

	void GetProjectionMatrix(XMFLOAT4X4& projectionMatrix);
	void GetWorldMatrix(XMFLOAT4X4& worldMatrix);
	void GetOrthoMatrix(XMFLOAT4X4& orthoMatrix);

	void GetVideoCardInfo(char*, int&);

	//void ZBufferEnable();
	//void ZBufferDisable();

	//void AlphaBlendOn();
	//void AlphaBlendOff();

private:
	int m_videoCardMemory;
	char m_videoCardDescription[128];

	D3D_DRIVER_TYPE m_driverType;
	D3D_FEATURE_LEVEL m_featureLevel;

	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_deviceContext;
	ID3D11RenderTargetView* m_renderTargetView;

	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilState* m_depthStencilState;
	ID3D11DepthStencilView* m_depthStencilView;
	ID3D11RasterizerState* m_rasterState;

	XMFLOAT4X4 m_projectionMatrix;
	XMFLOAT4X4 m_worldMatrix;
	XMFLOAT4X4 m_orthoMatrix;
};