#pragma once

class CGlowObjectManager
{
public:
	class GlowObjectDefinition_t
	{
	public:
		bool ShouldDraw() const { return m_pEntity && ( m_bRenderWhenOccluded || m_bRenderWhenUnoccluded ); }
		bool IsUnused() const { return m_nNextFreeSlot != GlowObjectDefinition_t::ENTRY_IN_USE; }

		void*	m_pEntity;
		Vector          m_vGlowColor;
		float           m_flGlowAlpha;

		char			unknown[ 4 ];
		float           flUnk;
		float           m_flBloomAmount;
		float           localplayeriszeropoint3;
		bool            m_bRenderWhenOccluded;
		bool            m_bRenderWhenUnoccluded;
		bool            m_bFullBloomRender;
		char            unknown1[ 1 ];
		int             m_nFullBloomStencilTestValue; // 0x28 only render full bloom objects if stencil is equal to this value (value of -1 implies no stencil test)
		int             iUnk; //appears like it needs to be zero  
		int             m_nSplitScreenSlot; //Should be -1 
											// Linked list of free slots 
		int             m_nNextFreeSlot;
		// Special values for GlowObjectDefinition_t::m_nNextFreeSlot 
		static const int END_OF_FREE_LIST = -1;
		static const int ENTRY_IN_USE = -2;
	};

	//CUtlVector< GlowObjectDefinition_t > m_glObjectDefinitions;
	//int m_nFirstFreeSlot;
	GlowObjectDefinition_t *m_glObjectDefinitions;
	char pad[8];
	int size;
};

struct ShaderStencilState_t
{
	bool m_bEnable;
	StencilOperation_t m_FailOp;
	StencilOperation_t m_ZFailOp;
	StencilOperation_t m_PassOp;
	StencilComparisonFunction_t m_CompareFunc;
	int m_nReferenceValue;
	uint32 m_nTestMask;
	uint32 m_nWriteMask;

	ShaderStencilState_t()
	{
		m_bEnable = false;
		m_PassOp = m_FailOp = m_ZFailOp = STENCILOPERATION_KEEP;
		m_CompareFunc = STENCILCOMPARISONFUNCTION_ALWAYS;
		m_nReferenceValue = 0;
		m_nTestMask = m_nWriteMask = 0xFFFFFFFF;
	}
};

extern CGlowObjectManager* g_pGlowObjectManager;