/********************************************************************
	created:	22:12:2012   10:35
	filename: 	Brush.h
	author:		maval
	
	purpose:	���λ�ˢ
*********************************************************************/
#ifndef Brush_h__
#define Brush_h__



class GizmoCircle;
class GizmoRectangle;

//
//��ˢ����
//
class Brush
{
public:
	Brush();
	virtual ~Brush() {}

public:
	virtual	void	SetPosition(const VEC3& pos) { m_pos = pos; }
	virtual void	OnGizmoNodeReset() = 0;
	//��Բ�λ�ˢ,dim1=�ھ�,dim2=�⾶
	//�Է��λ�ˢ,dim1=��,dim2=��
	virtual void	SetDimension(float dim1, float dim2) = 0;
	virtual void	GetDimension(float& dim1, float& dim2) = 0;

public:
	void		SetActive(bool bActive);
	bool		GetActive() const { return m_bActive; }
	const VEC3&	GetPosition() const { return m_pos; }

protected:
	//SCENENODE*		m_pNode;
	bool			m_bActive;
	VEC3			m_pos;
};



//
//Բ�λ�ˢ
//
class BrushCircle : public Brush
{
public:
	BrushCircle();
	~BrushCircle();

public:
	virtual	void	SetPosition(const VEC3& pos) {}
	virtual void	OnGizmoNodeReset() {}
	virtual void	SetDimension(float dim1, float dim2) {}
	virtual void	GetDimension(float& dim1, float& dim2) {}

private:
	GizmoCircle*	m_pRenderable;
};

//
//���λ�ˢ
//
class BrushSquare : public Brush
{
public:
	BrushSquare();
	~BrushSquare();

public:
	virtual	void	SetPosition(const VEC3& pos);
	virtual void	OnGizmoNodeReset();
	virtual void	SetDimension(float dim1, float dim2);
	virtual void	GetDimension(float& dim1, float& dim2) { dim1=m_width; dim2=m_height; }

public:
	void			SetWidth(float w);
	void			SetHeight(float h);

private:
	GizmoRectangle*	m_pRenderable;
	float			m_width;
	float			m_height;
};


#endif // Brush_h__



