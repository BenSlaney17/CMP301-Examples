// Texture pixel/fragment shader
// Basic fragment shader for rendering textured geometry

// Texture and sampler registers
Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);

cbuffer CameraBuffer : register(b0)
{
	float3 cameraPos;
	float padding;
}

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 worldPos : TEXCOORD1;
	float3 normal : NORMAL;
};


float4 main(InputType input) : SV_TARGET
{
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	float4 textureColor = texture0.Sample(Sampler0, input.tex);
	
	float4 camPos = float4(cameraPos.x, cameraPos.y, cameraPos.z, 1.f);

	camPos.xyz /= input.position.w;
	camPos.xz *= float2(0.5, -0.5);
	camPos.xz += 0.5f;
	camPos.xz *= float2(1200, 675);

	input.position.xz *= float2(1200, 675);

	if (distance(input.position.xz, cameraPos.xz) < 10)
		return float4(0.1f, 0.9f, 0.4f, 1.f);
	else
		return textureColor;
}