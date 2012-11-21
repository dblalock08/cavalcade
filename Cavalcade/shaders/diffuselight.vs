// Variables //
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	//float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType VS_Main(VertexInputType vsInput)
{
	PixelInputType vsOutput;
	
	vsInput.position.w = 1.0f;
	
	vsOutput.position = mul(vsInput.position, worldMatrix);
	vsOutput.position = mul(output.position, viewMatrix);
	vsOutput.position = mul(output.position, projectionMatrix);
	
	vsOutput.tex = vsInput.tex;
	
	vsOutput.normal = mul(vsInput.normal, (float3x3)worldMatrix);
	
	vsOutput.normal = normalize(vsOutput.normal);
	
	return vsOutput;
}