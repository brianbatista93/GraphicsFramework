static float3 vertices[3] = {
	float3(0.0, 0.5, 0.0),
	float3(0.5, -0.5, 0.0),
	float3(-0.5, -0.5, 0.0)
};

float4 main(uint vertexID : SV_VertexID) : SV_POSITION
{
	return float4(vertices[vertexID], 1.0);
}