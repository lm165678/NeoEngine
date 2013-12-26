/********************************************************************
	created:	28:1:2013   0:19
	filename: 	ManipulatorEditorResource.h
	author:		maval
	
	purpose:	�༭�������Դ����
*********************************************************************/
#ifndef ManipulatorEditorResource_h__
#define ManipulatorEditorResource_h__



class ManipulatorResource
{
	typedef std::unordered_map<std::wstring, Gdiplus::Bitmap*> IconContainer;

public:
	ManipulatorResource() {}
	~ManipulatorResource();

public:
	//RTT��Ⱦ����mesh��ͼ��,����Icon�б��mesh�����б�
	void	RenderAllMeshIcons(CImageList& retImageList, StringVector& retMeshNames);
	//׼���ø�����ͼ�������
	void	PrepareAllIcons();
	//ȡ��ָ�����͵�ͼ������
	Gdiplus::Bitmap*	GetIcon(const std::wstring& iconName) const;

private:
	IconContainer	m_icons;
};


#endif // ManipulatorEditorResource_h__







