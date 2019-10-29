// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "LightShader.h"
#include "TextureShader.h"
#include "VerticalBlurShader.h"
#include "HorizontalBlurShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void firstPass();
	void downSample();
	void verticalBlur();
	void horizontalBlur();
	void upSample();
	void finalPass();
	void gui();

private:
	CubeMesh* cubeMesh;
	OrthoMesh* orthoMesh;
	LightShader* lightShader;
	TextureShader* textureShader;

	RenderTexture* renderTexture;
	RenderTexture* downRenderTexture;
	RenderTexture* horizontalBlurTexture;
	RenderTexture* verticalBlurTexture;
	RenderTexture* upRenderTexture;
	VerticalBlurShader* verticalBlurShader;
	HorizontalBlurShader* horizontalBlurShader;

	Light* light;
};

#endif