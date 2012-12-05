/**
 * Handles data for text sentences.
 */
#pragma once

#include "FontClass.h"
#include "FlatTextShader.h"

class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, XMFLOAT4X4);
	void Shutdown();
	void Render(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	void RenderSentence(ID3D11DeviceContext*, SentenceType*, XMFLOAT4X4, XMFLOAT4X4);

private:
	FontClass* m_Font;
	int m_screenWidth, m_screenHeight;
	XMFLOAT4X4 m_baseViewMatrix;
	SentenceType* m_sentence;

	FlatTextShader* m_TextShader;
};