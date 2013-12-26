/********************************************************************
	created:	30:9:2013   21:16
	filename	MainFrm.h
	author:		maval

	purpose:	MFC main frame window
*********************************************************************/
#ifndef MainFrm_h__
#define MainFrm_h__


#include "Manipulator/ManipulatorEventCallback.h"

class CEditorView;
class CPropertiesPane;
class PropertyPaneTerrain;
class PropertyPaneObject;
class PropertyPaneEffect;
class PropertyPaneParticle;
class PropertyPaneDLight;
class PropertyPaneEntityEffect;
class DialogBehaviorTreeEditor;
class DialogGameDataBuilding;

//----------------------------------------------------------------------------------------
class CMainFrame 
	: public CXTPFrameWnd
	, public ManipulatorSceneEventCallback
	, public ManipulatorObjectEventCallback
{
	
public:
	CMainFrame();
	virtual ~CMainFrame();

public:
	virtual BOOL	PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL	OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	/////////////////////////////////////////////////////////
	///�¼��ص�
	virtual	void	OnSceneNew();
	virtual	void	OnSceneOpen();
	virtual void	OnSceneClose();

// 	virtual void	OnObjectSetSelection(Ogre::Entity* pObject);
// 	virtual void	OnObjectClearSelection(Ogre::Entity* pObject);
// 	virtual void	OnObjectPropertyChanged(Ogre::Entity*);
	
#ifdef _DEBUG
	virtual void	AssertValid() const;
	virtual void	Dump(CDumpContext& dc) const;
#endif

	//��ʼ���༭������
	bool			CreateEditorMainUI();
	//ˢ��Ribbon���
	void			RefreshRibbonBar();

protected:
	DECLARE_DYNAMIC(CMainFrame)
	virtual BOOL	OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	afx_msg int		OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl);

private:
	DECLARE_MESSAGE_MAP()
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSetFocus(CWnd *pOldWnd);
	afx_msg void	OnClose();
	afx_msg void	OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnResPanelNotify(WPARAM wParam, LPARAM lParam);

	void			_LoadIcon();
	bool			_OnCreateRibbon();
	void			_CreateLayerTexIcon();
	void			_CreateDockPane();
	LRESULT			_AttachDockPane(WPARAM wParam, LPARAM lParam);
	CPropertiesPane*	_GetCurAttachmentPane();
	void			_OnAttachmentPaneChange(BOOL bEnable, BOOL bRefresh);
	//����mesh��Դѡ�����
	bool			_CreateMeshPanel(CImageList& imageList, StringVector& meshNames);

	///Terrain
	void			OnUpdateUI_TerrainBrushSize1(CCmdUI* pCmdUI);
	void			OnUpdateUI_TerrainBrushSize2(CCmdUI* pCmdUI);
	void			OnTerrainBrushSize1(NMHDR* pNMHDR, LRESULT* pResult);
	void			OnTerrainBrushSize1Spin(NMHDR* pNMHDR, LRESULT* pResult);
	void			OnTerrainBrushSize2(NMHDR* pNMHDR, LRESULT* pResult);
	void			OnTerrainBrushSize2Spin(NMHDR* pNMHDR, LRESULT* pResult);
	//deform
	void			OnUpdateUI_BtnTerrainDeform(CCmdUI* pCmdUI);
	void			OnBtnTerrainDeform();
	//splat
	void			OnUpdateUI_BtnTerrainSplat(CCmdUI* pCmdUI);
	void			OnBtnTerrainSplat();
	//LayerTexture
	void			OnUpdateUI_GalleryLayerTex(CCmdUI* pCmdUI);
	void			OnSelectLayerTex(NMHDR* pNMHDR, LRESULT* pResult);
	void			OnUpdateUI_SplatSelectLayer(CCmdUI* pCmdUI);
	void			OnSplatSelectLayer(UINT nID);
	//vegetation
	void			OnUpdateUI_BtnVegetationGrass(CCmdUI* pCmdUI);
	void			OnBtnVegetationGrass();		

	///Object
	template<int mode> void OnObjectEdit();
	template<int mode> void	OnUpdateUI_ObjectEdit(CCmdUI* pCmdUI);
	void			OnUpdateUI_ObjectRemove(CCmdUI* pCmdUI);
	void			OnObjectRemove();
	///Animation
	void			OnUpdateUI_AnimNames(CCmdUI* pCmdUI);
	void			OnAnimSelectChange(NMHDR* pNMHDR, LRESULT* pResult);
	void			OnUpdateUI_AnimPlay(CCmdUI* pCmdUI);
	void			OnUpdateUI_AnimStop(CCmdUI* pCmdUI);
	void			OnAnimPlay();
	void			OnAnimStop();
	void			OnUpdateUI_AttachEffectAdd(CCmdUI* pCmdUI);
	void			OnUpdateUI_AttachEffectRemove(CCmdUI* pCmdUI);
	void			OnAttachEffectAdd(UINT nID);
	void			OnAttachEffectRemove();
	void			OnUpdateUI_AttachEffectList(CCmdUI* pCmdUI);
	void			OnAttachEffectSelectChange(NMHDR* pNMHDR, LRESULT* pResult);

	///Effect
	void			OnUpdateUI_ShadowOnOff(CCmdUI* pCmdUI);
	void			OnUpdateUI_SSAOOnOff(CCmdUI* pCmdUI);
	void			OnUpdateUI_SharpenOnOff(CCmdUI* pCmdUI);
	void			OnUpdateUI_FXAAOnOff(CCmdUI* pCmdUI);
	void			OnShadowOnOff();
	void			OnSSAOOnOff();
	void			OnSharpenOnOff();
	void			OnFXAAOnOff();

private:
	CXTPDockingPaneManager	m_paneManager;
	CEditorView*			m_wndView;
	CXTPTaskPanel			m_resourceSelector;		//meshѡ��ؼ�
	PropertyPaneTerrain*	m_propertyTerrain;		//��������
	CXTPControlGalleryItems* m_terrainTexGallery;	//���������ؼ�
	PropertyPaneObject*		m_propertyObject;		//��������
	PropertyPaneEffect*		m_propertyEffect;		//��Ч����
	PropertyPaneParticle*	m_propertyParticle;		//�ҽ���������
	PropertyPaneDLight*		m_propertyDLight;		//�ҽ��ӳٹ�����
	PropertyPaneEntityEffect* m_propertyEntityEffct; //�ҽ�ģ������

	CXTPRibbonTab*			m_animTab;
	CXTPControlComboBox*	m_animList;
	CXTPControlComboBox*	m_effectList;

	CXTPDockingPane*		m_paneResSelector;		
	CXTPDockingPane*		m_paneTerrain;
	CXTPDockingPane*		m_paneObject;
	CXTPDockingPane*		m_paneEffect;
	CXTPDockingPane*		m_paneAttachment;

	typedef std::unordered_map<int, bool> DialogVisibleFlags;
	DialogVisibleFlags		m_dlgVisibleFlags;
};

#endif // MainFrm_h__
