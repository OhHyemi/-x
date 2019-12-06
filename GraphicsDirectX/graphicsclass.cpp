
#include "graphicsclass.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;



GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	*m_Model = 0;
	m_LightShader = 0;
	m_Light = 0;
	

	player = 0;

	m_Terrain = 0;
	m_TerrainShader = 0;

	m_SkyDome = 0;
	m_SkyDomeShader = 0;

	m_SkyPlane = 0;
	m_SkyDomeShader = 0;

	m_TextureShader = 0;
	//m_Bitmap = 0;
	m_Text = 0;
	m_MiniMap = 0;
	m_FireShader = 0;
	m_Foliage = 0;
	m_Foliage1 = 0;
	m_FoliageShader = 0;

	m_ParticleShader = 0;
	m_ParticleSystem = 0;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
	
}


GraphicsClass::GraphicsClass(const GraphicsClass& other) {}

GraphicsClass::~GraphicsClass() {}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	{
		player = new ModelClass;

		result = player->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/rabbit.obj", (WCHAR*)L"./Engine/data/rabbit.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}

		player->SetPosition(D3DXVECTOR3(15.0f, 0.5f, 15.0f));
		player->SetCollsionSphere(D3DXVECTOR3(15.0f, 0.0f, 15.0f), 2.0f);

		//========================================================================================

		for (int i = 0; i < modelCount; i++)
			m_Model[i] = new ModelClass;


		// Initialize the model object.
		result = m_Model[EFFECT_FIRE]->Initialize(m_D3D->GetDevice()
			, const_cast<char*>("./Engine/data/fire/square.txt")
			, const_cast<WCHAR*>(L"./Engine/data/fire/fire01.dds")
			, const_cast<WCHAR*>(L"./Engine/data/fire/noise01.dds")
			, const_cast<WCHAR*>(L"./Engine/data/fire/alpha01.dds"));
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[EFFECT_FIRE2]->Initialize(m_D3D->GetDevice()
			, const_cast<char*>("./Engine/data/fire/square.txt")
			, const_cast<WCHAR*>(L"./Engine/data/fire/fire01.dds")
			, const_cast<WCHAR*>(L"./Engine/data/fire/noise01.dds")
			, const_cast<WCHAR*>(L"./Engine/data/fire/alpha01.dds"));
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT01]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT02]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT03]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT04]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;

		}
		result = m_Model[CARROT05]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT06]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}

		result = m_Model[CARROT07]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT08]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}

		result = m_Model[CARROT09]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT010]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}

	/*	result = m_Model[CARROT011]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[CARROT012]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/carrot.obj", (WCHAR*)L"./Engine/data/carrot.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}*/
		result = m_Model[BIRD]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/bird.obj", (WCHAR*)L"./Engine/data/bird.TIF");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[BIRD2]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/bird.obj", (WCHAR*)L"./Engine/data/bird.TIF");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[BIRD3]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/bird.obj", (WCHAR*)L"./Engine/data/bird.TIF");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[DOG]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/dog.obj", (WCHAR*)L"./Engine/data/dog.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[DOG2]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/dog.obj", (WCHAR*)L"./Engine/data/dog.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[BASKET]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/basket.obj", (WCHAR*)L"./Engine/data/basket.jpg");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
	
		result = m_Model[ROCK1]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/rock(1).obj", (WCHAR*)L"./Engine/data/pig.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[ROCK2]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/rock(2).obj", (WCHAR*)L"./Engine/data/pig.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[ROCK3]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/rock(3).obj", (WCHAR*)L"./Engine/data/pig.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}
		result = m_Model[ROCK4]->Initialize(m_D3D->GetDevice(), (char*)"./Engine/data/rock(3).obj", (WCHAR*)L"./Engine/data/pig.dds");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the model object0.", L"Error", MB_OK);
			return false;
		}


		// =======================================================================================
		
		float x = 25, z =  25;

		m_Model[EFFECT_FIRE]->SetPosition(D3DXVECTOR3(100.0f, 5.0f, 80.0f));
		m_Model[EFFECT_FIRE2]->SetPosition(D3DXVECTOR3(100.0f, 5.0f, 80.0f));
		for (int i = CARROT01; i <= CARROT010; i++)
		{
			m_Model[i]->SetPosition(D3DXVECTOR3(x, -4.0f, z));
			m_Model[i]->SetCollsionSphere(D3DXVECTOR3(x, 0.0f, z), 5.0f);
			x += 12;
			z += 11;

		}
		m_Model[BIRD]->SetPosition(D3DXVECTOR3(50.0f, 3.0f, 50.0f));
		m_Model[BIRD2]->SetPosition(D3DXVECTOR3(60.0f, 2.0f, 100.0f));
		m_Model[BIRD3]->SetPosition(D3DXVECTOR3(150.0f, 1.5f, 70.0f));
		m_Model[DOG]->SetPosition(D3DXVECTOR3(100.0f, 0.5f, 130.0f));
		m_Model[DOG2]->SetPosition(D3DXVECTOR3(50.0f, 0.5f, 70.0f));
		m_Model[BASKET]->SetPosition(D3DXVECTOR3(15.0f, 0.5f, 55.0f));

		m_Model[ROCK1]->SetPosition(D3DXVECTOR3(15.0f, 0.5f, 150.0f));
		m_Model[ROCK2]->SetPosition(D3DXVECTOR3(170.0f, 0.5f, 10.0f));
		m_Model[ROCK3]->SetPosition(D3DXVECTOR3(4.0f, 0.5f, 100.0f));
		m_Model[ROCK4]->SetPosition(D3DXVECTOR3(45.0f, 0.5f, 10.0f));
	}

	//정점들 계산
	int vertexCount = 0;

	for (int i = 0; i < modelCount; i++)
	{
		vertexCount += m_Model[i]->GetIndexCount();
	}

	// 파이어 쉐이더 객체를 생성한다.
	{
		m_FireShader = new FireShaderClass;
		if (!m_FireShader)
		{
			return false;
		}

		// 화재 쉐이더 객체를 초기화합니다.
		if (!m_FireShader->Initialize(m_D3D->GetDevice(), hwnd))
		{
			MessageBox(hwnd, L"Could not initialize the fire shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Create the camera object.
	{
		m_Camera = new CameraClass;
		if (!m_Camera)
		{
			return false;
		}

		// Set the initial position of the camera.
		m_Camera->SetPosition(player->GetPosition() + (D3DXVECTOR3(0.0f, 5.0f, -5.0f)));
		// Create the model object.
		m_Camera->Render();
		m_Camera->GetViewMatrix(baseViewMatrix);
	}

	//Create the SkyDome object.
	{
		m_SkyDome = new SkyDomeClass;
		if (!m_SkyDome)
		{
			return false;
		}

		result = m_SkyDome->Initialize(m_D3D->GetDevice());
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the skydome object.", L"Error", MB_OK);
			return false;
		}

		m_SkyDomeShader = new SkyDomeShaderClass;
		if (!m_SkyDomeShader)
		{
			return false;
		}

		result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the skydome shader object.", L"Error", MB_OK);
			return false;
		}
	}

	//Create the SkyPlan object.
	{
		m_SkyPlane = new SkyPlaneClass;
		if (!m_SkyPlane)
		{
			return false;
		}

		result = m_SkyPlane->Initialize(m_D3D->GetDevice(), (WCHAR*)L"./Engine/data/SkyPlane/cloud001.dds",
			(WCHAR*)L"./Engine/data/SkyPlane/perturb001.dds");

		if (!result)
		{
			MessageBox(hwnd, L"Counld not initialize the sky plane object.", L"Eorror", MB_OK);
			return false;
		}

		m_SkyPlaneShader = new SkyPlaneShaderClass;
		if (!m_SkyPlaneShader)
		{
			return false;
		}

		result = m_SkyPlaneShader->Initialize(m_D3D->GetDevice(), hwnd);

		if (!result)
		{
			MessageBox(hwnd, L"Counld not initialize the sky plane shader object.", L"Eorror", MB_OK);
			return false;
		}
	}

	// Create the Terrain object.
	{
		m_Terrain = new TerrainClass;
		if (!m_Terrain)
		{
			return false;
		}

		result = m_Terrain->Initialize(m_D3D->GetDevice()
			, "./Engine/data/terrain/heightmap01.bmp"
			, L"./Engine/data/terrain/grass.dds"
			, "./Engine/data/minimap/colorm01.bmp");
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
			return false;
		}

		m_TerrainShader = new TerrainShaderClass;
		if (!m_TerrainShader)
		{
			return false;
		}

		result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
			return false;
		}
	}


	// Create the ColorShader object.
	{
		m_ColorShader = new ColorShaderClass;
		if (!m_ColorShader)
		{
			return false;
		}

		result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
			return false;
		}
	}

	// Create the light shader object.
	{
		m_LightShader = new LightShaderClass;
		if (!m_LightShader)
		{
			return false;
		}
		// Initialize the light shader object.
		result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
			return false;
		}

		// Create the light object.
		m_Light = new LightClass;
		if (!m_Light)
		{
			return false;
		}

		// Initialize the light object.
		m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetDiffuseColor(0.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetDirection(0.0f, 0.0f, 1.0f);
		m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light->SetSpecularPower(30.0f);



		// Create the texture shader object.
		{
			m_TextureShader = new TextureShaderClass;
			if (!m_TextureShader)
			{
				return false;
			}
			// Initialize the texture shader object.
			result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
			if (!result)
			{
				MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
				return false;
			}
		}

		// Create the bitmap object.
		//m_Bitmap = new BitmapClass;
		//if (!m_Bitmap)
		//{
		//	return false;
		//}
		//// Initialize the bitmap object.
		//result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight,
		//	(WCHAR*)L"./Engine/data/garden.jpg", screenWidth, screenHeight);
		//if (!result)
		//{
		//	MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		//	return false;
		//}
		//// Initialize a base view matrix with the camera for 2D user interface rendering.


		// Create the text object.
		{
			m_Text = new TextClass;
			if (!m_Text)
			{
				return false;
			}

			// Initialize the text object.
			result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth,
				screenHeight, baseViewMatrix, vertexCount, modelCount + 1, carrotCount);
			if (!result)
			{
				MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
				return false;
			}
		}

		{
			// 미니맵에서 이 정보가 필요하기 때문에 지형의 크기를 가져옵니다.
			int terrainWidth = 0;
			int terrainHeight = 0;
			m_Terrain->GetTerrainSize(terrainWidth, terrainHeight);

			// 미니맵 객체를 생성합니다.
			m_MiniMap = new MiniMapClass;
			if (!m_MiniMap)
			{
				return false;
			}

			// 미니맵 객체를 초기화 합니다.
			result = m_MiniMap->Initialize(m_D3D->GetDevice(), hwnd, screenWidth, screenHeight, baseViewMatrix, (float)(terrainWidth - 1),
				(float)(terrainHeight - 1));
			if (!result)
			{
				MessageBox(hwnd, L"Could not initialize the mini map object.", L"Error", MB_OK);
				return false;
			}
		}

		{
			//단풍 객체를 생성합니다.
			m_Foliage = new FoliageClass;
			if (!m_Foliage)
			{
				return false;
			}
			//단풍 객체를 초기화합니다.
			result = m_Foliage->Initialize(m_D3D->GetDevice(), L"./Engine/data/grass.dds", grassCount);
			if (!result)
			{
				MessageBox(hwnd, L"Could not initialize the foliage object", L"Error", MB_OK);
				return false;
			}

			m_Foliage1 = new FoliageClass;
			if (!m_Foliage)
			{
				return false;
			}
			//단풍 객체를 초기화합니다.
			result = m_Foliage1->Initialize(m_D3D->GetDevice(), L"./Engine/data/Tree.png", 50);
			if (!result)
			{
				MessageBox(hwnd, L"Could not initialize the foliage object", L"Error", MB_OK);
				return false;
			}

			// 단풍 쉐이더 개체를 만듭니다.
			m_FoliageShader = new FoliageShaderClass;
			if (!m_FoliageShader)
			{
				return false;
			}

			// 단풍 쉐이더 개체를 초기화합니다.
			result = m_FoliageShader->Initialize(m_D3D->GetDevice(), hwnd);
			if (!result)
			{
				MessageBox(hwnd, L"Could not initialize the foliage shader object.", L"Error", MB_OK);
				return false;
			}
		}

		// 파티클 셰이더 개체를 만듭니다.
		{
			m_ParticleShader = new ParticleShaderClass;
			if (!m_ParticleShader)
			{
				return false;
			}

			// 파티클 셰이더 개체를 초기화합니다.
			if (!m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd))
			{
				MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
				return false;
			}

			// 파티클 시스템 객체를 만듭니다.
			m_ParticleSystem = new ParticleSystemClass;
			if (!m_ParticleSystem)
			{
				return false;
			}

			// 파티클 시스템 객체를 초기화합니다.
			if (!m_ParticleSystem->Initialize(m_D3D->GetDevice()
				, const_cast<WCHAR*>(L"./Engine/data/particle/star.dds")))
			{
				return false;
			}
		}
		return true;
	}
}


void GraphicsClass::Shutdown()
{

	// 파티클 해제합니다.
	{
		// 파티클 시스템 객체를 해제합니다.
		if (m_ParticleSystem)
		{
			m_ParticleSystem->Shutdown();
			delete m_ParticleSystem;
			m_ParticleSystem = 0;
		}

		// particle shader 객체를 해제한다.
		if (m_ParticleShader)
		{
			m_ParticleShader->Shutdown();
			delete m_ParticleShader;
			m_ParticleShader = 0;
		}
	}
	//단풍 객체를 해제합니다.
	if (m_Foliage)
	{
		m_Foliage->Shutdown();
		delete m_Foliage;
		m_Foliage = 0;
	}
	if (m_Foliage1)
	{
		m_Foliage1->Shutdown();
		delete m_Foliage1;
		m_Foliage1 = 0;
	}
	// 단풍 쉐이더 객체를 해제합니다.
	if (m_FoliageShader)
	{
		m_FoliageShader->Shutdown();
		delete m_FoliageShader;
		m_FoliageShader = 0;
	}
	// 미니맵 객체를 해제합니다.
	if (m_MiniMap)
	{
		m_MiniMap->Shutdown();
		delete m_MiniMap;
		m_MiniMap = 0;
	}
	//// Release the bitmap object.
	//if (m_Bitmap)
	//{
	//	m_Bitmap->Shutdown();
	//	delete m_Bitmap;
	//	m_Bitmap = 0;
	//}
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}
	
	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the ColorShader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	
	// fire shader 객체를 해제한다.
	if (m_FireShader)
	{
		m_FireShader->Shutdown();
		delete m_FireShader;
		m_FireShader = 0;
	}


	if (m_Model)
	{
		for (int i = 0; i < modelCount; i++)
		{
			m_Model[i]->Shutdown();
			delete m_Model[i];
		}
		*m_Model = 0;
	}

	if (player)
	{
		delete player;
		player = 0;
	}
	
	 //Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}


	// Release the Terrain object.
	{
		if (m_TerrainShader)
		{
			m_TerrainShader->Shutdown();
			delete m_TerrainShader;
			m_TerrainShader = 0;
		}
		if (m_Terrain)
		{
			m_Terrain->Shutdown();
			delete m_Terrain;
			m_Terrain = 0;
		}
	}

	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the SkyDome object.
	{
		if (m_SkyDomeShader)
		{
			m_SkyDomeShader->Shutdown();
			delete m_SkyDomeShader;
			m_SkyDomeShader = 0;
		}
		if (m_SkyDome)
		{
			m_SkyDome->Shutdown();
			delete m_SkyDome;
			m_SkyDome = 0;
		}
	}

	//Release the SkyPlane object
	{
		if (m_SkyPlane)
		{
			m_SkyPlane->Shutdown();
			delete m_SkyPlane;
			m_SkyPlane = 0;
		}
		if (m_SkyPlaneShader)
		{
			m_SkyPlaneShader->Shutdown();
			delete m_SkyPlaneShader;
			m_SkyPlaneShader = 0;
		}
	}
	
	return;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime, int screenWidth, int screenHeight, int lx, int ly)
{
	bool result;
	static float rotation = 0.0f;
	static float dogMoveX; 
	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;

	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// 파티클 시스템에 대한 프레임 처리를 실행합니다.
	m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	dogMoveX = sinf(rotation * 100.0f * 0.0174532925f) * 10.0f;


	// Render the graphics scene.
	result = Render(rotation, dogMoveX);
	if (!result)
	{
		return false;
	}
	
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Show screen size.
	result = m_Text->ShowScreenSize(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	// Show polygon count.
	result = m_Text->ShowPolygonCount( m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->ShowModelCount(m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->ShowGotCarrot(carrotCount, m_D3D->GetDeviceContext() );
	if (!result)
	{
		return false;
	}

	mouseMove(frameTime, lx, ly);

	// 카메라의 현재 위치를 가져옵니다.
	D3DXVECTOR3 position = m_Camera->GetPosition();
	D3DXVECTOR3 modelPosition = { 10.0f, -5.0f, 30.0f };

	//단풍에 대한 프레임 처리를 수행한다.
	result = m_Foliage->Frame(position, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Foliage1->Frame(position, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// 미니 맵에서 카메라의 위치를 ​​업데이트 합니다.
	m_MiniMap->PositionUpdate(position.x, position.z);

	
	return true;
}



bool GraphicsClass::Render(float rotation, float dogMoveX)
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix, orthoMatrix;
	D3DXMATRIX  Rx, Ry, Ry2, Rz, S, T, FRy;

	bool result = false;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// FIRE SET

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	static float frameTime = 0.0f;

	m_D3D->TurnOffCulling();
	// 프레임 시간 카운터를 증가시킵니다.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// 세 가지 다른 노이즈 텍스처에 대해 세 가지 스크롤 속도를 설정합니다.
	D3DXVECTOR3 scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	// 세 개의 서로 다른 노이즈 옥타브 텍스처를 만드는 데 사용할 세 개의 스케일을 설정합니다.
	D3DXVECTOR3 scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// 세 가지 다른 노이즈 텍스처에 대해 세 가지 다른 x 및 y 왜곡 인수를 설정합니다.
	D3DXVECTOR2 distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	D3DXVECTOR2 distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	D3DXVECTOR2 distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// 텍스처 좌표 샘플링 섭동의 스케일과 바이어스.
	float distortionScale = 0.8f;
	float distortionBias = 0.5f;

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);


	D3DXVECTOR3 cameraposition = m_Camera->GetPosition();

	//스카이돔을 카메라 위치를 중심으로 변환합니다.
	D3DXMatrixTranslation(&worldMatrix, cameraposition.x, cameraposition.y, cameraposition.z);

	//표면 컬링을 끕니다.
	m_D3D->TurnOffCulling();

	//z버퍼를 끕니다.
	m_D3D->TurnZBufferOff();

	//스카이돔 버퍼를 렌더링 합니다.
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	
	//표면 컬링을 킵니다.
	m_D3D->TurnOnCulling();
	
	m_D3D->EnableSecondBlendState();

	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
	m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(),
	m_SkyPlane->GetScale(), m_SkyPlane->GetBrightness());
	
	m_D3D->TurnOffAlphaBlending();
	// 미니맵을 렌더링 합니다.
	if (!m_MiniMap->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix, m_TextureShader))
	{
		return false;
	}

	m_D3D->TurnOnAlphaBlending();
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}
	
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();

	//Z buffer - 2D rendering
	{
		// 지형 버퍼를 렌더링 합니다.
		m_Terrain->Render(m_D3D->GetDeviceContext());
		if (!m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture()))
		{
			return false;
		}

		//색상 쉐이더를 사용하여 모델을 렌더링 합니다.
		if (!m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix))
		{
			return false;
		}

		

		m_D3D->GetWorldMatrix(worldMatrix);
	}

	//bird
	{
		for (int i = BIRD; i <= BIRD3; i++)
		{
			m_Model[i]->Render(m_D3D->GetDeviceContext());

			D3DXMatrixScaling(&S, 30.0f, 30.0f, 30.0f);
			D3DXMatrixRotationY(&Rx, 75.0f);
			D3DXMatrixRotationY(&Ry, rotation);

			D3DXMatrixTranslation(&T, m_Model[i]->GetPosition().x, m_Model[i]->GetPosition().y, m_Model[i]->GetPosition().z);

			worldMatrix = S * Rx * T * Ry;

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Model[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
			if (!result)
			{
				return false;
			}
		}

	}
	//dog
	{
		for (int i = DOG; i <= DOG2; i++)
		{
			m_Model[i]->Render(m_D3D->GetDeviceContext());
			
			D3DXMatrixScaling(&S, 0.1f, 0.1f, 0.1f);
			if (dogMoveX < 0.0f) 
				D3DXMatrixRotationY(&Ry, -89.5);
		
			else 
				D3DXMatrixRotationY(&Ry, 89.5);

			D3DXMatrixTranslation(&T, m_Model[i]->GetPosition().x+ dogMoveX, m_Model[i]->GetPosition().y, m_Model[i]->GetPosition().z);
			worldMatrix = S * Ry *  T;
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Model[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			if (!result)
			{
				return false;
			}

		}
		

	}
	//CARROT
	{
		srand(time(NULL));

		float randomX = rand() % 255 +1;
		float randomZ = rand() % 255 +1;
	
		D3DXVECTOR3 carrotMove = { randomX, -5.0f, randomZ};

		for (int i = CARROT01; i <= CARROT010; i++)
		{
			m_Model[i]->Render(m_D3D->GetDeviceContext());

			D3DXMatrixScaling(&S, 0.08f, 0.08f, 0.08f);
			D3DXMatrixRotationX(&Rx, 89.5);

			result = IsEatenCarrot(i);

			if (result)
			{
				D3DXVECTOR3 temp = { 0.0f,0.0f,0.0f };

				D3DXMatrixTranslation(&T, carrotMove.x, carrotMove.y, carrotMove.z);
				m_Model[i]->SetPosition(carrotMove);
				temp.x = carrotMove.x;
				temp.z = carrotMove.z;
				m_Model[i]->SetCollsionSphereCenter(temp);
			
				carrotCount++;
			}
			else
			{
				D3DXMatrixTranslation(&T, m_Model[i]->GetPosition().x, m_Model[i]->GetPosition().y, m_Model[i]->GetPosition().z);
			}
			
			worldMatrix = S * Rx *  T;

			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Model[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
		}
	}
	//BASKET
	{
		m_Model[BASKET]->Render(m_D3D->GetDeviceContext());
		D3DXMatrixScaling(&S, 0.5f, 0.5f, 0.5f);
		D3DXMatrixRotationX(&Rx, 89.5);
		D3DXMatrixTranslation(&T, m_Model[BASKET]->GetPosition().x, m_Model[BASKET]->GetPosition().y, m_Model[BASKET]->GetPosition().z);
		
		worldMatrix = S * Rx * T;

		// Render the model using the texture shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[BASKET]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_Model[BASKET]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result)
		{
			return false;
		}
	}
		
	
	//ROCK
	{
		for(int i = ROCK1; i <= ROCK4; i++)
		{
			m_Model[i]->Render(m_D3D->GetDeviceContext());
			D3DXMatrixScaling(&S, 2.0f, 2.0f, 2.0f);
			D3DXMatrixRotationX(&Rx, 89.5);
			D3DXMatrixTranslation(&T, m_Model[i]->GetPosition().x, m_Model[i]->GetPosition().y, m_Model[i]->GetPosition().z);
			worldMatrix = S * Rx * T;
			
			// Render the model using the texture shader.
			result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Model[i]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				m_Model[i]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(),m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			if (!result)
			{
				return false;
			} 
		}

	}

	{
		m_D3D->EnableAlphaToCoverageBlending();
		m_D3D->GetWorldMatrix(worldMatrix);
		// Render the text strings.

		//풀
		m_Foliage->Render(m_D3D->GetDeviceContext());
		m_FoliageShader->Render(m_D3D->GetDeviceContext(), m_Foliage->GetVertexCount(), m_Foliage->GetInstanceCount(),
			viewMatrix, projectionMatrix, m_Foliage->GetTexture());

		//나무
		m_Foliage1->Render(m_D3D->GetDeviceContext());
		m_FoliageShader->Render(m_D3D->GetDeviceContext(), m_Foliage1->GetVertexCount(), m_Foliage1->GetInstanceCount(),
			viewMatrix, projectionMatrix, m_Foliage1->GetTexture());

		m_D3D->TurnOffAlphaBlending();
	}
	//Z buffer - 2D rendering
	{

		m_D3D->TurnOffCulling();
		m_D3D->EnableAlphaToCoverageBlending();
		D3DXMatrixScaling(&S, 5.0f, 5.0f, 5.0f);
		//fire
		{

			m_Model[EFFECT_FIRE]->Render(m_D3D->GetDeviceContext());
			D3DXMatrixTranslation(&T, m_Model[EFFECT_FIRE]->GetPosition().x
				, m_Model[EFFECT_FIRE]->GetPosition().y
				, m_Model[EFFECT_FIRE]->GetPosition().z);

			worldMatrix = S*T;


			if (!m_FireShader->Render(m_D3D->GetDeviceContext(), m_Model[EFFECT_FIRE]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Model[EFFECT_FIRE]->GetTexture1(), m_Model[EFFECT_FIRE]->GetTexture2(), m_Model[EFFECT_FIRE]->GetTexture3(), frameTime, scrollSpeeds,
				scales, distortion1, distortion2, distortion3, distortionScale, distortionBias))
			{
				return false;
			}


			m_Model[EFFECT_FIRE2]->Render(m_D3D->GetDeviceContext());
			D3DXMatrixRotationY(&Ry, 85.9);

			worldMatrix = S* Ry * T;

			if (!m_FireShader->Render(m_D3D->GetDeviceContext(), m_Model[EFFECT_FIRE2]->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_Model[EFFECT_FIRE2]->GetTexture1(), m_Model[EFFECT_FIRE2]->GetTexture2(), m_Model[EFFECT_FIRE2]->GetTexture3(), frameTime, scrollSpeeds,
				scales, distortion1, distortion2, distortion3, distortionScale, distortionBias))
			{
				return false;
			}
		}
		 //Turn off alpha blending after rendering the text.
		m_D3D->TurnOffAlphaBlending();

		D3DXVECTOR3 carrotPos = { 0.0f,0.0f, 0.0f };
		D3DXMatrixScaling(&S, 2.0f, 2.0f, 2.0f);

		m_D3D->TurnOnAlphaBlending();
		for (int i = CARROT01; i <= CARROT010; i++)
		{

			carrotPos = m_Model[i]->GetPosition();
			// 파티클 시스템 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
			m_ParticleSystem->Render(m_D3D->GetDeviceContext());

			// 텍스처 셰이더를 사용하여 모델을 렌더링합니다.
			D3DXMatrixScaling(&S, 5.0f, 5.0f, 5.0f);
			D3DXMatrixTranslation(&T, carrotPos.x, carrotPos.y + 20.0f, carrotPos.z);
			worldMatrix = S * T;
			if (!m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_ParticleSystem->GetTexture()))
			{
				return false;
			}

		}
		m_D3D->TurnOffAlphaBlending();

		m_D3D->TurnOnCulling();
	}
	//Player
	{
		player->Render(m_D3D->GetDeviceContext());

		D3DXMatrixRotationX(&Rx, 89.5);
		D3DXMatrixRotationY(&Ry, -89.55);
		D3DXMatrixScaling(&S, 0.3f, 0.3f, 0.3f);
		D3DXMatrixTranslation(&T, player->GetPosition().x, player->GetPosition().y, player->GetPosition().z);

		//Player rotate
		{
			float yaw, pitch, roll;
			pitch = this->rotation.x * 0.0174532925f;
			yaw = this->rotation.y * 0.0174532925f;
			roll = this->rotation.z * 0.0174532925f;
			D3DXMatrixRotationYawPitchRoll(&Ry2, yaw, pitch, roll);
		}

		worldMatrix = S * Rx*Ry*Ry2 *T;
	}

	// Render the model using the texture shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), player->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		player->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}



	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

void GraphicsClass::moveForward( float frameTime)
{
	D3DXMATRIX dir;
	D3DXMatrixIdentity(&dir);
	D3DXVECTOR3 direction(0, 0, 1);
	position = m_Camera->GetPosition();
	rotation = m_Camera->GetRotation();
	p_position = player->GetPosition();
	
	D3DXMatrixRotationYawPitchRoll(&dir, rotation.y * 0.0174532925f, rotation.x* 0.0174532925f, rotation.z* 0.0174532925f);

	D3DXVec3TransformCoord(&direction, &direction, &dir);

	position += direction * frameTime * 0.05;
	p_position += direction * frameTime * 0.05;
	if (p_position.x > 255)
	{
		p_position.x = 255;
	}
	if (p_position.x < 0)
	{
		p_position.x = 0;
	}
	if (p_position.z > 255)
	{
		p_position.z = 255;
	}
	if (p_position.z < 0)
	{
		p_position.z = 0;
	}
	player->SetPosition(p_position);
	player->SetCollsionSphere(p_position, 2.0f);
	m_Camera->SetPosition(position);
}

void GraphicsClass::moveBackward( float frameTime)
{
	D3DXMATRIX dir;
	D3DXMatrixIdentity(&dir);
	D3DXVECTOR3 direction(0, 0, -1);
	position = m_Camera->GetPosition();
	rotation = m_Camera->GetRotation();
	p_position = player->GetPosition();

	D3DXMatrixRotationYawPitchRoll(&dir, rotation.y * 0.0174532925f, rotation.x* 0.0174532925f, rotation.z* 0.0174532925f);

	D3DXVec3TransformCoord(&direction, &direction, &dir);

	position += direction * frameTime * 0.05;
	p_position += direction * frameTime * 0.05;
	if (p_position.x > 255)
	{
		p_position.x = 255;
	}
	if (p_position.x < 0)
	{
		p_position.x = 0;
	}
	if (p_position.z > 255)
	{
		p_position.z = 255;
	}
	if (p_position.z < 0)
	{
		p_position.z = 0;
	}
	player->SetPosition(p_position);
	player->SetCollsionSphere(p_position, 2.0f);
	m_Camera->SetPosition(position);
}

void GraphicsClass::moveRightward( float frameTime)
{
	D3DXMATRIX dir;
	D3DXMatrixIdentity(&dir);
	D3DXVECTOR3 direction(1, 0, 0);
	position = m_Camera->GetPosition();
	rotation = m_Camera->GetRotation();
	p_position = player->GetPosition();


	D3DXMatrixRotationYawPitchRoll(&dir, rotation.y * 0.0174532925f, rotation.x* 0.0174532925f, rotation.z* 0.0174532925f);

	D3DXVec3TransformCoord(&direction, &direction, &dir);

	position += direction  * frameTime * 0.05;
	p_position += direction * frameTime * 0.05;
	
	if (p_position.x > 255)
	{
		p_position.x = 255;
	}
	if (p_position.x < 0)
	{
		p_position.x = 0;
	}
	if (p_position.z > 255)
	{
		p_position.z = 255;
	}
	if (p_position.z < 0)
	{
		p_position.z = 0;
	}
	
	player->SetPosition(p_position);
	player->SetCollsionSphere(p_position, 2.0f);
	m_Camera->SetPosition(position);
}

void GraphicsClass::moveLeftward( float frameTime)
{
	D3DXMATRIX dir;
	D3DXMatrixIdentity(&dir);
	D3DXVECTOR3 direction(-1, 0, 0);
	position = m_Camera->GetPosition();
	rotation = m_Camera->GetRotation();
	p_position = player->GetPosition();

	D3DXMatrixRotationYawPitchRoll(&dir, rotation.y * 0.0174532925f, rotation.x* 0.0174532925f, rotation.z* 0.0174532925f);

	D3DXVec3TransformCoord(&direction, &direction, &dir);

	position += direction * frameTime * 0.05;
	p_position += direction * frameTime * 0.05;
	if (p_position.x > 255)
	{
		p_position.x = 255;
	}
	if (p_position.x < 0)
	{
		p_position.x = 0;
	}
	if (p_position.z > 255)
	{
		p_position.z = 255;
	}
	if (p_position.z < 0)
	{
		p_position.z = 0;
	}

	player->SetPosition(p_position);
	player->SetCollsionSphere(p_position, 2.0f);
	m_Camera->SetPosition(position);
}

void GraphicsClass::mouseMove(float frameTime, int lx, int ly)
{
	p_position = player->GetPosition();

	// rotation
	{
		rotation.y += lx * frameTime * 0.01;
		//rotation.x += ly * frameTime * 0.01;

		m_Camera->SetRotation(rotation);
		m_Camera->Seteyes(p_position);
	}
	// transform
	{
		m_Camera->SetPosition(
			sinf(rotation.y  * 0.0174532925f) * -10.0f + p_position.x,     // player의 x좌표에서 2.0f만큼 떨어진 길이
			p_position.y + 2.0f,                                           // 카메라의 높이
			cosf(rotation.y  * 0.0174532925f) * -10.0f + p_position.z);    //player의 z좌표에서 2.0f만큼 떨어진 길이
	}
	
}

bool GraphicsClass::IsEatenCarrot(int carrotIndex)
{
	D3DXVECTOR3 center = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 playerCenter = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 diff = { 0.0f, 0.0f, 0.0f };
	float radius=0.0f, playerRadius = 0.0f, distance = 0.0f;
	
	
	m_Model[carrotIndex]->GetCollsionSphere(center, radius);
	player->GetCollsionSphere(playerCenter, playerRadius);

	diff = playerCenter - center;
	distance = D3DXVec3Length(&diff);

	if (distance <= (radius + playerRadius))
	{
		return true;
	}

	return false;
}




