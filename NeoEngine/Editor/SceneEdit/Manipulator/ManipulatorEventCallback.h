/********************************************************************
	created:	27:12:2012   20:44
	filename: 	ManipulatorEventCallback.h
	author:		maval
	
	purpose:	��Manipulator�¼��ص���
*********************************************************************/

#ifndef ManipulatorEventCallback_h__
#define ManipulatorEventCallback_h__

#include "EventCallbackBase.h"

////////////////////////////////////////////////////////////////////////
///ManipulatorScene�ص��¼�
class ManipulatorSceneEventCallback : public EventCallbackBase
{
public:
	virtual	void	OnSceneNew() {}
	virtual	void	OnSceneOpen() {}
	virtual void	OnSceneClose() {}
};

////////////////////////////////////////////////////////////////////////
///ManipulatorObject�ص��¼�
class ManipulatorObjectEventCallback : public EventCallbackBase
{
public:
// 	virtual void	OnObjectSetSelection(Ogre::Entity* pObject) {}
// 	virtual void	OnObjectClearSelection(Ogre::Entity* pObject) {}
// 	virtual	void	OnObjectPropertyChanged(Ogre::Entity* pObject) {}
};


#endif // ManipulatorEventCallback_h__






