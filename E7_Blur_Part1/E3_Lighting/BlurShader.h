#pragma once

#include "BaseShader.h"

using namespace std;
using namespace DirectX;

class BlurShader : public BaseShader
{
public:
	struct ScreenSizeBufferType
	{
		float width;
		float height;
		XMFLOAT2 padding;
	};

	BlurShader(ID3D11Device* device, HWND hwnd);
	~BlurShader();

	void setShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, float screenWidth, float screenHeight);

private:
	void initShader(const wchar_t* vs, const wchar_t* ps);

private:
	ID3D11Buffer * matrixBuffer;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* screenBuffer;
};

