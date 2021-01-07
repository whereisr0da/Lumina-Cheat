#pragma once

// from Osiris : https://github.com/danielkrupinski/Osiris/blob/master/Osiris/SDK/StudioRender.h

enum class OverrideType {
	Normal = 0,
	BuildShadows,
	DepthWrite,
	CustomMaterial, // weapon skins
	SsaoDepthWrite
};

class IStudioRender {
	byte pad_0[0x250];
	IMaterial* materialOverride;
	byte pad_1[0xC];
	OverrideType overrideType;

public:
	bool isForcedMaterialOverride()
	{
		if (!materialOverride)
			return overrideType == OverrideType::DepthWrite || overrideType == OverrideType::SsaoDepthWrite; // see CStudioRenderContext::IsForcedMaterialOverride

		return strstr(materialOverride->GetName(), XorStr("dev/glow"));
	}
};
