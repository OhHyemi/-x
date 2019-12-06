#pragma once
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_
//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();
	void SetPosition(float, float, float);
	void SetPosition(D3DXVECTOR3);
	void SetRotation(float, float, float);
	void SetRotation(D3DXVECTOR3);
	D3DXVECTOR3 GetLookAt();
	D3DXVECTOR3 Geteyes();
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void SetLookAt(D3DXVECTOR3);
	void Seteyes(D3DXVECTOR3);
	void Render();
	void GetViewMatrix(D3DXMATRIX&);
	//float m_positionX, m_positionY, m_positionZ;
	D3DXVECTOR3 up, lookAt, eyes;
	//float m_rotationX, m_rotationY, m_rotationZ;

private:
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_rotation;
	
	D3DXMATRIX m_viewMatrix;
};\

#endif