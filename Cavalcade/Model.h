// Model.h
#pragma once

#include <D3D11.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device* device, WCHAR* modelFilename, WCHAR* textureFilename);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount() { return m_Mesh->GetIndexCount(); }
	ID3D11ShaderResourceView* GetTexture() { return m_Texture->GetTexture(); }

	XMFLOAT4X4 GetRotationMatrix() { return m_rotationMatrix; }

private:
	void RenderBuffers(ID3D11DeviceContext*);
	void ShutdownBuffers();

	void ReleaseTextures();
	void ReleaseModel();

private:
	Mesh* m_Mesh;
	Texture* m_Texture;

	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMFLOAT4X4 m_rotationMatrix;
};