// Mesh.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>
#include <D3D11.h>
#ifdef _DEBUG
#include <DxErr.h>
#endif

#include "ObjLoader.h"

class Mesh
{
#pragma pack(push, 1)
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
	};

	struct MeshType
	{
		float x, y, z;	// Vertex position
		float tu, tv;	// Texture coordinates
		float nx, ny, nz;
	};
#pragma pack(pop)

public:
	Mesh();
	Mesh(const Mesh&);
	~Mesh();

	bool Initialize(ID3D11Device* device, WCHAR* meshFilename);
	void Shutdown();

	int GetIndexCount() { return m_indexCount; }
	int GetStride() { return sizeof(VertexType); }
	ID3D11Buffer** GetVertexBufferPtr() { return &m_vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return m_indexBuffer; }

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();

	bool LoadMesh(WCHAR*);
	void ReleaseMesh();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	ObjLoader* m_objLoader;
	MeshType* m_mesh;

	int m_vertexCount, m_indexCount;
};