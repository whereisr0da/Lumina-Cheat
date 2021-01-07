#ifndef texture_h

#define texture_h

// from : https://www.unknowncheats.me/wiki/Team_Fortress_2:Embedding_and_rendering_custom_textures

#include "../common/includes.h"
#include "../sdk/interfaces.h"

class texture
{
public:
	typedef std::shared_ptr<texture> Ptr;
	texture()
		: m_pSurface(interfaces::surface), m_iH(0), m_iW(0), m_bgColor(255, 255, 255, 255), m_bValid(false)
	{ };

	texture(const unsigned char* pRawRGBAData, uint32 W, uint32 H)
		: m_pSurface(interfaces::surface), m_iH(H), m_iW(W), m_bgColor(255, 255, 255, 255), m_bValid(false)
	{
		m_iTexture = m_pSurface->CreateNewTextureID(true);
		if (!m_iTexture)
			return;
		m_pSurface->DrawSetTextureRGBA(m_iTexture, pRawRGBAData, W, H);
		m_bValid = true;
	};

	bool IsValid() const
	{
		return m_bValid;
	};

	int GetTextureId() const
	{
		return m_iTexture;
	};

	bool Draw(int x, int y, float scale = 1.0)
	{
		if (!m_pSurface->IsTextureIDValid(m_iTexture))
			return false;

		m_pSurface->DrawSetColor(m_bgColor);
		m_pSurface->DrawSetTexture(m_iTexture);
		m_pSurface->DrawTexturedRect(x, y, x + (int)(m_iW * scale), (int)(y + m_iH * scale));
		return true;
	};

	uint32 m_iTexture;
	uint32 m_iW, m_iH;
	Color  m_bgColor;
	bool   m_bValid;

	ISurface* m_pSurface;
};

#endif // !texture_h