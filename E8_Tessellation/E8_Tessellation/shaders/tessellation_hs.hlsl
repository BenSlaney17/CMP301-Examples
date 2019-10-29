// Tessellation Hull Shader
// Prepares control points for tessellation

cbuffer TesselationBuffer : register(b0)
{
	float4 edges;
	float2 insides;
	float2 padding;
};

struct InputType
{
    float3 position : POSITION;
    float4 colour : COLOR;
};

struct ConstantOutputType
{
    float edges[4] : SV_TessFactor;
    float insides[2] : SV_InsideTessFactor;
};

struct OutputType
{
    float3 position : POSITION;
    float4 colour : COLOR;
};

ConstantOutputType PatchConstantFunction(InputPatch<InputType, 4> inputPatch, uint patchId : SV_PrimitiveID)
{    
    ConstantOutputType output;


    // Set the tessellation factors for the three edges of the triangle.
	output.edges[0] = edges.x;
	output.edges[1] = edges.y;
	output.edges[2] = edges.z;
	output.edges[3] = edges.w;

    // Set the tessellation factor for tessallating inside the triangle.
	output.insides[0] = insides.x;
	output.insides[1] = insides.y;

    return output;
}


[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("PatchConstantFunction")]
OutputType main(InputPatch<InputType, 4> patch, uint pointId : SV_OutputControlPointID, uint patchId : SV_PrimitiveID)
{
    OutputType output;


    // Set the position for this control point as the output position.
    output.position = patch[pointId].position;

    // Set the input colour as the output colour.
    output.colour = patch[pointId].colour;

    return output;
}