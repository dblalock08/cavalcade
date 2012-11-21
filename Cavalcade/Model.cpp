/****************************************/
/* Game geometry model					*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Model.h"

Model::Model() : m_Mesh(0), m_Texture(0)
{

}

Model::Model(const Model& other)
{

}

Model::~Model()
{

}

// Initialization //
bool Model::Initialize(ID3D11Device* device, WCHAR* modelFilename, WCHAR* textureFilename)
{
	bool result;

	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);

// Geometry //
	m_Mesh = new Mesh;
	if (!m_Mesh)
		return false;

	result = m_Mesh->Initialize(device, modelFilename);
	if (!result)
		return false;

// Texturing //
	m_Texture = new Texture;
	if (!m_Texture)
		return false;

	result = m_Texture->Initialize(device, textureFilename);
	if (!result)
		return false;

	return true;
}

// Run //
void Model::Render(ID3D11DeviceContext* deviceContext)
{
	// Rotate the model
	float yaw, pitch, roll;

	m_rotation.y += (float)XM_PI * 0.0005f;
	m_rotation.x += (float)XM_PI * 0.0005f;

	m_position.x += 1.0f;

	if (m_position.x > 50)
		m_position.x -= 50;

	if (m_rotation.x > 360.0f)
		m_rotation.x -= 360.0f;
	if (m_rotation.y > 360.0f)
		m_rotation.y-= 360.0f;
	if (m_rotation.z > 360.0f)
		m_rotation.z -= 360.0f;

	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	pitch = 0.0f;
	yaw = 0.0f;
	roll = 0.0f;

	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMStoreFloat4x4(&m_rotationMatrix, rotationMatrix);

	RenderBuffers(deviceContext);

	return;
}

void Model::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = m_Mesh->GetStride();
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, m_Mesh->GetVertexBufferPtr(), &stride, &offset);
	deviceContext->IASetIndexBuffer(m_Mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

// Cleanup and Shutdown //
void Model::Shutdown()
{	
	ReleaseModel();

	return;
}

void Model::ReleaseModel()
{
	if (m_Mesh)
	{
		m_Mesh->Shutdown();
		delete m_Mesh;
		m_Mesh = 0;
	}

	return;
}

void Model::ReleaseTextures()
{
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}