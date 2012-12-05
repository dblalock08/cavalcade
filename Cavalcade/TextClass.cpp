/*#include "TextClass.h"

TextClass::TextClass() : m_Font(0), m_TextShader(0), m_sentence(0)
{

}

TextClass::TextClass(const TextClass& other)
{

}

TextClass::~TextClass()
{

}

bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd,
						   int screenWidth, int screenHeight, XMFLOAT4X4 baseViewMatrix)
{
	bool result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;
	m_baseViewMatrix = baseViewMatrix;

	m_Font = new FontClass;
	if (!m_Font)
	{
		return false;
	}
	result = m_Font->Initialize(device, "text\\consola22_2048x26.txt", L"text\\consola22_2048x26.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize text font", L"Error", MB_OK);
		return false;
	}

	m_TextShader = new FlatTextShader;
	if (!m_TextShader)
	{
		return false;
	}
	result = m_TextShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	result = InitializeSentence(&m_sentence, 256, device);
	if (!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	ReleaseSentence(&m_sentence);

	if (m_TextShader)
	{
		m_TextShader->Shutdown();
		delete m_TextShader;
		m_TextShader = 0;
	}

	if (m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}

void TextClass::Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 orthoMatrix)
{
	RenderSentence(deviceContext, m_sentence, worldMatrix, orthoMatrix);

	return;
}

bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	*sentence = new SentenceType;
	if (!*sentence)
	{
		return false;
	}

	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	(*sentence)->maxLength = maxLength;
	
	(*sentence)->vertexCount = 6 * maxLength;
	(*sentence)->indexCount = (*sentence)->vertexCount;

	vertices = new VertexType[(*sentence)->vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[(*sentence)->indexCount];
	if (!indices)
	{
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));
	
	for (int i = 0; i < (*sentence)->indexCount; ++i)
	{
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;

	return true;
}

bool TextClass::UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red,
							   float green, float blue, ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType*  verticesPtr;

	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	numLetters = (int)strlen(text);
	if (numLetters > sentence->maxLength)
	{
		return false;
	}

	vertices = new VertexType[sentence->vertexCount];
	if (!vertices)
	{
		return false;
	}

	memset(vertices, 0, sizeof(VertexType) * sentence->vertexCount);

	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, sizeof(VertexType) * sentence->vertexCount);

	deviceContext->Unmap(sentence->vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;

	return true;
}

void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if (*sentence)
	{
		if ((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		if ((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		delete *sentence;
		*sentence = 0;
	}

	return;
}

void TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, XMFLOAT4X4 worldMatrix, XMFLOAT4X4 orthoMatrix)
{
	unsigned int stride, offset;
	XMFLOAT4 pixelColor;
	
	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pixelColor = XMFLOAT4(sentence->red, sentence->green, sentence->blue, 1.0f);

	m_TextShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), pixelColor);

	return;
}
*/