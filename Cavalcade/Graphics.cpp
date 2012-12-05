/****************************************/
/* Graphics system						*/
/*										*/
/* David Blalock 2012					*/
/****************************************/
#include "Graphics.h"

Graphics::Graphics() : m_D3D(0), m_Camera(0), m_ShaderManager(0), m_Model(0), m_AmbientLight(0)
{

}

Graphics::~Graphics()
{

}

bool Graphics::Initialize(HWND hwnd, HINSTANCE hInstance, int screenWidth, int screenHeight)
{
	bool result;
	XMFLOAT4X4 baseViewMatrix;

	m_D3D = new D3DClass;
	if (!m_D3D)
		return false;
	
	result = m_D3D->Initialize(hwnd, hInstance);
	if (!result)
		return false;

// Main Camera //
	m_Camera = new CameraClass;
	if (!m_Camera)
		return false;

	m_Camera->SetPosition(0.0f, 0.0f, -120.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);
	m_Camera->UpdateView();		// Calculate initial view matrix
	m_Camera->GetViewMatrix(baseViewMatrix);

	m_ShaderManager = new ShaderManager;
	if (!m_ShaderManager)
		return false;

	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
		return false;

	// Text rendering system //
	/*
	m_Text = new TextClass;
	if (!m_Text)
		return false;

	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
		return false;
	*/

// Test ambient light textured model //
	m_Model = new Model;
	if (!m_Model)
		return false;

	result = m_Model->Initialize(m_D3D->GetDevice(), L"models\\torus.obj", L"seafloor.dds");
	if (!result)
	{
		//TODO: Return more detailed error messages
		return false;
	}

	// Lighting //
	m_AmbientLight = new AmbientLight;
	if (!m_AmbientLight)
		return false;

	m_AmbientLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_AmbientLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_AmbientLight->SetDirection(0.0f, -1.0f, 0.0f);

	return true;
}

void Graphics::Shutdown()
{
	if (m_AmbientLight)
	{
		delete m_AmbientLight;
		m_AmbientLight = 0;
	}

	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	/*
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}
	*/

	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool Graphics::Update()
{
	Render();

	return true;
}

void Graphics::Render()
{
	XMFLOAT4X4 worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	m_D3D->BeginScene();

	m_Camera->UpdateView();

	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

/// Begin 2D rendering ///
	m_D3D->ZBufferDisable();
	m_D3D->AlphaBlendOn();

	//m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);

	m_D3D->AlphaBlendOn();
	m_D3D->ZBufferEnable();
/// End 2D rendering ///

/// Begin 3D rendering ///
	// Put models on the pipeline //
	m_Model->Render(m_D3D->GetDeviceContext());

	m_ShaderManager->RenderAmbientColorShader(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetRotationMatrix(), viewMatrix, projectionMatrix,
											  m_Model->GetTexture(), m_AmbientLight->GetDirection(), m_AmbientLight->GetAmbientColor(),
											  m_AmbientLight->GetDiffuseColor());

	m_D3D->EndScene();

	return;
}

bool Graphics::CreateObjectFromFile(char* filename)
{


	return true;
}

void Graphics::MoveCamera(bool forward, bool backward, bool left, bool right, bool up, bool down)
{
	if (forward)
		m_Camera->MoveCameraFwd();
	if (backward)
		m_Camera->MoveCameraBack();
	if (left)
		m_Camera->MoveCameraLeft();
	if (right)
		m_Camera->MoveCameraRight();
	if (up)
		m_Camera->MoveCameraUp();
	if (down)
		m_Camera->MoveCameraDown();

	return;
}

void Graphics::RotateCamera(float x, float y, float z)
{
	m_Camera->RotateCamera(x, y, z);

	return;
}