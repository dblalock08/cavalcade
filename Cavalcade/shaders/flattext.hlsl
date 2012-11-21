// GLOBALS //
cbuffer PerFrameBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
}

// TYPEDEFS //
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 FlatText_VS( float4 pos : POSITION ) : SV_POSITION
{
	PixelInputType output;

	input.position.w = 1.0f;

	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	return output;
}

// GLOBALS //
Texture2D shaderTexture;
SamplerState SampleType;

cbuffer PixelBuffer
{
	float4 pixelColor;
};

// TYPEDEFS //
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

float4 FlatText_PS(PixelInputType input) : SV_TARGET
{
	float4 color;

	color = shaderTexture.Sample(SampleType, input.tex);

	if (color.r == 0.0f)
	{
		color.a = 0.0f;
	}
	else
	{
		color.a = 1.0f;
		color = color * pixelColor;
	}

	return color;
}