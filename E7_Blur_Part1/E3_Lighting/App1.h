// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "LightShader.h"
#include "TextureShader.h"
#include "BlurShader.h"


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
	void blurPass();
	void finalPass();
	void gui();

private:
	LightShader* shader;
	SphereMesh* mesh;
	Light* light;

	LightShader* lightShader;
	TextureShader* textureShader;
	BlurShader* blurShader;

	OrthoMesh* orthoMesh;

	RenderTexture* firstRenderTexture;
	RenderTexture* blurRenderTexture;

	int screenW, screenH;
};

#endif