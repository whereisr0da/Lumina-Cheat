#pragma once

class C_CSGameRulesProxy
{
public:
	OFFSET( m_bFreezePeriod, bool, 0x20 )
		OFFSET( m_bIsValveDS, bool, 0x75 )
		OFFSET( m_bBombPlanted, bool, 0x8D1 )
		OFFSET( m_bBombDropped, bool, 0x8D0 )
};