/********************************************************************
	created:	2:7:2013   22:35
	filename	Camera.h
	author:		maval

	purpose:	�������.
*********************************************************************/
#ifndef Camera_h__
#define Camera_h__

#include "Prerequiestity.h"
#include "MathDef.h"

class Camera
{
public:
	Camera();

	bool	m_bActive;

public:
	void	Update();

	void	SetNearClip(float n);
	void	SetFarClip(float f);
	void	SetAspectRatio(float r);
	void	SetPosition(const VEC3& pos);
	void	SetDirection(const VEC3& dir);
	void	Yaw(float angle);
	void	SetMoveSpeed(float fSpeed) { m_moveSpeed = fSpeed; }
	void	AddMoveSpeed(float delta);
	float	GetMoveSpeed()	{ return m_moveSpeed; }

	const VEC4&		GetPos() const		{ return m_viewPt;	}
	VEC4			GetDirection() const;
	VEC4			GetRight() const;
	float	GetNearClip() const	{ return m_nearClip; }
	float	GetFarClip() const	{ return m_farClip; }
	float	GetFov() const		{ return m_fov; }
	float	GetAspectRatio() const	{ return m_aspectRatio; }
	void	GetFarCorner(VEC4 v[4]);

	const MAT44&	GetViewMatrix() const	{ return m_matView; }
	const MAT44&	GetProjMatrix() const	{ return m_matProj; }

	void	_BuildViewMatrix();
	void	_BuildProjMatrix();

private:
	VEC4	m_viewPt;

	float	m_nearClip;
	float	m_farClip;
	float	m_fov;			//xz����Ұ��(����ֵ)
	float	m_aspectRatio;
	VEC4	m_farCorner[4];

	bool	m_fixYawAxis;	//�̶�yaw��Ϊy��,һ��������������͹���.����ģ�����͵Ĳ�fix,��Ϊ��Ҫroll.
	float	m_moveSpeed;

	MAT44	m_matView;
	MAT44	m_matProj;
	MAT44	m_matRot;		//�������������ת
};

#endif // Camera_h__