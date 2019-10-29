#pragma once

#include "DXF.h"

using namespace std;
using namespace DirectX;

class MinimapShader : public BaseShader
{
private:
	struct CameraBufferType
	{
		XMFLOAT3 position;
		float padding;
	};

public:
	MinimapShader(ID3D11Device* device, HWND hwnd);
	~MinimapShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, XMFLOAT3 cameraPos);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* cameraBuffer;
};

