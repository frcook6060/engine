/**
	main_ps.hlsl
*/

struct OutputVS
{
	float4 posH : SV_POSITION;
	float4 colors : COLOR;
	float2 texCoords : TEXCOORD;
};

Texture2D tex0;
SamplerState samplerState0;

float4 main(OutputVS input) : SV_Target
{
	float4 colors = tex0.Sample(samplerState0, input.texCoords);
	colors.rgb *= input.colors.rgb;
	return colors;
	//return input.colors;
}