#pragma once
#include"d3dclass.h"

class TextureClass;


class FoliageClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

	struct FoliageType
	{
		float x, z;
		float r, g, b;
	};

	struct InstanceType
	{
		D3DXMATRIX matrix;
		D3DXVECTOR3 color;
	};

public:
	FoliageClass();
	FoliageClass(const FoliageClass&);
	~FoliageClass();

	bool Initialize(ID3D11Device*, const WCHAR*, int);
	void Shutdown();
	void Render(ID3D11DeviceContext*);
	bool Frame(D3DXVECTOR3, ID3D11DeviceContext*);

	int GetVertexCount();
	int GetInstanceCount();

	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, const WCHAR*);
	void ReleaseTexture();

	bool GeneratePositions();

private:
	int m_foliageCount = 0;
	FoliageType* m_foliageArray = nullptr;
	InstanceType* m_Instances = nullptr;
	ID3D11Buffer *m_vertexBuffer = nullptr;
	ID3D11Buffer *m_instanceBuffer = nullptr;
	int m_vertexCount = 0;
	int m_instanceCount = 0;
	TextureClass* m_Texture = nullptr;
	float m_windRotation = 0.0f;
	int m_windDirection = 0;
};