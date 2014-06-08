/********************************************************************
	created:	2013/07/23
	created:	23:7:2013   10:23
	filename: 	Prerequiestity.h
	author:		maval
	
	purpose:	��Ŀǰ���ļ�
*********************************************************************/
#ifndef Prerequiestity_h__
#define Prerequiestity_h__

#include "Common.h"


const int	MAX_TEXTURE_STAGE	=	8;


#define USE_SIMD				0			//�Ƿ�ʹ��SIMD


enum eTextureType
{
	eTextureType_2D,
	eTextureType_3D,
	eTextureType_CubeMap,
	eTextureType_TextureArray
};

enum eTextureUsage
{
	eTextureUsage_WriteOnly		= 1 << 0,
	eTextureUsage_ReadWrite		= 1 << 1,		// Staging
	eTextureUsage_RenderTarget	= 1 << 2,
	eTextureUsage_DomainShader	= 1 << 3,		// Bind to domain shader
	eTextureUsage_HullShader	= 1 << 4,		// Bind to hull shader
	eTextureUsage_RecreateOnWndResized = 1 << 5,
	eTextureUsage_Depth			= 1 << 6
};

enum eEntity
{
	eEntity_StaticModel,
	eEntity_Tree
};

enum eVertexType
{
	eVertexType_General,		// SVertex
	eVertexType_TreeLeaf		// Svertex_TreeLeaf
};

// Use for render target to control which part to render
enum eRenderPhase
{
	eRenderPhase_Sky		= 1 << 0,
	eRenderPhase_Terrain	= 1 << 1,
	eRenderPhase_SSAO		= 1 << 2,
	eRenderPhase_Solid		= 1 << 3,
	eRenderPhase_Water		= 1 << 4,
	eRenderPhase_UI			= 1 << 5,
	eRenderPhase_ShadowMap	= 1 << 6,

	eRenderPhase_Geometry	= eRenderPhase_Sky | eRenderPhase_Terrain | eRenderPhase_Solid | eRenderPhase_Water,

	eRenderPhase_All = eRenderPhase_Geometry | eRenderPhase_UI | eRenderPhase_SSAO
};

enum eRenderQueue
{
	eRenderQueue_Entity		=	0,
	eRenderQueue_UI,
	eRenderQueue_Count
};

enum eShaderFlag
{
	eShaderFlag_EnableClipPlane			= 1<<0,		// Clip plane support for water reflection
	eShaderFlag_EnableSSAO				= 1<<1,
	eShaderFlag_EnableShadowReceive		= 1<<2,
};

enum ePixelFormat
{
	ePF_R8G8B8 = 0,
	ePF_A8R8G8B8,
	ePF_A8B8G8R8,
	ePF_R16F,
	ePF_G16R16F,
	ePF_A16B16G16R16F,
	ePF_R32F,
	ePF_G32R32F,
	ePF_A32B32G32R32F,
	ePF_L8,
	ePF_L16,
	ePF_DXT1,
	ePF_DXT2,
	ePF_DXT3,
	ePF_DXT4,
	ePF_DXT5,
	ePF_Unknown
};

enum eTransform
{
	eTransform_World,
	eTransform_View,
	eTransform_Proj,
	eTransform_WVP,
	eTransform_WorldIT,
	eTransform_Shadow,		// World space -> sun light NDC space -> texture space
	eTransform_Count
};

enum eDebugRT
{
	eDebugRT_None,
	eDebugRT_SSAO,
	eDebugRT_ShadowMap
};

/// Forward declaration
namespace Common
{
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix44;
	class Plane;
	class AxisAlignBBox;
	class iPoint;
	class Quaternion;
}

typedef std::string			STRING;
typedef std::vector<STRING>	StringVector;
typedef unsigned int		uint32;
typedef unsigned short		uint16;
typedef unsigned char		uint8;
typedef Common::Vector2			VEC2;
typedef Common::Vector3			VEC3;
typedef Common::Vector4			VEC4;
typedef Common::Matrix44		MAT44;
typedef Common::AxisAlignBBox	AABB;
typedef Common::Plane			PLANE;
typedef Common::iPoint			IPOINT;
typedef Common::Quaternion		QUATERNION;

namespace Neo
{
	class	Camera;
	class	D3D11RenderSystem;
	class	PixelBox;
	struct	SColor;
	struct	SVertex;
	struct	STreeLeafVertex;
	struct	SFrameStat;
	struct	SDirectionLight;
	class	VertexData;
	class	Material;
	class	D3D11Texture;
	class	D3D11RenderTarget;
	class	Terrain;
	class	Water;
	class	Sky;
	class	Scene;
	class	SceneManager;
	class	Font;
	class	MeshLoader;
	class	SSAO;
	class	ShadowMap;
	class	Tree;
	class	Entity;
	class	SubMesh;
	class	Mesh;
}



struct SGlobalEnv 
{
	HWND					hwnd;			// Main window handle
	Neo::D3D11RenderSystem*	pRenderSystem;	// Render system
	Neo::SceneManager*		pSceneMgr;		// Scene manager
	Neo::SFrameStat*		pFrameStat;		// Frame statics info
};
extern SGlobalEnv	g_env;


#endif // Prerequiestity_h__