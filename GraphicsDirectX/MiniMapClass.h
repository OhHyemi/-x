#pragma once


class BitmapClass;
class TextureShaderClass;


class MiniMapClass
{
public:
	MiniMapClass();
	MiniMapClass(const MiniMapClass&);
	~MiniMapClass();

	bool Initialize(ID3D11Device*, HWND, int, int, D3DXMATRIX , float, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX , D3DXMATRIX , TextureShaderClass*);
	
	void PositionUpdate(float, float);

private:
	int m_mapLocationX = 0;
	int m_mapLocationY = 0;
	int m_pointLocationX = 0;
	int m_pointLocationY = 0;
	float m_mapSizeX = 0;
	float m_mapSizeY = 0;
	float m_terrainWidth = 0;
	float m_terrainHeight = 0;
	D3DXMATRIX m_viewMatrix;
	BitmapClass *m_MiniMapBitmap = nullptr;
	BitmapClass *m_Border = nullptr;
	BitmapClass *m_Point = nullptr;
};