/********************************************************************
	created:	2013/07/23
	created:	23:7:2013   9:21
	filename: 	AABB.h
	author:		maval
	
	purpose:	������Χ��
*********************************************************************/
#ifndef AABB_h__
#define AABB_h__

#include "Prerequiestity.h"
#include "MathDef.h"

namespace Common
{
	class AxisAlignBBox
	{
	public:
		AxisAlignBBox();

		void	SetNull();
		VEC3	GetCenter() const;
		void	Merge(const VEC3& pt);
		void	Merge(const AABB& aabb);
		VEC3	GetSize() const;
		bool	IsFinite() const { return m_boundingRadius != -1; }
		//�任AABB,from ogre. NB: �任����Ҫ���������
		void	Transform(const MAT44& matrix);

		VEC3	m_minCorner, m_maxCorner;
		float	m_boundingRadius;		//�������
	};	
}

#endif // AABB_h__