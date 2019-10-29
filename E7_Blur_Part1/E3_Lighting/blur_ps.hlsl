// Blur pixel/fragment shader
// Basic fragment shader for rendering textured geometry

// Texture and sampler registers
Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);

cbuffer ScreenSizeBuffer : register(b0)
{
	float screenWidth;
	float screenHeight;
	float2 padding;
}
struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


float4 main(InputType input) : SV_TARGET
{
	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	float4 colour;

	// Initialise the colour to black
	colour = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Determine the floating point size of a texel with this specific width
	float texelWidth = 1.0f / screenWidth;
	float texelHeight = 1.0f / screenHeight;

	// Add the nine pixel to the colour
	colour += texture0.Sample(Sampler0, input.tex);
	colour += texture0.Sample(Sampler0, input.tex + float2(-texelWidth, -texelHeight));
	colour += texture0.Sample(Sampler0, input.tex + float2(0.0f, texelHeight));
	colour += texture0.Sample(Sampler0, input.tex + float2(texelWidth, -texelHeight));
	colour += texture0.Sample(Sampler0, input.tex + float2(-texelWidth, 0.0f));
	colour += texture0.Sample(Sampler0, input.tex + float2(texelWidth, 0.0f));
	colour += texture0.Sample(Sampler0, input.tex + float2(-texelWidth, texelHeight));
	colour += texture0.Sample(Sampler0, input.tex + float2(0.0f, texelHeight));
	colour += texture0.Sample(Sampler0, input.tex + float2(texelWidth, texelHeight));

	colour /= 9.0f;

	// Set the alpha channel to one
	colour.a = 1.0f;

	return colour;
}