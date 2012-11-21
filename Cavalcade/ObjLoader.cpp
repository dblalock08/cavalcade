/****************************************/
/* Loads Wavefront .obj files.			*/
/* This is a simple format which is		*/
/* suitable mainly for static meshes.	*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "ObjLoader.h"

ObjLoader::ObjLoader() : m_vertices(0), m_normals(0), m_texCoords(0)
{
	m_vertexCount = 0;
	m_numTexCoords = 0;
}

ObjLoader::ObjLoader(const ObjLoader& other)
{

}

ObjLoader::~ObjLoader()
{
	Shutdown();
}

bool ObjLoader::LoadFromFile(wchar_t* filename)
{
	ifstream fin;
	char* buffer;
	int filesize;
	Tokenizer tokenStream, lineStream, faceStream;
	vector<float> verts;
	vector<float> norms;
	vector<float> texC;
	vector<int> faces;
	string tempLine, token;

	fin.open(filename, ios_base::in);
	if (fin.fail())
		return false;

	fin.seekg(0, ios_base::end);
	filesize = static_cast<int>(fin.tellg());
	fin.seekg(0, ios_base::beg);

	buffer = new char[filesize];
	memset(buffer, '\0', filesize);

	fin.read(buffer, filesize);
	fin.close();

	// Send buffer to tokenstream
	tokenStream.SetStream(buffer);

	if (buffer)
	{
		delete[] buffer;
		buffer = 0;
	}

	char lineDelimiters[2] = { '\n', ' ' };

	while (tokenStream.MoveToNextLine(&tempLine))
	{
		lineStream.SetStream((char*)tempLine.c_str());
		tokenStream.GetNextToken(0, 0, 0);

		if (!lineStream.GetNextToken(&token, lineDelimiters, 2))
			continue;

		if (strcmp(token.c_str(), "v") == 0)
		{
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			verts.push_back((float)atof(token.c_str()));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			verts.push_back((float)atof(token.c_str()));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			verts.push_back((float)atof(token.c_str()));
		}
		else if (strcmp(token.c_str(), "vn") == 0)
		{
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			norms.push_back((float)atof(token.c_str()));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			norms.push_back((float)atof(token.c_str()));
			
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			norms.push_back((float)atof(token.c_str()));
		}
		else if (strcmp(token.c_str(), "vt") == 0)
		{
			lineStream.GetNextToken(&token, lineDelimiters, 2);
			texC.push_back((float)atof(token.c_str()));

			lineStream.GetNextToken(&token, lineDelimiters, 2);
			texC.push_back((float)atof(token.c_str()));
		}
		else if (strcmp(token.c_str(), "f") == 0)
		{
			char faceTokens[3] = { '\n', ' ', '/' };
			string faceIndex;

			faceStream.SetStream((char*)tempLine.c_str());
			faceStream.GetNextToken(0, 0, 0);

			for (int i = 0; i < 3; ++i)
			{
				faceStream.GetNextToken(&faceIndex, faceTokens, 3);
				faces.push_back((int)atoi(faceIndex.c_str()));
				
				faceStream.GetNextToken(&faceIndex, faceTokens, 3);
				faces.push_back((int)atoi(faceIndex.c_str()));
				
				faceStream.GetNextToken(&faceIndex, faceTokens, 3);
				faces.push_back((int)atoi(faceIndex.c_str()));
			}
		}

		token[0] = '\0';
	}

	int vIndex = 0, nIndex = 0, tIndex = 0;
	int numFaces = (int)faces.size() / 9;
	m_numTexCoords = (int)texC.size() / 2;
	m_vertexCount = numFaces * 3;

	m_vertices = new float[m_vertexCount * 3];

	if ((int)texC.size() != 0)
	{
		m_texCoords = new float[m_vertexCount * 2];
	}

	if ((int)norms.size() != 0)
	{
		m_normals = new float[m_vertexCount * 3];
	}

	for (int f = 0; f < (int)faces.size(); f+=3)
	//for (int f = 0; f < static_cast<int>(numFaces); ++f)
	{
		m_vertices[vIndex] = verts[(faces[f] - 1) * 3 + 0];
		vIndex++;
		m_vertices[vIndex] = verts[(faces[f] - 1) * 3 + 1];
		vIndex++;
		m_vertices[vIndex] = verts[(faces[f] - 1) * 3 + 2];
		vIndex++;

		if (m_texCoords)
		{
			m_texCoords[tIndex] = texC[(faces[f + 1] - 1) * 2 + 0];
			tIndex++;
			m_texCoords[tIndex] = texC[(faces[f + 1] - 1) * 2 + 1];
			tIndex++;
		}

		if (m_normals)
		{
			m_normals[nIndex] = norms[(faces[f + 2] - 1) * 3 + 0];
			nIndex++;
			m_normals[nIndex] = norms[(faces[f + 2] - 1) * 3 + 1];
			nIndex++;
			m_normals[nIndex] = norms[(faces[f + 2] - 1) * 3 + 2];
			nIndex++;
		}
	}

	faces.clear();
	verts.clear();
	norms.clear();
	texC.clear();

	return true;
}

void ObjLoader::Shutdown()
{
	if (m_vertices)
	{
		delete [] m_vertices;
		m_vertices = 0;
	}

	if (m_normals)
	{
		delete [] m_normals;
		m_normals = 0;
	}

	if (m_texCoords)
	{
		delete [] m_texCoords;
		m_texCoords = 0;
	}

	m_vertexCount = 0;
	m_numTexCoords = 0;

	return;
}