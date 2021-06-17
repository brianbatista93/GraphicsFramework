struct GSOutput
{
	float4 pos : SV_POSITION;
};

static float4 center[3] = {
	float4(0,0,0,1),
	float4(0.5,0,0,1),
	float4(0,0.5,0,1),
};

[maxvertexcount(3 * 10)]
void main(
	triangle float4 input[3] : SV_POSITION,
	inout TriangleStream< GSOutput > output
)
{
	for (uint k = 0; k < 10; k++) {
		for (uint i = 0; i < 3; i++)
		{
			GSOutput element;
			element.pos = input[i] + center[k % 3] * k;
			output.Append(element);
		}
		output.RestartStrip();
	}
}