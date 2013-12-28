#include "stdafx.h"
#include "D3D11RenderTarget.h"
#include "D3D11RenderSystem.h"
#include "D3D11Texture.h"
#include "SceneManager.h"
#include "Camera.h"


namespace Neo
{
	RenderObject* D3D11RenderTarget::m_pQuadMesh = nullptr;
	//----------------------------------------------------------------------------------------
	D3D11RenderTarget::D3D11RenderTarget()
	:m_pRenderSystem(g_env.pRenderSystem)
	,m_pRenderTexture(nullptr)
	,m_clearColor(SColor::BLACK)
	,m_bClearColor(true)
	,m_bClearZBuffer(true)
	,m_bUpdateViewport(false)
	,m_bHasDepthBuffer(false)
	,m_phaseFlag(eRenderPhase_Geometry)
	,m_pDepthStencil(nullptr)
	,m_pDepthStencilView(nullptr)
	,m_oldViewportW(0)
	,m_oldViewportH(0)
	,m_sizeRatio(0, 0)
	{
		// Create screen quad
		static bool bCreate = false;
		if (!bCreate)
		{
			m_pQuadMesh = new RenderObject;

			SVertex v[4] = 
			{
				SVertex(VEC3(-1,1,0), VEC2(0,0)),
				SVertex(VEC3(1,1,0), VEC2(1,0)),
				SVertex(VEC3(-1,-1,0), VEC2(0,1)),
				SVertex(VEC3(1,-1,0), VEC2(1,1))
			};
			DWORD index[6] = { 0,1,2, 1,3,2 };

			// Store index to frustum far corner
			v[0].normal.x = 0;
			v[1].normal.x = 1;
			v[2].normal.x = 2;
			v[3].normal.x = 3;

			m_pQuadMesh->CreateVertexBuffer(v, ARRAYSIZE(v), true);
			m_pQuadMesh->CreateIndexBuffer(index, ARRAYSIZE(index), true);

			bCreate = true;
		}
	}
	//----------------------------------------------------------------------------------------
	D3D11RenderTarget::~D3D11RenderTarget()
	{
		Destroy();
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::Init( uint32 width, uint32 height, ePixelFormat format, bool bUpdateViewport /*= true*/, bool bOwnDepthBuffer /*= true*/ )
	{
		const uint32 screenW = m_pRenderSystem->GetWndWidth();
		const uint32 screenH = m_pRenderSystem->GetWndHeight();

		m_sizeRatio.Set(width / (float)screenW, height / (float)screenH);

		m_bUpdateViewport = bUpdateViewport;
		m_bHasDepthBuffer = bOwnDepthBuffer;

		// Create render texture
		m_pRenderTexture = new D3D11Texture(width, height, nullptr, format, eTextureUsage_RenderTarget, false);

		// Create depth stencil buffer
		if (m_bHasDepthBuffer)
			_CreateDepthBuffer(width, height);
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::Destroy()
	{
		SAFE_RELEASE(m_pDepthStencilView);
		SAFE_RELEASE(m_pDepthStencil);
		SAFE_RELEASE(m_pRenderTexture);
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::_CreateDepthBuffer( uint32 width, uint32 height )
	{
		D3D11_TEXTURE2D_DESC descTex;
		m_pRenderTexture->GetInternalTex()->GetDesc(&descTex);

		D3D11_TEXTURE2D_DESC descDepth;
		ZeroMemory( &descDepth, sizeof(descDepth) );

		descDepth.Width = width;
		descDepth.Height = height;
		descDepth.MipLevels				= 1;
		descDepth.ArraySize				= descTex.ArraySize;
		descDepth.Format				= DXGI_FORMAT_D32_FLOAT;
		descDepth.SampleDesc.Count		= descTex.SampleDesc.Count;
		descDepth.SampleDesc.Quality	= descTex.SampleDesc.Quality;
		descDepth.Usage					= D3D11_USAGE_DEFAULT;
		descDepth.BindFlags				= D3D11_BIND_DEPTH_STENCIL;
		descDepth.CPUAccessFlags		= 0;
		descDepth.MiscFlags				= 0;

		HRESULT hr = S_OK;
		V(m_pRenderSystem->GetDevice()->CreateTexture2D( &descDepth, NULL, &m_pDepthStencil ));

		// Create the depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory( &descDSV, sizeof(descDSV) );
		descDSV.Format = descDepth.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		V(m_pRenderSystem->GetDevice()->CreateDepthStencilView( m_pDepthStencil, &descDSV, &m_pDepthStencilView ));
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::_BeforeRender()
	{
		// Update aspect ratio and viewport
		if (m_bUpdateViewport)
		{
			m_oldViewportW = m_pRenderSystem->GetWndWidth();
			m_oldViewportH = m_pRenderSystem->GetWndHeight();

			m_pRenderSystem->OnViewportResize(m_pRenderTexture->GetWidth(), m_pRenderTexture->GetHeight());
		}

		m_pRenderSystem->SetRenderTarget(this, m_bClearColor, m_bClearZBuffer, &m_clearColor);
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::_AfterRender()
	{
		// Restore
		if (m_bUpdateViewport)
		{
			m_pRenderSystem->OnViewportResize(m_oldViewportW, m_oldViewportH);
		}

		m_pRenderSystem->SetRenderTarget(nullptr, false, false);
	}
	//----------------------------------------------------------------------------------------
	void D3D11RenderTarget::Update(Material* pMaterial)
	{
		_BeforeRender();

		g_env.pSceneMgr->RenderPipline(m_phaseFlag, pMaterial);

		_AfterRender();
	}
	//----------------------------------------------------------------------------------------
	D3D11Texture* D3D11RenderTarget::GetRenderTexture()
	{
		return m_pRenderTexture;
	}
	//----------------------------------------------------------------------------------------
	void D3D11RenderTarget::SetClearColor( const SColor& color )
	{
		m_clearColor = color;
	}
	//----------------------------------------------------------------------------------------
	void D3D11RenderTarget::SetClearEveryFrame( bool bColor, bool bZBuffer )
	{
		m_bClearColor = bColor;
		m_bClearZBuffer = bZBuffer;
	}
	//------------------------------------------------------------------------------------
	ID3D11DepthStencilView* D3D11RenderTarget::GetDSView()
	{
		return m_pDepthStencilView ? m_pDepthStencilView : m_pRenderSystem->GetDSView();
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::RenderScreenQuad( Material* pMaterial )
	{
		_BeforeRender();

		// Turn off z buffer
		D3D11_DEPTH_STENCIL_DESC& depthDesc = m_pRenderSystem->GetDepthStencilDesc();
		depthDesc.DepthEnable = FALSE;
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		m_pRenderSystem->SetDepthStencelState(depthDesc);

		m_pQuadMesh->Render(pMaterial);	

		_AfterRender();

		// Restore render state
		depthDesc.DepthEnable = TRUE;
		depthDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		m_pRenderSystem->SetDepthStencelState(depthDesc);
	}
	//------------------------------------------------------------------------------------
	void D3D11RenderTarget::OnWindowResized()
	{
		const uint32 screenW = m_pRenderSystem->GetWndWidth();
		const uint32 screenH = m_pRenderSystem->GetWndHeight();

		const uint32 newWidth = (uint32)(screenW * m_sizeRatio.x);
		const uint32 newHeight = (uint32)(screenH * m_sizeRatio.y);

		// Resize render texture
		m_pRenderTexture->Resize(newWidth, newHeight);

		// Resize depth stencil buffer
		if (m_bHasDepthBuffer)
		{
			SAFE_RELEASE(m_pDepthStencilView);
			SAFE_RELEASE(m_pDepthStencil);

			_CreateDepthBuffer(newWidth, newHeight);
		}
	}
}
