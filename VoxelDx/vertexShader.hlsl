struct vs_input
{
	float2 inPos : POSITION;
	float3 inColor : COLOR;
};

struct vs_output
{
	float4 outPos : SV_POSITION;
	float3 outColor : COLOR;
};

vs_output main(vs_input input)
{
	vs_output output;
	output.outPos = float4(input.inPos, 0.0f, 1.0f);
	output.outColor = input.inColor;

	return output;
}