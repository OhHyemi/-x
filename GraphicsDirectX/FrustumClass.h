#pragma once

#include "d3dclass.h"

class FrustumClass//: public AlignedAllocationPolicy<16>
{
public:
	FrustumClass();
	FrustumClass(const FrustumClass&);
	~FrustumClass();

	void ConstructFrustum(float, D3DXMATRIX , D3DXMATRIX );

	bool CheckPoint(float, float, float);
	bool CheckCube(float, float, float, float);
	bool CheckSphere(float, float, float, float);
	bool CheckRectangle(float, float, float, float, float, float);

private:
	D3DXPLANE m_planes[6];

private:
	FLOAT D3DXVectorGetX(CONST D3DXVECTOR4 V)
	{
		if (!V)	return 0.0f;
		return V.x;
	}
	D3DXVECTOR4 D3DXPlaneDotCoord(CONST D3DXPLANE* P, CONST D3DXVECTOR4* V)
	{
		if (!P || !V)	return D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);

		D3DXVECTOR4 vectorOut;

		vectorOut.x = P->a * V->x + P->b * V->y + P->c * V->z + P->d * 1.0f;
		vectorOut.y = P->a * V->x + P->b * V->y + P->c * V->z + P->d * 1.0f;
		vectorOut.z = P->a * V->x + P->b * V->y + P->c * V->z + P->d * 1.0f;
		vectorOut.w = P->a * V->x + P->b * V->y + P->c * V->z + P->d * 1.0f;

		return vectorOut;
	}
};