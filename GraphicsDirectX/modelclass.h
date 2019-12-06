#pragma once

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


#include "textureclass.h"

#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>

using namespace std;

#define XM_PI 3.14

class ModelClass
{
private:
	string m_temp;
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	char* model;
	typedef struct
	{
		float x, y, z;
	}VertexTypeF;

	typedef struct
	{
		int vIndex1, vIndex2, vIndex3;
		int tIndex1, tIndex2, tIndex3;
		int nIndex1, nIndex2, nIndex3;
	}FaceType;

	struct CollisionBound
	{
		D3DXVECTOR3	center;
		float radius;
	};
public:

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView* GetTexture1()
	{
		return m_Texture1->GetTexture();
	}
	ID3D11ShaderResourceView* GetTexture2()
	{
		return m_Texture2->GetTexture();
	}
	ID3D11ShaderResourceView* GetTexture3()
	{
		return m_Texture3->GetTexture();
	}

	bool ReadFileCounts(char*, int&, int&, int&, int&);
	bool LoadDataStructures(char*, int, int, int, int);
	bool LoadObject(char * filename);

	void SetPosition(float, float, float);
	void SetPosition(D3DXVECTOR3);
	D3DXVECTOR3 GetPosition();

	void SetRotation(D3DXVECTOR3);
	D3DXVECTOR3 GetRotation();

	void SetCollsionSphere(D3DXVECTOR3, float);
	void SetCollsionSphereCenter(D3DXVECTOR3);
	void GetCollsionSphere(D3DXVECTOR3&, float&);

private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR * filename);
	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*, WCHAR*);
	void ReleaseTextures();

	bool LoadModel(char*);
	bool LoadModelForEffect(const char*);
	void ReleaseModel();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_Texture;
	TextureClass* m_Texture1 = nullptr;
	TextureClass* m_Texture2 = nullptr;
	TextureClass* m_Texture3 = nullptr;
	ModelType* m_model;
	CollisionBound* m_sphere = nullptr;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
};
#endif