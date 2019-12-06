#pragma once
#include "d3dclass.h"

class TextureClass;

class SkyPlaneClass
{
private:
	struct SkyPlaneType
	{
		float x, y, z;
		float tu, tv;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	SkyPlaneClass();
	SkyPlaneClass(const SkyPlaneClass&);
	~SkyPlaneClass();

	bool Initialize(ID3D11Device*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	void Frame();

	int GetIndexCount();
	ID3D11ShaderResourceView* GetCloudTexture();
	ID3D11ShaderResourceView* GetPerturbTexture();
	
	float GetScale();
	float GetBrightness();
	float GetTranslation();

private:
	bool InitializeSkyPlane(int, float, float, float, int);
	void ShutdownSkyPlane();

	bool InitializeBuffers(ID3D11Device*, int);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTextures();

private:
	SkyPlaneType* m_skyPlane = nullptr;
	int m_vertexCount = 0;
	int m_indexCount = 0;
	ID3D11Buffer *m_vertexBuffer = nullptr;
	ID3D11Buffer *m_indexBuffer = nullptr;
	TextureClass *m_CloudTexture = nullptr;
	TextureClass *m_PerturbTexture = nullptr;
	float m_scale = 0.0f;
	float m_brightness = 0.0f;
	float m_translation = 0.0f;
};