/**
	main_ps.hlsl
*/

struct OutputVS
{
	float4 posH : SV_POSITION;
	float4 colors : COLOR;
};


float4 main(OutputVS input) : SV_Target
{
	return input.colors;
}