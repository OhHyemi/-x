
#include "TextureClass.h"
#include "foliageclass.h"
#include <time.h>


FoliageClass::FoliageClass()
{
}


FoliageClass::FoliageClass(const FoliageClass& other)
{
}


FoliageClass::~FoliageClass()
{
}


bool FoliageClass::Initialize(ID3D11Device* device, const WCHAR* textureFilename, int fCount)
{
	// 단풍 수를 설정합니다.
	m_foliageCount = fCount;

	// 단풍의 위치를 ​​생성합니다.
	if(!GeneratePositions())
	{
		return false;
	}

	// 단풍 모델의 지오메트리를 포함하는 정점과 인스턴스 버퍼를 초기화합니다.
	if(!InitializeBuffers(device))
	{
		return false;
	}

	//이 모델의 텍스처를 로드합니다.
	if(!LoadTexture(device, textureFilename))
	{
		return false;
	}

	// 초기 바람 회전과 방향을 설정합니다.
	m_windRotation = 0.0f;
	m_windDirection = 1;

	return true;
}


void FoliageClass::Shutdown()
{
	// 모델 텍스처를 릴리즈한다.
	ReleaseTexture();

	// 버텍스와 인스턴스 버퍼를 해제한다.
	ShutdownBuffers();

	// 잎 배열을 놓습니다.
	if(m_foliageArray)
	{
		delete [] m_foliageArray;
		m_foliageArray = 0;
	}
}


void FoliageClass::Render(ID3D11DeviceContext* deviceContext)
{
	// 버텍스와 인스턴스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
	RenderBuffers(deviceContext);
}


bool FoliageClass::Frame(D3DXVECTOR3 cameraPosition, ID3D11DeviceContext* deviceContext)
{
	D3DXMATRIX rotateMatrix, translationMatrix, rotateMatrix2, finalMatrix;
	D3DXVECTOR3 modelPosition = { 0.0f, 0.0f, 0.0f };
	double angle = 0.0f;
	float rotation = 0.0f;
	float windRotation = 0.0f;

	// 바람 회전을 업데이트합니다.
	if(m_windDirection == 1)
	{
		m_windRotation += 0.1f;
		if(m_windRotation > 10.0f)
		{
			m_windDirection = 2;
		}
	}
	else
	{
		m_windRotation -= 0.1f;
		if(m_windRotation < -10.0f)
		{
			m_windDirection = 1;
		}
	}

	// 업데이트 된 위치로 인스턴스 버퍼를 로드합니다.
	for(int i=0; i<m_foliageCount; i++)
	{
		// 이 조각의 위치를 ​​얻는다.
		modelPosition.x = m_foliageArray[i].x;
		modelPosition.y = 0.3f;
		modelPosition.z = m_foliageArray[i].z;

		// 아크 탄젠트 함수를 사용하여 현재 카메라 위치를 향하도록 빌보드 모델에 적용해야하는 회전을 계산합니다.
		double angle = atan2(modelPosition.x - cameraPosition.x, modelPosition.z - cameraPosition.z) * (180.0 / D3DX_PI);

		// 회전을 라디안으로 변환합니다.
		rotation = (float)angle * 0.0174532925f;

		// 빌보드의 X 회전을 설정합니다.
		D3DXMatrixRotationY(&rotateMatrix, rotation);
	
		// 단풍의 바람 회전을 얻는다.
		windRotation = m_windRotation * 0.0174532925f;

		// 바람 회전을 설정합니다.
		D3DXMatrixRotationX(&rotateMatrix2, windRotation);

		// 변환 행렬을 설정합니다.
		D3DXMatrixTranslation(&translationMatrix, modelPosition.x, modelPosition.y, modelPosition.z);

		// 최종 행렬을 만들고 인스턴스 배열에 저장합니다.
		
		D3DXMatrixMultiply(&finalMatrix, &rotateMatrix, &rotateMatrix2);
		D3DXMatrixMultiply(&m_Instances[i].matrix, &finalMatrix, &translationMatrix);
	}

	// 쓸 수 있도록 인스턴스 버퍼를 잠급니다.
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	if(FAILED(deviceContext->Map(m_instanceBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return false;
	}

	// 인스턴스 버퍼의 데이터에 대한 포인터를 가져옵니다.
	InstanceType* instancesPtr = (InstanceType*)mappedResource.pData;

	// 인스턴스 배열을 인스턴스 버퍼에 복사합니다.
	memcpy(instancesPtr, (void*)m_Instances, (sizeof(InstanceType) * m_foliageCount));

	// 인스턴스 버퍼를 잠금 해제합니다.
	deviceContext->Unmap(m_instanceBuffer, 0);

	return true;
}


int FoliageClass::GetVertexCount()
{
	return m_vertexCount;
}


int FoliageClass::GetInstanceCount()
{
	return m_instanceCount;
}


ID3D11ShaderResourceView* FoliageClass::GetTexture()
{
	return m_Texture->GetTexture();
}


bool FoliageClass::InitializeBuffers(ID3D11Device* device)
{
	// 정점 배열의 정점 수를 설정합니다.
	m_vertexCount = 6;

	// 정점 배열을 만듭니다.
	VertexType* vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// 정점 배열에 데이터를 로드합니다.
	vertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // 왼쪽 아래.
	vertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // 왼쪽 위.
	vertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[2].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  // 오른쪽 아래.
	vertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  // 오른쪽 아래.
	vertices[3].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[4].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // 왼쪽 위.
	vertices[4].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // 오른쪽 위.
	vertices[5].texture = D3DXVECTOR2(1.0f, 0.0f);

	// 정점 버퍼의 구조체를 설정한다.
	D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource 구조에 정점 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// 이제 마침내 정점 버퍼를 만듭니다.
	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// 이제 버텍스 버퍼가 생성되고 로드된 배열을 해제하십시오.
	delete [] vertices;
	vertices = 0;

	// 배열의 인스턴스 수를 설정합니다.
	m_instanceCount = m_foliageCount;

	// 인스턴스 배열을 만듭니다.
	m_Instances = new InstanceType[m_instanceCount];
	if(!m_Instances)
	{
		return false;
	}

	// 초기 매트릭스를 설정합니다.
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);

	// 데이터로 인스턴스 배열을로드합니다.
	for(int i=0; i<m_instanceCount; i++)
	{
		m_Instances[i].matrix = matrix;
		m_Instances[i].color = D3DXVECTOR3(m_foliageArray[i].r, m_foliageArray[i].g, m_foliageArray[i].b);
	}

	// 인스턴스 버퍼의 구조체를 설정합니다.
	D3D11_BUFFER_DESC instanceBufferDesc;
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// 하위 리소스 구조에 인스턴스 데이터에 대한 포인터를 제공합니다.
	D3D11_SUBRESOURCE_DATA instanceData;
	instanceData.pSysMem = m_Instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// 인스턴스 버퍼를 만듭니다.
	if(FAILED(device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer)))
	{
		return false;
	}

	return true;
}


void FoliageClass::ShutdownBuffers()
{
	// 인스턴스 버퍼를 해제합니다.
	if(m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// 버텍스 버퍼를 해제합니다.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	// 인스턴스 배열을 해제합니다.
	if(m_Instances)
	{
		delete [] m_Instances;
		m_Instances = 0;
	}
}


void FoliageClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// 버퍼 스트라이드를 설정합니다.
	unsigned int strides[2] = { sizeof(VertexType), sizeof(InstanceType) };

	// 버퍼 오프셋을 설정합니다.
	unsigned int offsets[2] = { 0, 0 };

	// 포인터의 배열을 정점 버퍼와 인스턴스 버퍼로 설정합니다.
	ID3D11Buffer* bufferPointers[2] = { m_vertexBuffer, m_instanceBuffer };

	// 렌더링 할 수 있도록 입력 어셈블러에서 꼭지점 버퍼와 인스턴스 버퍼를 활성화로 설정합니다.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// 이 꼭지점 버퍼에서 렌더링되어야하는 프리미티브 유형을 설정합니다.이 경우에는 삼각형입니다.
    deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


bool FoliageClass::LoadTexture(ID3D11Device* device, const WCHAR* filename)
{
	// 텍스처 오브젝트를 생성한다.
	m_Texture = new TextureClass;
	if(!m_Texture)
	{
		return false;
	}

	// 텍스처 오브젝트를 초기화한다.
	if(!m_Texture->Initialize(device, (WCHAR*)filename))
	{
		return false;
	}

	return true;
}


void FoliageClass::ReleaseTexture()
{
	// 텍스처 오브젝트를 릴리즈한다.
	if(m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}
}


bool FoliageClass::GeneratePositions()
{
	// 모든 단풍 정보를 저장할 배열을 만듭니다.
	m_foliageArray = new FoliageType[m_foliageCount];
	if(!m_foliageArray)
	{
		return false;
	}

	// 난수 생성기에 시드합니다.
	srand((int)time(NULL));

	// 각 조각에 임의의 위치와 임의의 색상을 설정합니다.
	for(int i=0; i<m_foliageCount; i++)
	{
		m_foliageArray[i].x = ((float)rand() / (float)(RAND_MAX)) * 248.0 + 3.0f;

		m_foliageArray[i].z = ((float)rand() / (float)(RAND_MAX)) * 248.0 + 3.0f;


		float red = ((float)rand() / (float)(RAND_MAX)) * 1.0f;
		float green = ((float)rand() / (float)(RAND_MAX)) * 1.0f;

		m_foliageArray[i].r = red + 1.0f;
		m_foliageArray[i].g = green + 0.5f;
		m_foliageArray[i].b = 0.0f;
	}

	return true;
}