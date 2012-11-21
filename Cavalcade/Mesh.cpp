/****************************************/
/* Game model geometry					*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Mesh.h"

Mesh::Mesh() : m_vertexBuffer(0), m_indexBuffer(0), m_mesh(0)
{

}

Mesh::Mesh(const Mesh& other)
{

}

Mesh::~Mesh()
{

}

bool Mesh::Initialize(ID3D11Device* device, WCHAR* meshFilename)
{
	bool result;

	result = LoadMesh(meshFilename);
	if (!result)
		return false;

	result = InitializeBuffers(device);
	if (!result)
		return false;

	return true;
}

void Mesh::Shutdown()
{
	ShutdownBuffers();

	ReleaseMesh();

	return;
}

bool Mesh::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
		return false;

	indices = new unsigned long[m_indexCount];
	if (!indices)
		return false;

	for (i = 0; i < m_vertexCount; ++i)
	{
		vertices[i].position = XMFLOAT3(m_mesh[i].x, m_mesh[i].y, m_mesh[i].z);
		vertices[i].texture = XMFLOAT2(m_mesh[i].tu, m_mesh[i].tv);
		vertices[i].normal = XMFLOAT3(m_mesh[i].nx, m_mesh[i].ny, m_mesh[i].nz);

		indices[i] = i;
	}

// Tri-color gradiant effect
/*
	for (i = 0; i < m_vertexCount; ++i)
	{
		vertices[i].position = XMFLOAT3(m_mesh[i].x, m_mesh[i].y, m_mesh[i].z);

		if ((i % 2) == 0)
		{
			vertices[i].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
		}
		else if ((i % 3) == 0)
		{
			vertices[i].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		}
		else
		{
			vertices[i].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		}

		indices[i] = i;
	}
*/

	

	// Vertex buffer description
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
#ifdef _DEBUG
		DXTRACE_MSG(L"Failed to load index buffer.");
#endif
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
#ifdef _DEBUG
		DXTRACE_MSG(L"Failed to load index buffer.");
#endif
		return false;
	}

	if (vertices)
	{
		delete vertices;
		vertices = 0;
	}
	if (indices)
	{
		delete indices;
		indices = 0;
	}

	return true;
}

void Mesh::ShutdownBuffers()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

bool Mesh::LoadMesh(WCHAR* meshFilename)
{
	bool result;
	float *verts, *norms, *texCoords;
	int i;

	m_objLoader = new ObjLoader;

	result = m_objLoader->LoadFromFile(meshFilename);
	if (!result)
		return false;

	m_vertexCount = m_objLoader->GetVertexCount();
	m_indexCount = m_vertexCount;

	verts = m_objLoader->GetVerticesPtr();
	norms = m_objLoader->GetNormalsPtr();
	texCoords = m_objLoader->GetTexCoordsPtr();
	
	int vIndex = 0;
	int nIndex = 0;
	int tIndex = 0;
	
	m_mesh = new MeshType[m_vertexCount];

	for (i = 0; i < m_vertexCount; ++i)
	{
		m_mesh[i].z = verts[vIndex] * -1.0f;	// Correct vertex winding
		vIndex++;
		m_mesh[i].y = verts[vIndex];
		vIndex++;
		m_mesh[i].x = verts[vIndex];
		vIndex++;
	}

	for (i = 0; i < m_objLoader->GetTexCoordsCount(); ++i)
	{
		m_mesh[i].tu = texCoords[tIndex];
		tIndex++;
		m_mesh[i].tv = texCoords[tIndex];
		tIndex++;
	}

	for (i = 0; i < m_vertexCount / 3; ++i)
	{
		m_mesh[i].nx = norms[nIndex];
		nIndex++;
		m_mesh[i].ny = norms[nIndex];
		nIndex++;
		m_mesh[i].nz = norms[nIndex];
		nIndex++;
	}

	if (m_objLoader)
	{
		m_objLoader->Shutdown();
		delete m_objLoader;
		m_objLoader = 0;
	}

	return true;
}

void Mesh::ReleaseMesh()
{
	if (m_mesh)
	{
		delete[] m_mesh;
		m_mesh = 0;
	}

	return;
}