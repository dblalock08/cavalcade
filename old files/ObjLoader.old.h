// ObjLoader.h
#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>

#include "TokenStream.h"

#include <fstream>
using namespace std;

class ObjLoader
{
public:
	ObjLoader();
	ObjLoader(const ObjLoader&);
	~ObjLoader();

	bool ReadFromFile(wstring filename);
	void Shutdown();

	float* GetVertices() { return m_vertices; }
	float* GetNormals() { return m_normals; }
	float* GetTexCoords() { return m_texCoords; }

	int GetVertexCount() { return m_vertexCount; }

private:
	int m_startIndex, m_endIndex;

	int m_vertexCount;
	int m_faceCount;

	float* m_vertices;
	float* m_normals;
	float* m_texCoords;
};