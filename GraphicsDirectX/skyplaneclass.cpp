#include "TextureClass.h"
#include "skyplaneclass.h"



SkyPlaneClass::SkyPlaneClass()
{
}


SkyPlaneClass::SkyPlaneClass(const SkyPlaneClass& other)
{
}


SkyPlaneClass::~SkyPlaneClass()
{
}


bool SkyPlaneClass::Initialize(ID3D11Device* device, WCHAR* cloudTextureFilename, WCHAR* perturbTextureFilename)
{
	// �ϴ� ��� �Ű� ������ �����մϴ�.
	int skyPlaneResolution = 50;
	float skyPlaneWidth = 10.0f;
	float skyPlaneTop = 0.5f;
	float skyPlaneBottom = 0.0f;
	int textureRepeat = 2;

	// �ϴ� ��� ���̴� ���� �Ű� ������ �����մϴ�.
	m_scale = 0.3f;
	m_brightness = 0.5f;

	// ������ 0���� �ʱ�ȭ�մϴ�.
	m_translation = 0.0f;

	// �ϴ� ����� ����ϴ�.
	if(!InitializeSkyPlane(skyPlaneResolution, skyPlaneWidth, skyPlaneTop, skyPlaneBottom, textureRepeat))
	{
		return false;
	}

	// �ϴ� ��鿡 ���� ���� �� �ε��� ���۸� ����ϴ�.
	if(!InitializeBuffers(device, skyPlaneResolution))
	{
		return false;
	}

	// �ϴ� ��� �ؽ�ó�� �ε��մϴ�. 
	if(!LoadTextures(device, cloudTextureFilename, perturbTextureFilename))
	{
		return false;
	}

	return true;
}


void SkyPlaneClass::Shutdown()
{
	// �ϴ� ��� �ؽ�ó�� �����մϴ�.
	ReleaseTextures();

	// �ϴ� ��� �������� ��� �� ���� �� �ε��� ���۸� �����մϴ�.
	ShutdownBuffers();

	// �ϴ� ��� �迭�� �����մϴ�.
	ShutdownSkyPlane();
}


void SkyPlaneClass::Render(ID3D11DeviceContext* deviceContext)
{
	// �ϴ� ����� �������մϴ�.
	RenderBuffers(deviceContext);
}


void SkyPlaneClass::Frame()
{
	// �� �������� �ؽ�ó ��ȯ ���� ������ŵ�ϴ�.
	m_translation += 0.0001f;
	if(m_translation > 1.0f)
	{
		m_translation -= 1.0f;
	}
}


int SkyPlaneClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* SkyPlaneClass::GetCloudTexture()
{
	return m_CloudTexture->GetTexture();
}


ID3D11ShaderResourceView* SkyPlaneClass::GetPerturbTexture()
{
	return m_PerturbTexture->GetTexture();
}


float SkyPlaneClass::GetScale()
{
	return m_scale;
}


float SkyPlaneClass::GetBrightness()
{
	return m_brightness;
}


float SkyPlaneClass::GetTranslation()
{
	return m_translation;
}


bool SkyPlaneClass::InitializeSkyPlane(int skyPlaneResolution, float skyPlaneWidth, float skyPlaneTop, float skyPlaneBottom, int textureRepeat)
{
	float positionX = 0.0f;
	float positionY = 0.0f;
	float positionZ = 0.0f;
	float tu = 0.0f;
	float tv = 0.0f;

	// �ϴ� ��� ��ǥ�� ���� �� �迭�� ����ϴ�.
	m_skyPlane = new SkyPlaneType[(skyPlaneResolution + 1) * (skyPlaneResolution + 1)];
	if(!m_skyPlane)
	{
		return false;
	}

	// �ϴ� ��鿡�� �� ������ ũ�⸦ �����մϴ�.
	float quadSize = skyPlaneWidth / (float)skyPlaneResolution;

	// �ʺ� �������� �ϴ� ����� �������� ����մϴ�.
	float radius = skyPlaneWidth / 2.0f;

	// ���� �� ���� ����� ����մϴ�.
	float constant = (skyPlaneTop - skyPlaneBottom) / (radius * radius);

	// �ؽ�ó ��ǥ ���� ���� ����մϴ�.
	float textureDelta = (float)textureRepeat / (float)skyPlaneResolution;

	// �ϴ� ����� �ݺ��ϰ� ������ ���� ���� ������� ��ǥ�� ����ϴ�.
	for(int j=0; j<=skyPlaneResolution; j++)
	{
		for(int i=0; i<=skyPlaneResolution; i++)
		{
			// ���� ��ǥ�� ����մϴ�.
			positionX = (-0.5f * skyPlaneWidth) + ((float)i * quadSize);
			positionZ = (-0.5f * skyPlaneWidth) + ((float)j * quadSize);
			positionY = skyPlaneTop - (constant * ((positionX * positionX) + (positionZ * positionZ)));

			// �ؽ�ó ��ǥ�� ����մϴ�.
			tu = (float)i * textureDelta;
			tv = (float)j * textureDelta;

			// �� ��ǥ�� �߰��ϱ� ���� �ϴ� ��� �迭�� �ε����� ����մϴ�.
			int index = j * (skyPlaneResolution + 1) + i;

			// �ϴ� ��� �迭�� ��ǥ�� �߰��մϴ�.
			m_skyPlane[index].x = positionX;
			m_skyPlane[index].y = positionY;
			m_skyPlane[index].z = positionZ;
			m_skyPlane[index].tu = tu;
			m_skyPlane[index].tv = tv;
		}
	}

	return true;
}


void SkyPlaneClass::ShutdownSkyPlane()
{
	// �ϴ� ��� �迭�� �����մϴ�.
	if(m_skyPlane)
	{
		delete [] m_skyPlane;
		m_skyPlane = 0;
	}
}


bool SkyPlaneClass::InitializeBuffers(ID3D11Device* device, int skyPlaneResolution)
{
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int index4 = 0;

	// �ϴ� ��� �޽��� ���� ���� ����մϴ�.
	m_vertexCount = (skyPlaneResolution + 1) * (skyPlaneResolution + 1) * 6;

	// �ε��� ���� ������ ���� ���� �����մϴ�.
	m_indexCount = m_vertexCount;
		
	// ���� �迭�� ����ϴ�.
	VertexType* vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// �ε��� �迭�� ����ϴ�.
	unsigned long* indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// �ε����� ���� �迭�� �ʱ�ȭ �մϴ�.
	int index = 0;

	// �ϴ� ��� �迭 �����ͷ� �������� �ε��� �迭�� �ε��մϴ�.
	for(int j=0; j<skyPlaneResolution; j++)
	{
		for(int i=0; i<skyPlaneResolution; i++)
		{
			index1 = j * (skyPlaneResolution + 1) + i;
			index2 = j * (skyPlaneResolution + 1) + (i+1);
			index3 = (j+1) * (skyPlaneResolution + 1) + i;
			index4 = (j+1) * (skyPlaneResolution + 1) + (i+1);

			// �ﰢ�� 1 - ���� ��
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index1].x, m_skyPlane[index1].y, m_skyPlane[index1].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index1].tu, m_skyPlane[index1].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 1 - ������ ��
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index2].x, m_skyPlane[index2].y, m_skyPlane[index2].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index2].tu, m_skyPlane[index2].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 1 - ���� �Ʒ�
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index3].x, m_skyPlane[index3].y, m_skyPlane[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index3].tu, m_skyPlane[index3].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 2 - ���� �Ʒ�
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index3].x, m_skyPlane[index3].y, m_skyPlane[index3].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index3].tu, m_skyPlane[index3].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 2 - ������ ��
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index2].x, m_skyPlane[index2].y, m_skyPlane[index2].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index2].tu, m_skyPlane[index2].tv);
			indices[index] = index;
			index++;

			// �ﰢ�� 2 - ������ �Ʒ�
			vertices[index].position = D3DXVECTOR3(m_skyPlane[index4].x, m_skyPlane[index4].y, m_skyPlane[index4].z);
			vertices[index].texture = D3DXVECTOR2(m_skyPlane[index4].tu, m_skyPlane[index4].tv);
			indices[index] = index;
			index++;
		}
	}

	// ���� ������ ����ü�� �����Ѵ�.
	D3D11_BUFFER_DESC vertexBufferDesc;
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// subresource ������ ���� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA vertexData;
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// ���� ���۸� ����ϴ�.
	if(FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer)))
	{
		return false;
	}

	// �ε��� ������ ����ü�� �����մϴ�.
	D3D11_BUFFER_DESC indexBufferDesc;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// ���� ���ҽ� ������ �ε��� �����Ϳ� ���� �����͸� �����մϴ�.
	D3D11_SUBRESOURCE_DATA indexData;
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// �ε��� ���۸� ����ϴ�.
	if(FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer)))
	{
		return false;
	}

	// ���ؽ��� �ε��� ���۰� �����ǰ� �ε�� �迭�� �����մϴ�.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void SkyPlaneClass::ShutdownBuffers()
{
	// �ε��� ���۸� �����մϴ�.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// ���ؽ� ���۸� �����մϴ�.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}


void SkyPlaneClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	// ���� ���� ���� �� �������� �����մϴ�.
    unsigned int stride = sizeof(VertexType); 
	unsigned int offset = 0;
    
	// ������ �� �� �ֵ��� �Է� ��������� ���� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // ������ �� �� �ֵ��� �Է� ��������� �ε��� ���۸� Ȱ������ �����մϴ�.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // �� ������ ���ۿ��� �������Ǿ���ϴ� ������Ƽ�� ������ �����մϴ�.�� ��쿡�� �ﰢ���Դϴ�.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


bool SkyPlaneClass::LoadTextures(ID3D11Device* device,  WCHAR* textureFilename1,  WCHAR* textureFilename2)
{
	// Ŭ���� �ؽ�ó ��ü�� �����մϴ�.
	m_CloudTexture = new TextureClass;
	if(!m_CloudTexture)
	{
		return false;
	}

	// ���� �ؽ�ó ��ü�� �ʱ�ȭ�մϴ�.
	if(!m_CloudTexture->Initialize(device, textureFilename1))
	{
		return false;
	}

	// ���� �ؽ�ó ������Ʈ�� �����մϴ�.
	m_PerturbTexture = new TextureClass;
	if(!m_PerturbTexture)
	{
		return false;
	}

	// ���� �ؽ�ó ������Ʈ�� �ʱ�ȭ�մϴ�.
	if(!m_PerturbTexture->Initialize(device, textureFilename2))
	{
		return false;
	}

	return true;
}


void SkyPlaneClass::ReleaseTextures()
{
	// �ؽ�ó ������Ʈ�� �����մϴ�..
	if(m_PerturbTexture)
	{
		m_PerturbTexture->Shutdown();
		delete m_PerturbTexture;
		m_PerturbTexture = 0;
	}

	if(m_CloudTexture)
	{
		m_CloudTexture->Shutdown();
		delete m_CloudTexture;
		m_CloudTexture = 0;
	}
}