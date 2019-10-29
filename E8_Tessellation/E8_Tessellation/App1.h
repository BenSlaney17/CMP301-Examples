// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "DXF.h"	// include dxframework
#include "TessellationShader.h"
#include "TessellationQuadMesh.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input* in, bool VSYNC, bool FULL_SCREEN);

	bool frame();

protected:
	bool render();
	void gui();

private:
	TessellationMesh* mesh;
	TessellationShader* shader;
	TessellationQuadMesh* quadMesh;

	float edge1, edge2, edge3, edge4, inside1, inside2;
};

#endif