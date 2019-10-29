// Tessellation quad Mesh
// A simple quad mesh used for tessellation demonstration.
// Different output type, instead of  Trianglelist, a 4 control point patch list.
// The tessellator uses these points to generate new geometry but sub-division.
// Due to change in geometry type the sendData() function has been overridden.

#ifndef _TESSELLATIONQUADMESH_H_
#define _TESSELLATIONQUADMESH_H_

#include "BaseMesh.h"

using namespace DirectX;

class TessellationQuadMesh : public BaseMesh
{

public:
	TessellationQuadMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	~TessellationQuadMesh();

	void sendData(ID3D11DeviceContext*);

protected:
	void initBuffers(ID3D11Device* device);

};

#endif