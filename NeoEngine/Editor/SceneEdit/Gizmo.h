/********************************************************************
	created:	22:12:2012   12:01
	filename: 	Gizmo.h
	author:		maval
	
	purpose:	�༭���õĸ���ָʾ��
*********************************************************************/
#ifndef Gizmo_h__
#define Gizmo_h__



//
//����
//
class GizmoRectangle/* : public Ogre::SimpleRenderable*/
{
public:
	GizmoRectangle() {}
	virtual ~GizmoRectangle();

public:
// 	virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const { (void)cam; return 0; }
// 	virtual Ogre::Real getBoundingRadius(void) const { return 0; }

public:
	void	InitRenderable(float w, float h);
	void	DestroyRenderable();
	void	UpdatePosition(const VEC3& pos, float w, float h);

protected:
	//���ص�λ����.��Ϊ��������ֱ�Ӹ�����������
	//virtual void getWorldTransforms( Ogre::Matrix4* xform ) const;

private:
	//��ķֲ��ܶ�,��1�����絥λ��Ӧ��ĸ���
	static const int POINT_DENSITY = 5;
};

//
//Բ��
//
class GizmoCircle/* : public Ogre::SimpleRenderable*/
{
public:
	GizmoCircle() {}
	virtual ~GizmoCircle();

public:
// 	virtual Ogre::Real getSquaredViewDepth(const Ogre::Camera* cam) const { (void)cam; return 0; }
// 	virtual Ogre::Real getBoundingRadius(void) const { return 0; }

public:
	void	InitRenderable();
	void	DestroyRenderable() {}
};

//
//���������ת��
//
class GizmoAxis
{
public:
	GizmoAxis();
	~GizmoAxis();

	enum eAxis
	{
		eAxis_X,
		eAxis_Y,
		eAxis_Z,
		eAxis_None
	};

public:
// 	void	Attach(Ogre::Node* pNode);
 	void	Show(bool bShow, bool bMoveOrRotate);
 	void	Reset();
 	void	OnGizmoNodeReset();
 	void	HighlightAxis(bool bHighlight, eAxis axis, int mode);
// 	void	Update(const Ogre::Ray& ray, int mode);
	bool	IsActive() const { return m_curActiveAxis != eAxis_None; }
	eAxis	GetActiveAxis() const { return m_curActiveAxis; }

private:
	void	_Init();
	void	_Destroy();

private:
// 	Ogre::SceneNode*	m_pObjGizmoNode;
// 	Ogre::Node*			m_pAttachNode;
// 	Ogre::Entity*		m_pAxisMove[3];		//������
// 	Ogre::Entity*		m_pAxisRotate[3];	//��ת��
// 	Ogre::Plane			m_plane[3];			//����ƽ��,�������ʰȡ
	eAxis				m_curActiveAxis;	//��ǰ������
};


#endif // Gizmo_h__







