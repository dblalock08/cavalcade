#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <xnamath.h>
#include <D3D11.h>
#include <fstream>
using namespace std;

#include "Texture.h"

class FontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		/// Vertex position in (x,y,z)
		XMFLOAT3 position;
		/// Texture coordinates in (tu,tv)
		XMFLOAT2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	/** 
	 * <param name="device">Pointer to ID3D11Device.</param>
	 * <param name="fontFilename">Filename of the font data.</param>
	 * <param name="textureFilename">Filename of the font texture.</param>
	 */
	/// Initialize the font.
	bool Initialize(ID3D11Device* device, char* fontFilename, WCHAR* textureFilename);
	/// Shutdown the font.
	void Shutdown();

	/// Return a pointer to the font's texture.
	ID3D11ShaderResourceView* GetTexture();
	/// Builds and returns the vertex array of triangles that will render the character sentence given as input to this function.
	/**
	 * <param name="vertices"></param>
	 * <param name="sentence"></param>
	 * <param name="drawX"></param>
	 * <param name="drawY"></param>
	 */
	void BuildVertexArray(void* vertices, char* sentence, float drawX, float drawY);

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	Texture* m_Texture;
};