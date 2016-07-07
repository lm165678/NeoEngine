/********************************************************************
	created:	21:7:2013   17:54
	filename	ObjMeshLoader.h
	author:		maval

	purpose:	.obj .mtl ������.
				ܳ,obj��ʽ̫������,�������ĸо�
				TODO:��̨�������س���
*********************************************************************/

#ifndef ObjMeshLoader_h__
#define ObjMeshLoader_h__

#include "Prerequiestity.h"

namespace Neo
{
	class ObjMeshLoader
	{
	public:
		struct SVertCompare 
		{
			bool operator== (const SVertCompare& rhs) { return memcmp(this, &rhs, sizeof(SVertCompare)) == 0; }

			int idxPos, idxUv, idxNormal;
		};

		static Mesh*	LoadMesh(const STRING& filename, bool bFlipYZ, bool bNormalMap);
		static bool		LoadMtlFile(const STRING& filename);

	private:
		static void	_PreReadObject(std::ifstream& file, DWORD& nVert, DWORD& nUv, DWORD& nNormal, DWORD& nFace);
		static bool	_DefineVertex(const SVertCompare& comp, DWORD& retIdx);

		static std::vector<SVertCompare>	m_vecComp;
	};
}

#endif // ObjMeshLoader_h__
