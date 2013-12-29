/********************************************************************
	created:	20:1:2013   1:05
	filename: 	ManipulatorCamera.h
	author:		maval
	
	purpose:	��������ܹ���
*********************************************************************/
#ifndef ManipulatorCamera_h__
#define ManipulatorCamera_h__

#include "EditorDefine.h"
#include "ManipulatorEventCallback.h"
#include "Action/ActionBase.h"

//----------------------------------------------------------------------------------------
class ManipulatorCamera : public ManipulatorSceneEventCallback
{
public:
	ManipulatorCamera();
	~ManipulatorCamera() {}

	//////////////�¼��ص�
	virtual void	OnSceneNew()	{ Reset(); }
	virtual void	OnSceneOpen()	{ Reset(); }

public:
	void	Reset();
	void	SetType(eCameraType type);
	//Ҫ��������������Ͳ�����
//	void	SetModelViewerTarget(Ogre::Entity* pTarget);

	void	OnLButtonDown(const SActionParam& param);
	void	OnLButtonUp(const SActionParam& param);
	void	OnRButtonDown(const SActionParam& param);
	void	OnRButtonUp(const SActionParam& param);
	void	OnMouseMove(const SActionParam& param);
	void	OnMouseWheel(short nNotch);
	void	OnKeyDown(UINT nChar);
	void	OnKeyUp(UINT nChar);

private:
	Neo::Camera*	m_pCamera;
	eCameraType		m_type;
	bool			m_bRBDown;
	bool			m_bLBDown;
	POINT			m_ptLast;
};


#endif // ManipulatorCamera_h__







