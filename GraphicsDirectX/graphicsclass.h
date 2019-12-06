
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"
#include "TerrainClass.h"
#include "TerrainShaderClass.h"
#include "colorshaderclass.h"
#include "MiniMapClass.h"
#include "SkyDomeClass.h"
#include "SkyDomeShaderClass.h"
#include "SkyPlaneClass.h"
#include "skyplaneshaderclass.h"
#include "foliageclass.h"
#include "foliageShaderClass.h"
#include "fireShaderClass.h"
#include "ParticleShaderClass.h"
#include "ParticleSystemClass.h"




const bool VSYNC_ENABLED = true;
const bool FULL_SCREEN = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;
const int modelCount = 22;
const int grassCount = 30000;

enum OBJECTNAME {
	EFFECT_FIRE,
	EFFECT_FIRE2,
	CARROT01,
	CARROT02,
	CARROT03,
	CARROT04,
	CARROT05,
	CARROT06,
	CARROT07,
	CARROT08,
	CARROT09,
	CARROT010,
	//CARROT011,
	//CARROT012,
	BIRD,
	BIRD2,
	BIRD3,
	DOG,
	DOG2,
	BASKET,
	ROCK1,
	ROCK2,
	ROCK3,
	ROCK4
};

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	//bool Frame(int, int);
	bool Frame(int, int , float, int, int, int, int);
	bool Render(float, float);

	void moveForward( float);
	void moveBackward(float);
	void moveRightward(float);
	void moveLeftward(float);
	void mouseMove(float, int, int);
	bool IsEatenCarrot(int);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* m_Model[modelCount];
	ModelClass* player;
	
	LightShaderClass* m_LightShader;
	LightClass* m_Light, *m_Light2;

	ColorShaderClass* m_ColorShader;

	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;

	SkyPlaneClass* m_SkyPlane;
	SkyPlaneShaderClass* m_SkyPlaneShader;

	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;

	TextureShaderClass* m_TextureShader;
	//BitmapClass* m_Bitmap;
	MiniMapClass* m_MiniMap;
	TextClass* m_Text;
	
	FoliageClass* m_Foliage;
	FoliageClass* m_Foliage1;
	FoliageShaderClass* m_FoliageShader;
	
	FireShaderClass* m_FireShader;
	
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;

	float rotationX, rotationY, rotationZ;
	D3DXVECTOR3 position, rotation;
	D3DXVECTOR3 p_position;
	int carrotCount;
	



	
};

#endif