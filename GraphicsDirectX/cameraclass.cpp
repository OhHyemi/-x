#include "cameraclass.h"
CameraClass::CameraClass()
{
	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	
}
CameraClass::CameraClass(const CameraClass& other)
{
}
CameraClass::~CameraClass()
{
}
void CameraClass::SetPosition(float x, float y, float z)
{
	
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	return;
}

void CameraClass::SetPosition(D3DXVECTOR3 position)
{
	m_position = position;
	return;

}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
	return;
}

void CameraClass::SetRotation(D3DXVECTOR3 rotation)
{

	m_rotation = rotation;
	return;
}

D3DXVECTOR3 CameraClass::GetLookAt()
{
	return lookAt;
}

D3DXVECTOR3 CameraClass::Geteyes()
{
	return eyes;
}

D3DXVECTOR3 CameraClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 CameraClass::GetRotation()
{
	return m_rotation;
}

void CameraClass::SetLookAt(D3DXVECTOR3 lookat)
{
	lookat = lookat;
}

void CameraClass::Seteyes(D3DXVECTOR3 eyes)
{
	eyes = eyes;
}


void CameraClass::Render()
{
	float yaw, pitch, roll;
	D3DXVECTOR3 up,lookAt,eyes;
	D3DXMATRIX rotationMatrix;
	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	eyes = m_position;
	
	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.

	pitch = m_rotation.x * 0.0174532925f;
	yaw = m_rotation.y * 0.0174532925f;
	roll = m_rotation.z * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);
	
	// Translate the rotated camera position to the location of the viewer.
	lookAt = eyes + lookAt;
	
	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &eyes, &lookAt, &up);
	
	return;
}

void CameraClass::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

