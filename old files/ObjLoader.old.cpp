/****************************************/
/* Loads Wavefront .obj files.			*/
/* This is a simple format which is		*/
/* suitable mainly for static meshes.	*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "ObjLoader.h"

#include <string>
#include <vector>

ObjLoader::ObjLoader() : m_vertices(0), m_normals(0), m_texCoords(0)
{

}

ObjLoader::ObjLoader(const ObjLoader& other)
{

}

ObjLoader::~ObjLoader()
{

}

bool ObjLoader::ReadFromFile(std::wstring filename)
{
	ifstream fin;
	char* buffer;
	int filesize;
	int numVertices = 0;

	m_startIndex = 0;
	m_endIndex = 0;

	fin.open(filename, ios_base::in);
	if (fin.fail())
		return false;

	fin.seekg(0, ios_base::end);
	filesize = static_cast<int>(fin.tellg());
	fin.seekg(0, ios_base::beg);

	buffer = new char[filesize];
	memset(buffer, '\0', filesize);

	TokenStream tokenStream, lineStream, faceStream;
	std::string tempLine, token;

	fin.read(buffer, filesize);
	tokenStream.SetTokenStream(buffer);

	delete[] buffer;
	buffer = 0;

	std::vector<float> verts, norms, texC;
	std::vector<int> faces;

	char lineDelimiters[2] = { '\n', ' ' };

	while (tokenStream.MoveToNextLine(&tempLine))
	{
		lineStream.SetTokenStream((char*)tempLine.c_str());
		tokenStream.GetNextToken(0, 0, 0);

		if (!lineStream.GetNextToken(&token, lineDelimiters, 2))
			continue;

		if (strcmp(token.c_str(), "v") == 0)
		{
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			verts.push_back(static_cast<float>(atof(token.c_str())));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			verts.push_back(static_cast<float>(atof(token.c_str())));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			verts.push_back(static_cast<float>(atof(token.c_str())));
		}
		else if (strcmp(token.c_str(), "vn") == 0)
		{
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			norms.push_back(static_cast<float>(atof(token.c_str())));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			norms.push_back(static_cast<float>(atof(token.c_str())));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			norms.push_back(static_cast<float>(atof(token.c_str())));
		}
		else if (strcmp(token.c_str(), "vt") == 0)
		{
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			texC.push_back(static_cast<float>(atof(token.c_str())));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			texC.push_back(static_cast<float>(atof(token.c_str())));
		}
		else if (strcmp(token.c_str(), "f") == 0)
		{
			char faceTokens[3] = { '\n', ' ', '/' };
			std::string faceIndex;

			faceStream.SetTokenStream((char*)(tempLine.c_str()));
			faceStream.GetNextToken(0, 0, 0);

			for (int i = 0; i < 3; ++i)
			{
				faceStream.GetNextToken(&faceIndex, faceTokens, 3);
				faces.push_back(static_cast<int>(atoi(faceIndex.c_str())));

				faceStream.GetNextToken(&faceIndex, faceTokens, 3);
				faces.push_back(static_cast<int>(atoi(faceIndex.c_str())));

				faceStream.GetNextToken(&faceIndex, faceTokens, 3);
				faces.push_back(static_cast<int>(atoi(faceIndex.c_str())));
			}
		}
		else if (strcmp(token.c_str(), "#") == 0)
		{
			int a = 0;
			int b = a;
		}

		token[0] = '\0';
	}

	// Unroll the obj information into the appropriate data structures
	int vIndex = 0, nIndex = 0, tIndex = 0;
	int numFaces = static_cast<int>(faces.size() / 9);

	m_vertexCount = verts.size() / 3;

	m_vertices = new float[m_vertexCount * 3];

	if (static_cast<int>(norms.size()) != 0)
	{
		m_normals = new float[m_vertexCount * 3];
	}

	if (static_cast<int>(texC.size()) != 0)
	{
		m_texCoords = new float[m_vertexCount * 2];
	}

	for (int f = 0; f < static_cast<int>(verts.size()); f+=3)
	{
		m_vertices[vIndex + 0] = verts[f];
		m_vertices[vIndex + 1] = verts[f + 1];
		m_vertices[vIndex + 2] = verts[f + 2];
		vIndex += 3;
	}

	verts.clear();
	norms.clear();
	texC.clear();
	faces.clear();

	return true;
}

void ObjLoader::Shutdown()
{
	if (m_texCoords)
	{
		delete [] m_texCoords;
		m_texCoords = 0;
	}

	if (m_normals)
	{
		delete [] m_normals;
		m_normals = 0;
	}

	if (m_vertices)
	{
		delete [] m_vertices;
		m_vertices = 0;
	}

	return;
}