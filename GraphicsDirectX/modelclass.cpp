#include "modelclass.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_Texture = 0;
	m_model = 0;
	m_temp = "";
	model = (char*)"";
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
ModelClass::ModelClass(const ModelClass& other) {}
ModelClass::~ModelClass() {}

bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename)
{
	bool result;

	m_sphere = new CollisionBound;
	if (!m_sphere)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadModel(modelFilename);
	if (!result)
	{
		return false;
	}
	// Initialize the vertex and index buffer that hold the geometry for the triangle.
	result = InitializeBuffers(device);
	if (!result)
	{
		return false;
	}

	// Load the texture for this model.
	result = LoadTexture(device, textureFilename);
	if (!result)
	{
		return false;
	}
	return true;
}
bool ModelClass::Initialize(ID3D11Device* device, char* modelFilename
	, WCHAR* textureFilename1, WCHAR* textureFilename2, WCHAR* textureFilename3)
{
	// 모델 데이터를 로드합니다.
	if (!LoadModelForEffect(modelFilename))
	{
		return false;
	}

	// 정점 및 인덱스 버퍼를 초기화합니다.
	if (!InitializeBuffers(device))
	{
		return false;
	}

	return LoadTextures(device, textureFilename1, textureFilename2, textureFilename3);
}
void ModelClass::Shutdown()
{
	// 모델 텍스쳐를 반환합니다.
	if (m_Texture1)ReleaseTextures();
	// Release the vertex and index buffers.
	ShutdownBuffers();
	// Release the model data.
	ReleaseModel();

	if (m_sphere)
	{
		delete m_sphere;
		m_sphere = 0;
	}
	return;
}
void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);
	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;

	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	//m_vertexCount = 8;  // Set the number of vertices in the vertex array.
	//m_indexCount = 12;   // Set the number of indices in the index array.
	
	// Create the vertex and index array.
	{
		vertices = new VertexType[m_vertexCount];
		if (!vertices)
		{
			return false;
		}

		indices = new unsigned long[m_indexCount];
		if (!indices)
		{
			return false;
		}
	}

	// Load the vertex array and index array with data.
	for (int i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = D3DXVECTOR3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		indices[i] = i;
	}

	// Vertex buffer. Set up and Create
	{
		// Set up the description of the static vertex buffer.
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexBufferDesc.CPUAccessFlags = 0;
		vertexBufferDesc.MiscFlags = 0;
		vertexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the vertex data.
		vertexData.pSysMem = vertices;
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		// Now create the vertex buffer. 
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
		if (FAILED(result))
		{
			return false;
		}
	}

	// Index buffer. Set up and Create
	{
		// Set up the description of the static index buffer.
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;

		// Give the subresource structure a pointer to the index data.
		indexData.pSysMem = indices;
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		// Create the index buffer.
		result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
		if (FAILED(result))
		{
			return false;
		}
	}
	
	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;
	delete[] indices;
	indices = 0;
	return true;
}
void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	return;
}
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	
	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return;
}

bool ModelClass::LoadTexture(ID3D11Device* device, WCHAR * filename)
{
	bool result;
	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, (WCHAR*)filename);
	if (!result)
	{
		return false;
	}
	return true;
}
bool ModelClass::LoadTextures(ID3D11Device* device, WCHAR* textureFilename1, WCHAR* textureFilename2, WCHAR* textureFilename3)
{
	// 첫번째 텍스처 오브젝트를 생성한다.
	m_Texture1 = new TextureClass;
	if (!m_Texture1)
	{
		return false;
	}

	// 첫번째 텍스처 오브젝트를 초기화한다
	bool result = m_Texture1->Initialize(device, textureFilename1);
	if (!result)
	{
		return false;
	}

	// 두번째 텍스처 오브젝트를 생성한다.
	m_Texture2 = new TextureClass;
	if (!m_Texture2)
	{
		return false;
	}

	// 두번째 텍스처 오브젝트를 초기화한다
	result = m_Texture2->Initialize(device, textureFilename2);
	if (!result)
	{
		return false;
	}

	// 세번째 텍스처 오브젝트를 생성한다.
	m_Texture3 = new TextureClass;
	if (!m_Texture3)
	{
		return false;
	}

	// 세번째 텍스처 오브젝트를 초기화한다
	result = m_Texture3->Initialize(device, textureFilename3);
	if (!result)
	{
		return false;
	}

	return true;
}
void ModelClass::ReleaseTextures()
{
	// 텍스처 오브젝트를 해제한다
	if (m_Texture1)
	{
		m_Texture1->Shutdown();
		delete m_Texture1;
		m_Texture1 = 0;
	}

	if (m_Texture2)
	{
		m_Texture2->Shutdown();
		delete m_Texture2;
		m_Texture2 = 0;
	}

	if (m_Texture3)
	{
		m_Texture3->Shutdown();
		delete m_Texture3;
		m_Texture3 = 0;
	}
}

bool ModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;
	bool result;
	
	{
		m_temp = filename;
		int index = m_temp.find("obj");
		m_temp.erase(index, index + 2);
		m_temp = m_temp + "txt";
		
		model = (char*)m_temp.c_str();
		
		fin.open(model);
		if (fin.fail()) {

			result = LoadObject(filename);
			if (!result)
			{
				return false;
			}

		}

	}

	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();
	return true;
}
bool ModelClass::LoadModelForEffect(const char * filename)
{
	// 모델 파일을 엽니다.
	ifstream fin;
	fin.open(filename);

	// 파일을 열 수 없으면 종료합니다.
	if (fin.fail())
	{
		return false;
	}

	// 버텍스 카운트의 값까지 읽는다.
	char input = 0;
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// 버텍스 카운트를 읽는다.
	fin >> m_vertexCount;

	// 인덱스의 수를 정점 수와 같게 설정합니다.
	m_indexCount = m_vertexCount;

	// 읽어 들인 정점 개수를 사용하여 모델을 만듭니다.
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// 데이터의 시작 부분까지 읽는다.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// 버텍스 데이터를 읽습니다.
	for (int i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// 모델 파일을 닫는다.
	fin.close();
}
void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}
	return;
}

void ModelClass::SetPosition(float x, float y, float z)
{
	m_rotation.x = x; m_rotation.y = y; m_rotation.z = z;
}
void ModelClass::SetPosition(D3DXVECTOR3 pos)
{
	m_position = pos;

}
D3DXVECTOR3 ModelClass::GetPosition()
{
	return m_position;
}

void ModelClass::SetRotation(D3DXVECTOR3 rot)
{
	m_rotation = rot;
}
D3DXVECTOR3 ModelClass::GetRotation()
{
	return m_rotation;
}

void ModelClass::SetCollsionSphere(D3DXVECTOR3 center, float radius)
{
	m_sphere->center = center;
	m_sphere->radius = radius;
}

void ModelClass::SetCollsionSphereCenter(D3DXVECTOR3 center)
{
	m_sphere->center = center;
}

void ModelClass::GetCollsionSphere(D3DXVECTOR3 &center, float &radius)
{
	center = m_sphere->center;
	radius = m_sphere->radius;
}


bool ModelClass::LoadObject(char* filename)
{
	bool result;
	int vertexCount, textureCount, normalCount, faceCount;

	result = ReadFileCounts(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return false;
	}
	result = LoadDataStructures(filename, vertexCount, textureCount, normalCount, faceCount);
	if (!result)
	{
		return false;
	}

	return true;

}
bool ModelClass::ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;
	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;
	// Open the file.
	fin.open(filename);
	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}
	// Read from the file and continue to read until the end of the file is reached.
	fin.get(input);
	while (!fin.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}
		// If the line starts with 'f' then increment the face count.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}
		// Otherwise read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}
		// Start reading the beginning of the next line.
		fin.get(input);
	}
	// Close the file.
	fin.close();
	return true;
}
bool ModelClass::LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount)
{
	VertexTypeF *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input = NULL, input2 = NULL;
	ofstream fout;
	// Initialize the four data structures.
	vertices = new VertexTypeF[vertexCount];
	if (!vertices)
	{
		return false;
	}
	texcoords = new VertexTypeF[textureCount];
	if (!texcoords)
	{
		return false;
	}
	normals = new VertexTypeF[normalCount];
	if (!normals)
	{
		return false;
	}
	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}
	// Initialize the indexes.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;
	// Open the file.
	fin.open(filename);
	// Check if it was successful in opening the file.
	if (fin.fail() == true)
	{
		return false;
	}
	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);
			// Read in the vertices.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >>
					vertices[vertexIndex].z;
				// Invert the Z vertex to change to left hand system.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}
			// Read in the texture uv coordinates.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;
				// Invert the V texture coordinates to left hand system.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}
			// Read in the normals.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >>
					normals[normalIndex].z;
				// Invert the Z normal to change to left hand system.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}
		// Read in the faces.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >>
					input2 >> faces[faceIndex].nIndex3 >> faces[faceIndex].vIndex2 >> input2
					>> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2 >>
					faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >>
					faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}
		// Read in the remainder of the line.
		while (input != '\n')
		{
			fin.get(input);
		}
		// Start reading the beginning of the next line.
		fin.get(input);
	}
	m_temp = filename;
	int index = m_temp.find("obj");
	m_temp.erase(index, index + 2);
	m_temp = m_temp + "txt";

	model = (char*)m_temp.c_str();
	
	// Close the file.
	fin.close();
	// Open the output file.
	fout.open(model);
	// Write out the file header that our model format uses.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;
	// Now loop through all the faces and output the three vertices for each face.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;
		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;
		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;
		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}
	// Close the output file.
	fout.close();
	// Release the four data structures.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}
	return true;
}