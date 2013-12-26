/********************************************************************
	created:	11:3:2013   1:52
	filename: 	AttachmentPropertyPane.h
	author:		maval
	
	purpose:	ģ��attachment���Ի���
				attachment����ӦM3ģ����max�е�attachment�ڵ�
*********************************************************************/

#ifndef AttachmentPropertyPane_h__
#define AttachmentPropertyPane_h__

#include "PropertiesPane.h"

class PropertyPaneAttachment : public CPropertiesPane
{
public:
	enum ePropertyID
	{
		////property range [propStart, propEnd)
		propStart = 0,
		////////These are Mutable items					
		propMutableItemStart = propStart,
		propLocator = propMutableItemStart,				//�ҽӵ�				
		propStartTime,									//��Ч��Զ�����ʼ��ʱ��
		propLifeTime,									//��Чʱ��
		propMutableItemEnd,
		propEnd = propMutableItemEnd,
	};

public:
	PropertyPaneAttachment():CPropertiesPane() {}
	~PropertyPaneAttachment() = 0;

protected:
	virtual	bool	_OnCreate();
	virtual	void	_SetProperty(int nID);
	virtual	void	_UpdateProperty(int nID);

	virtual int		_GetIDStart()			{ return propStart;				}
	virtual int		_GetIDEnd()				{ return propEnd;				}
	virtual int		_GetIDMutableStart()	{ return propMutableItemStart;	}
	virtual int		_GetIDMutableEnd()		{ return propMutableItemEnd;	}
};


#endif // AttachmentPropertyPane_h__














