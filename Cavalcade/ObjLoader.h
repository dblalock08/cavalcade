// ObjLoader.h
#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

#include "Tokenizer.h"

class ObjLoader
{
public:
	ObjLoader();
	ObjLoader(const ObjLoader&);
	~ObjLoader();

	bool LoadFromFile(wchar_t* filename);
	void Shutdown();

	float* GetVerticesPtr() { return m_vertices; }
	float* GetNormalsPtr() { return m_normals; }
	float* GetTexCoordsPtr() { return m_texCoords; }
	
	int GetVertexCount() { return m_vertexCount; }
	int GetTexCoordsCount() { return m_numTexCoords; }

private:
	float* m_vertices;
	float* m_normals;
	float* m_texCoords;

	int m_vertexCount;
	int m_numTexCoords;
};