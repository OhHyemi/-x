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
	// 투영 행렬을 D3DXMATRIX 유형으로 변환합니다.
	D3DXMATRIX pMatrix = projectionMatrix;
	//XMStoreFloat4x4(&pMatrix, projectionMatrix);

	// 절두체에서 최소 Z 거리를 계산합니다.
	float zMinimum = -pMatrix._43 / pMatrix._33;
	float r = screenDepth / (screenDepth - zMinimum);

	// 업데이트 된 값을 다시 투영 행렬에 설정합니다.
	pMatrix._33 = r;
	pMatrix._43 = -r * zMinimum;
	//projectionMatrix = XMLoadFloat4x4(&pMatrix);
	projectionMatrix = pMatrix;

	// 뷰 매트릭스와 업데이트 된 프로젝션 매트릭스에서 절두체 매트릭스를 만듭니다.
	D3DXMATRIX finalMatrix;// = D3DXMATRIXMultiply(viewMatrix, projectionMatrix);
	D3DXMatrixMultiply(&finalMatrix, &viewMatrix, &projectionMatrix);

	// 최종 행렬을 D3DXMATRIX 유형으로 변환합니다.
	D3DXMATRIX matrix = finalMatrix;
	//XMStoreFloat4x4(&matrix, finalMatrix);

	// 절두체의 가까운 평면을 계산합니다.
	float x = (float)(matrix._14 + matrix._13);
	float y = (float)(matrix._24 + matrix._23);
	float z = (float)(matrix._34 + matrix._33);
	float w = (float)(matrix._44 + matrix._43);
	m_planes[0] = D3DXPLANE(x, y, z, w);
	//m_planes[0] = XMPlaneNormalize(m_planes[0]);
	D3DXPlaneNormalize(&m_planes[0], &m_planes[0]);

	// 절두체의 먼 평면을 계산합니다.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[1] = D3DXPLANE(x, y, z, w);
	//m_planes[1] = XMPlaneNormalize(m_planes[1]);
	D3DXPlaneNormalize(&m_planes[1], &m_planes[1]);

	// 절두체의 왼쪽 평면을 계산합니다.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[2] = D3DXPLANE(x, y, z, w);
	//m_planes[2] = XMPlaneNormalize(m_planes[2]);
	D3DXPlaneNormalize(&m_planes[2], &m_planes[2]);

	// 절두체의 오른쪽 평면을 계산합니다.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[3] = D3DXPLANE(x, y, z, w);
	//m_planes[3] = XMPlaneNormalize(m_planes[3]);
	D3DXPlaneNormalize(&m_planes[3], &m_planes[3]);

	// 절두체의 윗 평면을 계산합니다.
	x = (float)(matrix._14 + matrix._13);
	y = (float)(matrix._24 + matrix._23);
	z = (float)(matrix._34 + matrix._33);
	w = (float)(matrix._44 + matrix._43);
	m_planes[4] = D3DXPLANE(x, y, z, w);
	//m_planes[4] = XMPlaneNormalize(m_planes[4]);
	D3DXPlaneNormalize(&m_planes[4], &m_planes[4]);

	// 절두체의 아래 평면을 계산합니다.
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
		// 포인트가 뷰 frustum의 6 개 평면 모두 안에 있는지 확인합니다.
		//if (D3DXVectorGetX(XMPlaneDotCoord(m_planes[i], D3DXPLANE(x, y, z, 1.0f))) < 0.0f)
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4(x, y, z, 1.0f))) < 0.0f)
			return false;
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	// 뷰 프러스 텀에 큐브의 한 점이 있는지 확인합니다.
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
		// 구의 반경이 뷰 frustum 안에 있는지 확인합니다.
		if (D3DXVectorGetX(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR4(xCenter, yCenter, zCenter, 1.0f))) < -radius)
			return false;
	}

	return true;
}


bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	// 사각형의 6 개의 평면 중 하나가 뷰 frustum 안에 있는지 확인합니다.
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