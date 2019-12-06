#include "FrustumClass.h"

#include <DirectXMath.h>

FrustumClass::FrustumClass()
{
}


FrustumClass::FrustumClass(const FrustumClass& other)
{
}


FrustumClass::~FrustumClass()
{
}




void FrustumClass::ConstructFrustum(float screenDepth, D3DXMATRIX projectionMatrix, D3DXMATRIX viewMatrix)
{
	// ���� ����� D3DXMATRIX �������� ��ȯ�մϴ�.
	D3DXMATRIX pMatrix = projectionMatrix;
	//XMStoreFloat4x4(&pMatrix, projectionMatrix);

	// ����ü���� �ּ� Z �Ÿ��� ����մϴ�.
	float zMinimum = -pMatrix._43 / pMatrix._33;
	float r = screenDepth / (screenDepth - zMinimum);

	// ������Ʈ �� ���� �ٽ� ���� ��Ŀ� �����մϴ�.
	pMatrix._33 = r;
	pMatrix._43 = -r * zMinimum;
	//projectionMatrix = XMLoadFloat4x4(&pMatrix);
	projectionMatrix = pMatrix;

	// �� ��Ʈ������ ������Ʈ �� �������� ��Ʈ�������� ����ü ��Ʈ������ ����ϴ�.
	D3DXMATRIX finalMatrix;// = D3DXMATRIXMultiply(viewMatrix, projectionMatrix);
	D3DXMatrixMultiply(&finalMatrix, &viewMatrix, &projectionMatrix);

	// ���� ����� D3DXMATRIX �������� ��ȯ�մϴ�.
	D3DXMATRIX matrix = finalMatrix;
	//XMStoreFloat4x4(&matrix, finalMatrix);

	// ����ü�� ����� ����� ����մϴ�.
	float x = (float)(matrix._14 + matrix._13);
	float y = (float)(matrix._24 + matrix._23);
	float z = (float)(matrix._34 + matrix._33);
	float w = (float)(matrix._44 + matrix._43);
	m_planes[0] = D3DXPLANE(x, y, z, w);
	//m_planes[0] = XMPlaneNormalize(m_planes[0]);
	D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

	// ����ü�� �� ����� ����մϴ�.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[1] = D3DXPLANE(x, y, z, w);
	//m_planes[1] = XMPlaneNormalize(m_planes[1]);
	D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

	// ����ü�� ���� ����� ����մϴ�.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[2] = D3DXPLANE(x, y, z, w);
	//m_planes[2] = XMPlaneNormalize(m_planes[2]);
	D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

	// ����ü�� ������ ����� ����մϴ�.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[3] = D3DXPLANE(x, y, z, w);
	//m_planes[3] = XMPlaneNormalize(m_planes[3]);
	D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

	// ����ü�� �� ����� ����մϴ�.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[4] = D3DXPLANE(x, y, z, w);
	//m_planes[4] = XMPlaneNormalize(m_planes[4]);
	D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

	// ����ü�� �Ʒ� ����� ����մϴ�.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[5] = D3DXPLANE(x, y, z, w);
	//m_planes[5] = XMPlaneNormalize(m_planes[5]);
	D3DXPlaneNormalize(&m_planes[5], &m_planes[5]);
}


bool FrustumClass::CheckPoint(float x, float y, float z)
{
	for (int i = 0; i<6; i++)
	{
		// ����Ʈ�� �� frustum�� 6 �� ��� ��� �ȿ� �ִ��� Ȯ���մϴ�.
		//if (D3DXVectorGetX(XMPlaneDotCoord(m_planes[i], D3DXPLANE(x, y, z, 1.0f))) < 0.0f)
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4(x, y, z, 1.0f))) < 0.0f)
			return false;
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	// �� ������ �ҿ� ť���� �� ���� �ִ��� Ȯ���մϴ�.
	for (int i = 0; i<6; i++)
	{
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - radius), (yCenter - radius), (zCenter - radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + radius), (yCenter - radius), (zCenter - radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - radius), (yCenter + radius), (zCenter - radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + radius), (yCenter + radius), (zCenter - radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - radius), (yCenter - radius), (zCenter + radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + radius), (yCenter - radius), (zCenter + radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - radius), (yCenter + radius), (zCenter + radius), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + radius), (yCenter + radius), (zCenter + radius), 1.0f))) >= 0.0f)
			continue;

		return false;
	}

	return true;
}


bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	for (int i = 0; i<6; i++)
	{
		// ���� �ݰ��� �� frustum �ȿ� �ִ��� Ȯ���մϴ�.
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4(xCenter, yCenter, zCenter, 1.0f))) < -radius)
			return false;
	}

	return true;
}


bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	// �簢���� 6 ���� ��� �� �ϳ��� �� frustum �ȿ� �ִ��� Ȯ���մϴ�.
	for (int i = 0; i<6; i++)
	{
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - xSize), (yCenter - ySize), (zCenter - zSize), 1.0f))) >= 0.0f)
			continue;
		
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + xSize), (yCenter - ySize), (zCenter - zSize), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - xSize), (yCenter + ySize), (zCenter - zSize), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - xSize), (yCenter - ySize), (zCenter + zSize), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + xSize), (yCenter + ySize), (zCenter - zSize), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + xSize), (yCenter - ySize), (zCenter + zSize), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter - xSize), (yCenter + ySize), (zCenter + zSize), 1.0f))) >= 0.0f)
			continue;

		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4((xCenter + xSize), (yCenter + ySize), (zCenter + zSize), 1.0f))) >= 0.0f)
			continue;

		return false;
	}

	return true;
}