RWTexture2D<uint4> output : register(u0);

[numthreads(1, 1, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
	uint3 val = DTid % 32;
	output[DTid.xy] = uint4(val, 1);
}