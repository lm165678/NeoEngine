/********************************************************************
	created:	1:12:2013   17:28
	filename: 	IRefCount.h
	author:		maval
	
	purpose:	���ü�����.
				Ŀǰ���̰߳�ȫ֧��.
*********************************************************************/
#ifndef IRefCount_h__
#define IRefCount_h__

class IRefCount
{
public:
	IRefCount():m_refCnt(1) {}
	virtual ~IRefCount() { Release(); }

	void	AddRef()	{ ++m_refCnt; }
	void	Release()
	{
		assert(m_refCnt > 0);
		if (--m_refCnt == 0)
			delete this;
	}

private:
	int		m_refCnt;
};

#endif // IRefCount_h__