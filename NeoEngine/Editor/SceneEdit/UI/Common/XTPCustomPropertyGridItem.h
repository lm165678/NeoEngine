/********************************************************************
	created:	8:1:2013   1:26
	filename: 	XTPCustomPropertyGridItem.h
	author:		maval
	
	purpose:	XTP���Կؼ���չ
				TODO:�ĳ�ģ����
*********************************************************************/
#ifndef XTPCustomPropertyGridItem_h__
#define XTPCustomPropertyGridItem_h__



//
//Vector3���Կؼ�
//
class CXTPPropertyGridItemVec3 : public CXTPPropertyGridItem
{
public:
	CXTPPropertyGridItemVec3(CString strCaption, const VEC3& value);

public:
	virtual void SetReadOnly(BOOL bReadOnly = TRUE);
	virtual void SetValue(CString strValue);

	void		SetChildItemID(int idX, int idY, int idZ);
	CString		GetStrX() const { return m_X->GetValue(); }
	CString		GetStrY() const { return m_Y->GetValue(); }
	CString		GetStrZ() const { return m_Z->GetValue(); }
	void		UpdateFromChild();

protected:
	virtual void OnAddChildItem();

private:
	CXTPPropertyGridItem* m_X;
	CXTPPropertyGridItem* m_Y;
	CXTPPropertyGridItem* m_Z;

	VEC3	m_value;
};

//
//Vector4���Կؼ�
//
class CXTPPropertyGridItemVec4 : public CXTPPropertyGridItem
{
public:
	CXTPPropertyGridItemVec4(CString strCaption, const VEC4& value);

public:
	virtual void SetReadOnly(BOOL bReadOnly = TRUE);
	virtual void SetValue(CString strValue);

	void		SetChildItemID(int idX, int idY, int idZ, int idW);
	CString		GetStrX() const { return m_X->GetValue(); }
	CString		GetStrY() const { return m_Y->GetValue(); }
	CString		GetStrZ() const { return m_Z->GetValue(); }
	CString		GetStrW() const { return m_W->GetValue(); }
	void		UpdateFromChild();

protected:
	virtual void OnAddChildItem();

private:
	CXTPPropertyGridItem* m_X;
	CXTPPropertyGridItem* m_Y;
	CXTPPropertyGridItem* m_Z;
	CXTPPropertyGridItem* m_W;

	VEC4	m_value;
};

//helper
VEC3		GetVec3Value(CXTPPropertyGridItemVec3* pItem, bool bReflect);
VEC4		GetVec4Value(CXTPPropertyGridItemVec4* pItem, bool bReflect);

#endif // XTPCustomPropertyGridItem_h__














