// Lab1.cpp
// Lab 1 example, simple coloured triangle mesh
#include "App1.h"

App1::App1()
{

}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in, bool VSYNC, bool FULL_SCREEN)
{
	// Call super/parent init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in, VSYNC, FULL_SCREEN);

	// Create Mesh object and shader object

	topCamera = new Camera;
	topCamera->setPosition(50.0f, 80.0f, 50.f);
	topCamera->setRotation(90.0f, 0.0f, 0.f);

	textureMgr->loadTexture(L"brick", L"res/bunny.png");
	cubeMesh = new CubeMesh(renderer->getDevice(), renderer->getDeviceContext());
	sphereMesh = new SphereMesh(renderer->getDevice(), renderer->getDeviceContext());
	planeMesh = new PlaneMesh(renderer->getDevice(), renderer->getDeviceContext());
	leftOrthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth / 4, screenHeight / 4, -screenWidth / 2.7, screenHeight / 2.7);
	rightOrthoMesh = new OrthoMesh(renderer->getDevice(), renderer->getDeviceContext(), screenWidth / 4, screenHeight / 4, screenWidth / 2.7, screenHeight / 2.7);

	lightShader = new LightShader(renderer->getDevice(), hwnd);
	textureShader = new TextureShader(renderer->getDevice(), hwnd);
	greyscaleShader = new GreyscaleLightShader(renderer->getDevice(), hwnd);

	leftRenderTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);		
	rightRenderTexture = new RenderTexture(renderer->getDevice(), screenWidth, screenHeight, SCREEN_NEAR, SCREEN_DEPTH);

	light = new Light;
	light->setAmbientColour(0.0f, 0.0f, 0.0f, 1.0f);
	light->setDiffuseColour(1.0f, 1.0f, 1.0f, 1.0f);
	light->setDirection(0.7f, -0.5f, 0.7f);
}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	// Release the Direct3D object.

}


bool App1::frame()
{
	bool result;

	result = BaseApplication::frame();
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool App1::render()
{
	// Render first pass to render texture
	firstPass();

	// Render second pass to render texture
	secondPass();

	// Render final pass to frame buffer
	finalPass();

	return true;
}

void App1::firstPass()
{
	// Set the render target to be the render to texture and clear it
	leftRenderTexture->setRenderTarget(renderer->getDeviceContext());
	leftRenderTexture->clearRenderTarget(renderer->getDeviceContext(), 0.8f, 0.2f, 0.2f, 1.0f);

	// Get matrices
	// create a camera matrix to look down
	topCamera->update();

	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = topCamera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	// Render shape with simple lighting shader set.
	planeMesh->sendData(renderer->getDeviceContext());
	lightShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"), light, 1);
	lightShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::secondPass()
{
	// Set the render target to be the render to texture and clear it
	rightRenderTexture->setRenderTarget(renderer->getDeviceContext());
	rightRenderTexture->clearRenderTarget(renderer->getDeviceContext(), 0.2f, 0.2f, 0.8f, 1.0f);

	// Get matrices
	// create a camera matrix to look down
	topCamera->update();

	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = topCamera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	// Render shape with simple lighting shader set.
	planeMesh->sendData(renderer->getDeviceContext());
	lightShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"), light, 1);
	lightShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	renderer->setBackBufferRenderTarget();
}

void App1::finalPass()
{
	// Clear the scene. (default blue colour)
	renderer->beginScene(0.39f, 0.58f, 0.92f, 1.0f);

	// Get matrices
	camera->update();
	XMMATRIX worldMatrix = renderer->getWorldMatrix();
	XMMATRIX viewMatrix = camera->getViewMatrix();
	XMMATRIX projectionMatrix = renderer->getProjectionMatrix();

	// Render normal scene, with light shader set.
	planeMesh->sendData(renderer->getDeviceContext());
	lightShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, textureMgr->getTexture(L"brick"), light, 1);
	lightShader->render(renderer->getDeviceContext(), planeMesh->getIndexCount());


	// RENDER THE RENDER TEXTURE SCENE
	// Requires 2D rendering and an ortho mesh.
	renderer->setZBuffer(false);
	//render left render texture
	XMMATRIX orthoMatrix = renderer->getOrthoMatrix();  // ortho matrix for 2D rendering
	XMMATRIX orthoViewMatrix = camera->getOrthoViewMatrix();	// Default camera position for orthographic rendering

	leftOrthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, leftRenderTexture->getShaderResourceView());
	textureShader->render(renderer->getDeviceContext(), leftOrthoMesh->getIndexCount());

	//render right render texture
	//XMMATRIX orthoMatrix = renderer->getOrthoMatrix();  // ortho matrix for 2D rendering
	//XMMATRIX orthoViewMatrix = camera->getOrthoViewMatrix();	// Default camera position for orthographic rendering

	rightOrthoMesh->sendData(renderer->getDeviceContext());
	textureShader->setShaderParameters(renderer->getDeviceContext(), worldMatrix, orthoViewMatrix, orthoMatrix, rightRenderTexture->getShaderResourceView());
	//textureShader->render(renderer->getDeviceContext(), rightOrthoMesh->getIndexCount());
	renderer->setZBuffer(true);

	// Render GUI
	gui();

	// Present the rendered scene to the screen.
	renderer->endScene();
}

void App1::gui()
{
	// Force turn off unnecessary shader stages.
	renderer->getDeviceContext()->GSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->HSSetShader(NULL, NULL, 0);
	renderer->getDeviceContext()->DSSetShader(NULL, NULL, 0);

	// Build UI
	ImGui::Text("FPS: %.2f", timer->getFPS());
	ImGui::Checkbox("Wireframe mode", &wireframeToggle);

	// Render UI
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

