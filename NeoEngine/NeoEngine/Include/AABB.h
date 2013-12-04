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

		void	SetNull()
		{
			m_minCorner.Set(10000,10000,10000);
			m_maxCorner.Set(-10000,-10000,-10000);
			m_boundingRadius = -1;
		}

		VEC3	GetCenter() const
		{ 
			VEC3 ret = Common::Add_Vec3_By_Vec3(m_minCorner, m_maxCorner);
			ret = Common::Multiply_Vec3_By_K(ret, 0.5f);
			
			return std::move(ret);
		}

		void	Merge(const VEC4& pt);
		//�任AABB,from ogre. NB: �任����Ҫ���������
		void	Transform(const MAT44& matrix);

		VEC3	m_minCorner, m_maxCorner;
		float	m_boundingRadius;		//�������
	};	
}

#endif // AABB_h__