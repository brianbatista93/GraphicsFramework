static float3 vertices[3] = {
	float3(0.0, 0.5, 0.0),
	float3(0.5, -0.5, 0.0),
	float3(-0.5, -0.5, 0.0)
};

struct V2F {
	float4 Position : SV_POSITION;
};

V2F main(uint vertexID : SV_VertexID)
{
	V2F OUT = (V2F)0;

	OUT.Position = float4(vertices[vertexID], 1.0);

	return OUT;
}