/********************************************************************
	created:	17:3:2013   11:34
	filename	ManipulatorOperation.h
	author:		maval

	purpose:	Undo/Redo������
*********************************************************************/
#ifndef ManipulatorOperation_h__
#define ManipulatorOperation_h__

class Operation;
//----------------------------------------------------------------------------------------
class ManipulatorOperation
{
public:
	ManipulatorOperation();
	~ManipulatorOperation();

public:
	template<class T>
	T*				NewOperation();
	//һ������������,ͬʱ����������������
	void			Commit(Operation* newOp);
	void			Undo();
	void			Redo();
	//�е�Operationֱ�ӱ���������ָ��,��Ȼ���屻ɾ���ٻ���,����ʧЧ��,������������
//	void			RebindEntity(Ogre::Entity* pOld, Ogre::Entity* pNew);
	int				SnapshotMake();
	bool			SnapshotCheck(int snapshot);

private:
	int				m_snapshot;		//���ݿ���ȷ���Ƿ���ʾ�û���Ҫ���泡��
	typedef std::list<Operation*>	OperationStack;
	OperationStack	m_lstUndo;
	OperationStack	m_lstRedo;
};

template<class T>
T* ManipulatorOperation::NewOperation()
{
	return new T;
}

#endif // ManipulatorOperation_h__





