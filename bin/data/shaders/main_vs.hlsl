/**
	main_vs.hlsl
	
	This is the main shader for my game engine...
	There will be other for specific types of 
	rendering...
*/

cbuffer ConstVS
{
	float4x4 proj;
	float4x4 view;
	float4x4 model;
};

// Attributes
struct InputVS
{
	float3 vertices : POSITION;
};

struct OutputVS
{
	float4 posH : SV_POSITION;
};

OutputVS main(InputVS input)
{
	OutputVS output;
	output.posH = mul(model, float4(input.vertices, 1.0));
	output.posH = mul(view, output.posH);
	output.posH = mul(proj, output.posH);
	return output;
}
