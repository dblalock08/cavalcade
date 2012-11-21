/****************************************/
/* Basic model that supports flat color	*/
/* shading only; primarily used for		*/
/* testing new models.					*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "ColorModel.h"

ColorModel::ColorModel() : m_mesh(0)
{

}

ColorModel::ColorModel(const ColorModel& other)
{

}

ColorModel::~ColorModel()
{

}

bool ColorModel::Initialize(ID3D11Device* device, WCHAR* modelFilename)
{
	bool result;

	m_mesh = new Mesh;
	if (!m_mesh)
		return false;

	result = m_mesh->Initialize(device, modelFilename);
	if (!result)
		return false;

	return true;
}

void ColorModel::Shutdown()
{
	ReleaseTextures();

	ReleaseModel();

	return;
}

void ColorModel::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext);

	return;
}

void ColorModel::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride, offset;

	stride = 28;	// sizeof(VertexType) returns incorrect size due to structure padding
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, m_mesh->GetVertexBufferPtr(), &stride, &offset);
	deviceContext->IASetIndexBuffer(m_mesh->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void ColorModel::ReleaseModel()
{
	if (m_mesh)
	{
		m_mesh->Shutdown();
		delete m_mesh;
		m_mesh = 0;
	}

	return;
}

void ColorModel::ReleaseTextures()
{


	return;
}