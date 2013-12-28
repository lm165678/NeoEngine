/********************************************************************
	created:	14:10:2012   9:15
	filename: 	Application.h
	author:		maval
	
	purpose:	�༭��Ӧ�ó�������
*********************************************************************/

#ifndef Application_h__
#define Application_h__

struct SActionParam;

class Application
{
public:
	Application();
	~Application() {}

public:
	bool		Init(HWND hwnd, HWND hParent);
	bool		Update();
	void		Shutdown();
	//��Ⱦ�ӿڴ�С�ı�,������Ӧ����
	void		OnWindowResize(int w, int h);

	void		SceneNew();
	void		SceneOpen();
	void		SceneSave();
	bool		SceneClose();

	void		OnLButtonDown(const POINT& pt);
	void		OnLButtonUp(const POINT& pt);
	void		OnRButtonDown(const POINT& pt);
	void		OnRButtonUp(const POINT& pt);
	void		OnMouseMove(const POINT& pt);
	void		OnMouseWheel(short nNotch);
	void		OnKeyDown(UINT nChar);
	void		OnKeyUp(UINT nChar);

private:
	void		_UpdateInput(float dt);
	void		_CreateActionParam(const POINT& viewClientPt, SActionParam& retParam);

private:
	bool		m_bInit;
	int			m_appSnapshot;
	Neo::D3D11RenderSystem*	m_pRenderSystem;
};

#endif // Application_h__


