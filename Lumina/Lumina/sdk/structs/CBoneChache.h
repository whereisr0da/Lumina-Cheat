#pragma once

class CBoneCache
{
public:
	matrix3x4_t* m_pCachedBones;
	char pad[ 8 ];
	unsigned int m_CachedBoneCount;
};