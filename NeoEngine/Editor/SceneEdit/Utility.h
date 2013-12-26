/********************************************************************
	created:	9:1:2013   1:49
	filename: 	Utility.h
	author:		maval
	
	purpose:	�����Ӱ�
*********************************************************************/

#ifndef Utility_h__
#define Utility_h__



#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(a) { if(p) { delete []p; p=NULL; } }
#endif

namespace Utility
{
	std::wstring	EngineToUnicode(const char* src);
	std::wstring	EngineToUnicode(const STRING& src);
	STRING			UnicodeToEngine(const WCHAR* src);
	STRING			UnicodeToEngine(const std::wstring& src);

	//��ȡ��С�������λ
	std::wstring	FloatToString_CutPrecision(float f);
	std::wstring	StringCutPrecision(const CString& strFloat);

	//��ȡGUID
	int				GenGUID();

	//��ȡ��ֵ������
	template<typename T>
	T GetSign(T val)
	{
		if (val == 0)
		{
			return 0;
		}
		return val > 0 ? 1 : -1;
	}

	class WorkingDirectory
	{
	public:
		WorkingDirectory(const WCHAR* szNewDir)
		{
			::GetCurrentDirectoryW(MAX_PATH, m_oldDir);
			::SetCurrentDirectoryW(szNewDir);

		}
		WorkingDirectory()
		{
			::GetCurrentDirectoryW(MAX_PATH, m_oldDir);
		}
		~WorkingDirectory()
		{
			::SetCurrentDirectoryW(m_oldDir);
		}
	private:
		WCHAR	m_oldDir[MAX_PATH];
	};
}

//�����ڶ���
template<bool> struct Static_Assert;
template<> struct Static_Assert<true> {};

//ע��proerty
#define PROPERTY_REG(category, type, name, value, id)	\
{	\
	CXTPPropertyGridItem* pItem = category->AddChildItem(new CXTPPropertyGridItem##type(name, value));	\
	pItem->SetID(id);								\
	pItem->SetReadOnly(TRUE);						\
	m_mapItem.insert(std::make_pair(id, pItem));	\
}


#endif // Utility_h__



