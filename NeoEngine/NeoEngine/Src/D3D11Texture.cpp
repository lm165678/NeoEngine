#include "stdafx.h"
#include "D3D11Texture.h"
#include "D3D11RenderSystem.h"

namespace Neo
{
	//--------------------------------------------------------------------------
	D3D11Texture::D3D11Texture(const STRING& filename, eTextureType type, uint32 usage)
	:m_pTexture2D(nullptr)
	,m_pTexture3D(nullptr)
	,m_pRenderSystem(g_env.pRenderSystem)
	,m_rtView(nullptr)
	,m_pSRV(nullptr)
	,m_usage(usage)
	,m_texType(type)
	,m_width(0)
	,m_height(0)
	,m_bMipMap(true)
	{
		m_pd3dDevice = m_pRenderSystem->GetDevice();
		if (m_pd3dDevice)
			m_pd3dDevice->AddRef();

		////////////////////////////////////////////////////////////////
		////////////// Load texture
		HRESULT hr = S_OK;
		D3DX11_IMAGE_LOAD_INFO loadInfo;
		loadInfo.MipLevels = 0;
		ID3D11Resource** pTex = nullptr;

		switch (GetTextureType())
		{
		case eTextureType_2D:
			{
				pTex = (ID3D11Resource**)&m_pTexture2D;
			}
			break;

		case eTextureType_CubeMap:
			{
				loadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
				pTex = (ID3D11Resource**)&m_pTexture2D;
			}
			break;

		case eTextureType_3D:
			{
				pTex = (ID3D11Resource**)&m_pTexture3D;
			}
			break;

		default: assert(0);
		}

		V(D3DX11CreateTextureFromFileA(m_pd3dDevice, filename.c_str(), &loadInfo, nullptr,pTex, nullptr));

		// Create SRV
		CreateSRV();

		// Get texture dimension
		switch (GetTextureType())
		{
		case eTextureType_2D:
		case eTextureType_CubeMap:
			{
				D3D11_TEXTURE2D_DESC desc;
				m_pTexture2D->GetDesc(&desc);

				m_width = desc.Width;
				m_height = desc.Height;
			}
			break;

		case eTextureType_3D:
			{
				D3D11_TEXTURE3D_DESC desc;
				m_pTexture3D->GetDesc(&desc);

				m_width = desc.Width;
				m_height = desc.Height;
			}
			break;

		default: assert(0);
		}
	}
	//-------------------------------------------------------------------------------
	D3D11Texture::D3D11Texture( uint32 width, uint32 height, const char* pTexData, ePixelFormat format, uint32 usage, bool bMipMap )
	:m_pTexture2D(nullptr)
	,m_pTexture3D(nullptr)
	,m_pRenderSystem(g_env.pRenderSystem)
	,m_rtView(nullptr)
	,m_pSRV(nullptr)
	,m_width(width)
	,m_height(height)
	,m_usage(usage)
	,m_texType(eTextureType_2D)
	,m_bMipMap(bMipMap)
	,m_texFormat(format)
	{
		m_pd3dDevice = m_pRenderSystem->GetDevice();
		if (m_pd3dDevice)
			m_pd3dDevice->AddRef();

		_CreateManual(pTexData);
	}
	//------------------------------------------------------------------------------------
	D3D11Texture::D3D11Texture( const StringVector& vecTexNames )
	:m_pTexture2D(nullptr)
	,m_pTexture3D(nullptr)
	,m_pRenderSystem(g_env.pRenderSystem)
	,m_rtView(nullptr)
	,m_pSRV(nullptr)
	,m_usage(0)
	,m_texType(eTextureType_TextureArray)
	,m_bMipMap(true)
	{
		m_pd3dDevice = m_pRenderSystem->GetDevice();
		if (m_pd3dDevice)
			m_pd3dDevice->AddRef();

		assert(!vecTexNames.empty());

		HRESULT hr = S_OK;
		// First load all texture elements
		std::vector<ID3D11Texture2D*> vecTexs(vecTexNames.size());
		for (size_t i=0; i<vecTexNames.size(); ++i)
		{
			D3DX11_IMAGE_LOAD_INFO loadInfo;
			loadInfo.Width  = D3DX11_FROM_FILE;
			loadInfo.Height = D3DX11_FROM_FILE;
			loadInfo.Depth  = D3DX11_FROM_FILE;
			loadInfo.FirstMipLevel = 0;
			loadInfo.BindFlags = 0;
			loadInfo.Usage = D3D11_USAGE_STAGING;	// Local res
			loadInfo.MipLevels = D3DX11_FROM_FILE;
			loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			loadInfo.MiscFlags = 0;
			loadInfo.Format = DXGI_FORMAT_FROM_FILE;
			loadInfo.Filter = D3DX11_FILTER_NONE;
			loadInfo.MipFilter = D3DX11_FILTER_LINEAR;
			loadInfo.pSrcInfo  = 0;

			V(D3DX11CreateTextureFromFileA(m_pRenderSystem->GetDevice(), vecTexNames[i].c_str(), 
				&loadInfo, nullptr, (ID3D11Resource**)&vecTexs[i], nullptr));
		}

		// Then create the texture array object
		D3D11_TEXTURE2D_DESC texElementDesc;
		vecTexs[0]->GetDesc(&texElementDesc);

		m_width = texElementDesc.Width;
		m_height = texElementDesc.Height;

		D3D11_TEXTURE2D_DESC texArrayDesc;
		texArrayDesc.Width              = texElementDesc.Width;
		texArrayDesc.Height             = texElementDesc.Height;
		texArrayDesc.MipLevels          = texElementDesc.MipLevels;
		texArrayDesc.ArraySize          = vecTexs.size();
		texArrayDesc.Format             = texElementDesc.Format;
		texArrayDesc.SampleDesc.Count   = 1;
		texArrayDesc.SampleDesc.Quality = 0;
		texArrayDesc.Usage              = D3D11_USAGE_DEFAULT;
		texArrayDesc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		texArrayDesc.CPUAccessFlags     = 0;
		texArrayDesc.MiscFlags          = 0;

		V(m_pRenderSystem->GetDevice()->CreateTexture2D( &texArrayDesc, 0, &m_pTexture2D));

		// Fill texture array data
		ID3D11DeviceContext* dc = m_pRenderSystem->GetDeviceContext();

		for(size_t texElement=0; texElement<vecTexs.size(); ++texElement)
		{
			for(UINT mipLevel = 0; mipLevel < texElementDesc.MipLevels; ++mipLevel)
			{
				D3D11_MAPPED_SUBRESOURCE mappedTex2D;
				V(dc->Map(vecTexs[texElement], mipLevel, D3D11_MAP_READ, 0, &mappedTex2D));

				dc->UpdateSubresource(m_pTexture2D, 
					D3D11CalcSubresource(mipLevel, texElement, texElementDesc.MipLevels),
					0, mappedTex2D.pData, mappedTex2D.RowPitch, mappedTex2D.DepthPitch);

				dc->Unmap(vecTexs[texElement], mipLevel);
			}
		}

		CreateSRV();

		for(size_t i=0; i<vecTexs.size(); ++i)
			vecTexs[i]->Release();
	}
	//-------------------------------------------------------------------------------
	D3D11Texture::~D3D11Texture()
	{
		Destroy();
		SAFE_RELEASE(m_pd3dDevice);
	}
	//-----------------------------------------------------------------------------------
	void D3D11Texture::Destroy()
	{
		SAFE_RELEASE(m_pTexture2D);
		SAFE_RELEASE(m_pTexture3D);
		SAFE_RELEASE(m_pSRV);
		SAFE_RELEASE(m_rtView);
	}
	//------------------------------------------------------------------------------------
	void D3D11Texture::_CreateManual(const char* pTexData)
	{
		DXGI_FORMAT dxformat = DXGI_FORMAT_UNKNOWN;
		DWORD bytesPerPixel = 0;

		switch(m_texFormat)
		{
		case ePF_A8R8G8B8:
			dxformat = DXGI_FORMAT_B8G8R8A8_UNORM;
			bytesPerPixel = 4;
			break;
		case ePF_A8B8G8R8:
			dxformat = DXGI_FORMAT_R8G8B8A8_UNORM;
			bytesPerPixel = 4;
			break;
		case ePF_L16:
			dxformat = DXGI_FORMAT_R16_UNORM; 
			bytesPerPixel = 2;
			break;
		case ePF_R8G8B8:
			dxformat = DXGI_FORMAT_B8G8R8A8_UNORM;
			bytesPerPixel = 4;
			break;
		case ePF_A16B16G16R16F:
			dxformat = DXGI_FORMAT_R16G16B16A16_FLOAT;
			bytesPerPixel = 8;
			break;
		case ePF_L8:
			dxformat = DXGI_FORMAT_R8_UNORM;
			bytesPerPixel = 1;
			break;
		case ePF_R16F:
			dxformat = DXGI_FORMAT_R16_FLOAT;
			bytesPerPixel = 2;
			break;
		case ePF_R32F:
			dxformat = DXGI_FORMAT_R32_FLOAT;
			bytesPerPixel = 4;
			break;

		case ePF_DXT1: dxformat = DXGI_FORMAT_BC1_UNORM; bytesPerPixel = 4; break;
		case ePF_DXT2: dxformat = DXGI_FORMAT_BC2_UNORM; bytesPerPixel = 4; break;
		case ePF_DXT3: dxformat = DXGI_FORMAT_BC3_UNORM; bytesPerPixel = 4; break;
		case ePF_DXT4: dxformat = DXGI_FORMAT_BC4_UNORM; bytesPerPixel = 4; break;
		case ePF_DXT5: dxformat = DXGI_FORMAT_BC5_UNORM; bytesPerPixel = 4; break;

		default:
			assert(true);	// Not support yet...
			break;
		}

		DWORD pitch = bytesPerPixel * m_width;
		char* tmpBuf = (char*)pTexData;

		if(!pTexData)
			tmpBuf = new char[pitch * m_height];

		D3D11_SUBRESOURCE_DATA subData;
		D3D11_SUBRESOURCE_DATA* subDataArray = nullptr;
		subData.pSysMem = tmpBuf;
		subData.SysMemPitch = pitch;

		CD3D11_TEXTURE2D_DESC desc(dxformat, m_width, m_height);

		if (m_bMipMap)
		{
			int wid = m_width, hei = m_height;
			// Get mipmap level
			desc.MipLevels = 1;
			while((wid > 1) || (hei > 1))
			{
				wid = max(wid / 2, 1);
				hei = max(hei / 2, 1);
				++desc.MipLevels;
			}

			// Not correct mipmap data, just make room for later D3DX11FilterTexture
			subDataArray = new D3D11_SUBRESOURCE_DATA[desc.MipLevels];
			for (size_t i=0; i<desc.MipLevels; ++i)
			{
				subDataArray[i].pSysMem = tmpBuf;
				subDataArray[i].SysMemPitch = pitch;
			}
		}
		else
		{
			desc.MipLevels = 1;
			subDataArray = &subData;
		}

		// Validate usage
		assert(!((m_usage&eTextureUsage_WriteOnly)&&(m_usage&eTextureUsage_ReadWrite)) && "Invalid usage!");

		// Assign usage
		if (m_usage & eTextureUsage_WriteOnly)
		{
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			desc.Usage = D3D11_USAGE_DYNAMIC;
		}
		else if (m_usage & eTextureUsage_ReadWrite)
		{
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			desc.Usage = D3D11_USAGE_STAGING;
			desc.BindFlags = 0;
		}

		if (m_usage & eTextureUsage_RenderTarget)
		{
			desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		}

		if (GetTextureType() == eTextureType_CubeMap)
		{
			desc.MiscFlags |= D3D11_RESOURCE_MISC_TEXTURECUBE;
			desc.ArraySize = 6;
		}

		HRESULT hr = m_pd3dDevice->CreateTexture2D(&desc, subDataArray, &m_pTexture2D);

		if(!pTexData)
		{
			SAFE_DELETE_ARRAY(tmpBuf);
		}

		assert(SUCCEEDED(hr) && "Create texture failed!");

		// Generate mipmap levels
		if (m_bMipMap)
		{
			V(D3DX11FilterTexture(m_pRenderSystem->GetDeviceContext(), m_pTexture2D, 0, D3DX11_DEFAULT));
		}

		// Create SRV
		CreateSRV();

		// Bind RT view
		if (m_usage & eTextureUsage_RenderTarget)
		{
			V(m_pd3dDevice->CreateRenderTargetView( m_pTexture2D, NULL, &m_rtView ));
		}
	}
	//-------------------------------------------------------------------------------
	bool D3D11Texture::SaveToFile( const char* filename )
	{
		STRING str(filename);
		assert(str.substr(str.length()-4, 4) == ".dds");

		ID3D11DeviceContext* context = m_pRenderSystem->GetDeviceContext();
		HRESULT hr = D3DX11SaveTextureToFileA(context, m_pTexture2D, D3DX11_IFF_DDS, filename);

		return SUCCEEDED(hr);
	}
	//-------------------------------------------------------------------------------
	void D3D11Texture::CreateSRV()
	{
		// Local texture not create SRV
		if (m_usage & eTextureUsage_ReadWrite)
			return;

		SAFE_RELEASE(m_pSRV);

		ID3D11Resource** pTex = nullptr;
		D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;

		switch (GetTextureType())
		{
		case eTextureType_2D:
			{
				D3D11_TEXTURE2D_DESC SMTextureDesc;
				m_pTexture2D->GetDesc(&SMTextureDesc);

				SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
				SMViewDesc.Texture2D.MipLevels = SMTextureDesc.MipLevels;
				SMViewDesc.Texture2D.MostDetailedMip = 0;
				SMViewDesc.Format = SMTextureDesc.Format;

				pTex = (ID3D11Resource**)&m_pTexture2D;
			}
			break;

		case eTextureType_TextureArray:
			{
				D3D11_TEXTURE2D_DESC SMTextureDesc;
				m_pTexture2D->GetDesc(&SMTextureDesc);

				SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
				SMViewDesc.Texture2DArray.MipLevels = SMTextureDesc.MipLevels;
				SMViewDesc.Texture2DArray.MostDetailedMip = 0;
				SMViewDesc.Texture2DArray.FirstArraySlice = 0;
				SMViewDesc.Texture2DArray.ArraySize = SMTextureDesc.ArraySize;
				SMViewDesc.Format = SMTextureDesc.Format;

				pTex = (ID3D11Resource**)&m_pTexture2D;
			}
			break;

		case eTextureType_CubeMap:
			{
				D3D11_TEXTURE2D_DESC SMTextureDesc;
				m_pTexture2D->GetDesc(&SMTextureDesc);

				SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
				SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
				SMViewDesc.TextureCube.MostDetailedMip = 0;
				SMViewDesc.Format = SMTextureDesc.Format;

				pTex = (ID3D11Resource**)&m_pTexture2D;
			}
			break;

		case eTextureType_3D:
			{
				D3D11_TEXTURE3D_DESC SMTextureDesc;
				m_pTexture3D->GetDesc(&SMTextureDesc);

				SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
				SMViewDesc.Texture3D.MipLevels = SMTextureDesc.MipLevels;
				SMViewDesc.Texture3D.MostDetailedMip = 0;
				SMViewDesc.Format = SMTextureDesc.Format;

				pTex = (ID3D11Resource**)&m_pTexture3D;
			}
			break;

		default: assert(0);
		}

		HRESULT hr = S_OK;
		V(m_pd3dDevice->CreateShaderResourceView(*pTex, &SMViewDesc, &m_pSRV));
	}
	//------------------------------------------------------------------------------------
	void D3D11Texture::Resize( uint32 width, uint32 height )
	{
		assert(m_usage & eTextureUsage_RenderTarget);

		Destroy();

		m_width = width;
		m_height = height;

		_CreateManual(nullptr);
	}
}
