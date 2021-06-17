uniform float4 color : register(c0);
uniform Texture2D<uint4> tex : register(t0);

struct V2F
{
	float4 Position : SV_POSITION;
};

float4 main(in V2F IN) : SV_TARGET
{
	return color * tex.Load(IN.Position.xyz, 0);
}