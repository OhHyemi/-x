////////////////////////////////////////////////////////////////////////////////
// Filename: skyplane_ps.hlsl
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
Texture2D cloudTexture : register(t0);
Texture2D perturbTexture : register(t1);
SamplerState SampleType;

cbuffer SkyBuffer
{
	float translation;
	float scale;
	float brightness;
	float padding;
};


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 SkyPlanePixelShader(PixelInputType input) : SV_TARGET
{
	float4 perturbValue;
	float4 cloudColor;


	// �ؽ�ó ��ǥ ���ø� ��ġ�� ��ȯ ������ ��ȯ�մϴ�.
	input.tex.x = input.tex.x + translation;

	// ������ �ؽ�ó ��ǥ�� ����Ͽ� ���� �ؽ�ó���� �ؽ�ó ���� ���ø��մϴ�.
	perturbValue = perturbTexture.Sample(SampleType, input.tex);

	// ���� ���� ���� �������� ���մϴ�.
	perturbValue = perturbValue * scale;

	// ���� �� �ؽ�ó ��ǥ ���ø� ��ġ�� ��� ���� ��ȯ ���� �ؽ�ó ��ǥ�� �߰��մϴ�.
	perturbValue.xy = perturbValue.xy + input.tex.xy + translation;

	// ���� ���� ���ø� ��ǥ�� ����Ͽ� ���� �ؽ�ó���� ������ ���ø��մϴ�.
	cloudColor = cloudTexture.Sample(SampleType, perturbValue.xy);

	// ��� ������ ���� ������ ���Դϴ�.
	cloudColor = cloudColor * brightness;

	return cloudColor;
}