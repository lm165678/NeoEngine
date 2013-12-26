
// SceneEdit.h : SceneEdit Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Application.h"


// CSceneEditApp:
// �йش����ʵ�֣������ SceneEdit.cpp
//

class CSceneEditApp : public CWinApp
{
public:
	CSceneEditApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

private:
	DECLARE_MESSAGE_MAP()
	afx_msg void	OnAppAbout();
	afx_msg void	OnFileNew();
	afx_msg void	OnFileOpen();
	afx_msg void	OnFileSave();
	afx_msg void	OnFileClose();

public:
	Application		m_app;
};

extern CSceneEditApp theApp;
