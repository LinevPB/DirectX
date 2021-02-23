struct ps_input
{
	float4 inPos : SV_POSITION;
	float3 inColor : COLOR;
};

float4 main(ps_input input) : SV_Target
{
	return float4(input.inColor, 1.0f);
}