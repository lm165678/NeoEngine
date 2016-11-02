/********************************************************************
	created:	2:7:2013   20:13
	filename	PixelBox.h
	author:		maval

	purpose:	PixelBox�ǰ���һ�����ݿ�����ݽṹ
*********************************************************************/
#ifndef PixelBox_h__
#define PixelBox_h__

#include "Prerequiestity.h"
#include "Color.h"

namespace Neo
{
	class PixelBox
	{
	public:
		PixelBox(int width, int height, int bytesPerPixel, void* pData = nullptr, bool bOwnData = true);
		PixelBox(BITMAP* bm, bool bCopyData);
		~PixelBox();

	public:
		void*	GetDataPointer() const	{ return (void*)m_data; }
		int		GetWidth() const	{ return m_width; }
		int		GetHeight() const	{ return m_height; }
		int		GetPitch() const	{ return m_pitch; }
		int		GetBitsPerPixel() const	{ return m_bytesPerPixel * 8; }
		int		GetBytesPerPixel() const	{ return m_bytesPerPixel; }
		void	SetPixelAt(int x, int y, SColor p);
		SColor	GetPixelAt(int x, int y) const;

	private:
		char*		m_data;
		bool		m_ownData;			//�����Ƿ����Լ������.������Ҫ�Լ�����,������
		int			m_width;
		int			m_height;
		int			m_pitch;
		int			m_bytesPerPixel;
	};
}


#endif // PixelBox_h__