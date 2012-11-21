/* Simple flat color effect */

// Variables //
cbuffer cbChangeEachFrame : register (b0)
{
	matrix <float, 4, 4> worldMatrix;
};

cbuffer cbNeverChange : register (b1)
{
	matrix <float, 4, 4> viewMatrix;
};

cbuffer cbChangeOnResize : register (b2)
{
	matrix <float, 4, 4> projectionMatrix;
};

struct VS_Input
{
	float4 pos : POSITION;
	float4 color : COLOR;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

// Functions //
PS_Input VS_Main(VS_Input vertex)
{
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, worldMatrix);
	vsOut.pos = mul(vsOut.pos, viewMatrix);
	vsOut.pos = mul(vsOut.pos, projectionMatrix);
	vsOut.color = vertex.color;
	
	return vsOut;
}

float4 PS_Main(PS_Input fragment) : SV_TARGET
{
	return fragment.color;
}

// Technique //