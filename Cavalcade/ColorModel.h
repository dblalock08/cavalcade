// ColorModel.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>
#include <D3D11.h>

#include "Mesh.h"

class ColorModel
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	ColorModel();
	ColorModel(const ColorModel&);
	~ColorModel();

	bool Initialize(ID3D11Device* device, WCHAR* modelFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount() { return m_mesh->GetIndexCount(); }

private:
	void RenderBuffers(ID3D11DeviceContext*);
	
	void ReleaseModel();
	void ReleaseTextures();

private:
	Mesh* m_mesh;
};