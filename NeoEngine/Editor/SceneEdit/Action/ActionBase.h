/********************************************************************
	created:	24:12:2012   0:02
	filename: 	ActionBase.h
	author:		maval
	
	purpose:	�༭����Ϊ״̬����.����״̬ģʽ����༭����������Ϊ״̬,��
				�ƶ�����,ˢ���θ߶ȵȵ�������Ϊ.
*********************************************************************/
#ifndef ActionBase_h__
#define ActionBase_h__



//ActionЯ������
struct SActionParam 
{
	POINT		m_ptScreen;		//������Ļ����
	VEC2		m_ptPixel;		//�����View������,���ض���
	VEC2		m_ptRelative;	//�����View������,��Զ���
	VEC2		m_ptDeltaRel;	//�����View����֮֡�������ƫ��,��Զ���
	bool		m_bHitTerrain;	//������ڵ����߲�ѯ�Ƿ���е���
	VEC3		m_ptTerrain;	//������ڵ��ཻ�ĵ�������
};


class ActionBase
{
public:
	ActionBase() {}
	virtual ~ActionBase() {}

public:
	virtual	void	Enter() = 0;
	virtual void	Leave()	= 0;
	virtual	void	OnMouseLButtonDown(const SActionParam& param) {}
	virtual void	OnMouseLButtonUp(const SActionParam& param) {}
	virtual void	OnMouseRButtonDown(const SActionParam& param) {}
	virtual void	OnMouseRButtonUp(const SActionParam& param) {}
	virtual void	OnMouseMove(const SActionParam& param) {}
	virtual void	OnFrameMove(float dt) {}
};


#endif // ActionBase_h__







