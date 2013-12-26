/********************************************************************
	created:	20:12:2012   0:39
	filename: 	ManipulatorObject.h
	author:		maval
	
	purpose:	�ɰڷ����崴��,����,�ٿ�.
*********************************************************************/
#ifndef ManipulatorObject_h__
#define ManipulatorObject_h__


#include "ManipulatorEventCallback.h"
#include "EditorDefine.h"

class GizmoAxis;


///������Ϣ��װ�ṹ
struct SObjectInfo 
{
	SObjectInfo() {}
	std::string		m_meshname;
	VEC3			m_pos;
	MAT44			m_rot;
	VEC3			m_scale;
};

//typedef std::unordered_map<Ogre::Entity*, SObjectInfo*> ObjectContainer;

//----------------------------------------------------------------------------------------
class ManipulatorObject 
	: public ManipulatorSceneEventCallback
	, public EventCallbackManager<ManipulatorObjectEventCallback>
{
public:
	enum eEditMode
	{
		eEditMode_None,
		eEditMode_Move,
		eEditMode_Rotate,
		eEditMode_Scale,
		eEditMode_Select
	};

	//////////////�¼��ص�
	virtual void	OnSceneClose();
	virtual void	OnSceneNew();
	virtual void	OnSceneOpen();

public:
	ManipulatorObject();
	~ManipulatorObject();

public:
	void					Load(rapidxml::xml_node<>* XMLNode);
	void					Serialize(rapidxml::xml_document<>* doc, rapidxml::xml_node<>* XMLNode);
	void					OnFrameMove(float dt);
 	eEditMode				GetCurEditMode() const { return m_curEditMode; }
 	void					SetCurEditMode(eEditMode mode) { m_curEditMode = mode; }
// 	const ObjectContainer&	GetAllObjects() const { return m_objects; }
// 	void					SetObjectInfo(Ogre::Entity* ent, const SObjectInfo& info);
// 	SObjectInfo*			GetObjectInfo(Ogre::Entity* ent);

	//����Entity
//	void					AddGrass(const VEC3& pos, const MAT44& orient = ORIENT_IDENTITY, const VEC3& scale = VEC3(1,1,1));
// 	void					AddEntity(const STRING& meshname, const VEC3& worldPos, bool bOp = true,
// 		const MAT44& orient = ORIENT_IDENTITY, const VEC3& scale = VEC3(1,1,1));
// 	Ogre::Entity*			AddEntity(const Ogre::String& meshname, const Ogre::Vector2& screenPos);
// 	//ɾ������
// 	void					RemoveEntity(Ogre::Entity* ent, bool bOp = true);
// 
// 	///����ѡ��/�༭
// 	void					SetSelection(Ogre::Entity* pEnt);
// 	Ogre::Entity*			GetSelection() const { return m_pSelectEntity; }
 	void					ClearSelection();
// 	void					SetPosition(Ogre::Entity* ent, const Ogre::Vector3& newPos, bool bOp = true);
// 	void					SetOrientation(Ogre::Entity* ent, const Ogre::Quaternion& orient, bool bOp = true);
// 	void					SetScale(Ogre::Entity* ent, const Ogre::Vector3 scale, bool bOp = true);
// 	void					Rotate(Ogre::Entity* ent, float radian, bool bOp = true);
// 	void					Scale(Ogre::Entity* ent, const Ogre::Vector3& scaleMultiplier, bool bOp = true);
// 
// 	//ȡ��Entity�İ�Χ��Gizmo.��Χ����ʾ�������Լ�����,��ʹ��OGREĬ�ϵ�showBoundingBox
// 	Ogre::WireBoundingBox*	GetEntityAABBGizmo(Ogre::Entity* pEntity);
// 	//���ݲ���ģʽ,��ʾ������Ӧ��Gizmo
// 	void					ShowEntityGizmo(Ogre::Entity* pEntity, bool bShow, eEditMode mode, bool bDrift = false);
 	GizmoAxis*				GetGizmoAxis() const { return m_pGizmoAixs; }
 	void					OnGizmoNodeReset();
// 	void					CommitEditOperation(Ogre::Entity* ent, eEditMode mode, const Ogre::Any& oldValue, const Ogre::Any& newValue);
// 
// 	//���߲�ѯ
// 	Ogre::MovableObject* DoRaySceneQuery(const Ogre::Ray& ray, int queryMask = 0xffffffff);
// 	void		DoAABBSceneQuery(const Ogre::AxisAlignedBox& aabb, int queryMask = 0xffffffff);
// 
// private:
// 	void		_UpdateAABBOfEntity(Ogre::Entity* pEntity);

private:
// 	ObjectContainer	m_objects;			//�����е����аڷ�����
 	eEditMode		m_curEditMode;
// 	Ogre::Entity*	m_pSelectEntity;	//��ǰѡ������
 	GizmoAxis*		m_pGizmoAixs;		//������ָʾ��
// 	Ogre::RaySceneQuery* m_pRaySceneQuery;
// 	Ogre::AxisAlignedBoxSceneQuery*	m_pAABBSceneQuery;
};


#endif // ManipulatorObject_h__







