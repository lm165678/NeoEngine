/********************************************************************
	created:	30:4:2013   21:43
	filename	EventCallbackBase.h
	author:		maval

	purpose:	�¼��ص�����
*********************************************************************/

#ifndef EventCallbackBase_h__
#define EventCallbackBase_h__


////////////////////////////////////////////////////////////////////////
///�¼��ص�������
template<class TBase>
class EventCallbackManager : public TBase
{
public:
	EventCallbackManager() {}
	virtual ~EventCallbackManager() {}

public:
	void	AddCallback(TBase* pCB);
	void	RemoveCallback(TBase* pCB);
	void	RemoveAllCallbacks();
	//������ע��ļ�����ִ�лص�
	//����д��Ϊ�˽���������m_listeners�����
	template<class Func> void	Excute(Func&& fun)
	{
		std::for_each(m_listeners.begin(), m_listeners.end(), fun);
	}

private:
	typedef std::list<TBase*>	lstListeners;
	lstListeners	m_listeners;
};

template<class T> void EventCallbackManager<T>::AddCallback( T* pCB )
{
	assert(std::find(m_listeners.begin(), m_listeners.end(), pCB) == m_listeners.end() && "The callback had already registered!");
	m_listeners.push_back(pCB);
}

template<class T> void EventCallbackManager<T>::RemoveCallback( T* pCB )
{
	auto iter = std::find(m_listeners.begin(), m_listeners.end(), pCB);
	assert(iter != m_listeners.end() && "The callback didn't registered!");
	m_listeners.erase(iter);
}

template<class T> void EventCallbackManager<T>::RemoveAllCallbacks()
{
	m_listeners.clear();
}

////////////////////////////////////////////////////////////////////////
///�¼��ص�����
class EventCallbackBase
{
public:
	virtual ~EventCallbackBase() {}
};

#endif // EventCallbackBase_h__