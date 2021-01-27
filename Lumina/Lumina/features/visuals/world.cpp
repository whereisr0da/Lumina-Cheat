#include "world.h"

#include "../../common/common.h"
#include "../../sdk/interfaces.h"

std::vector<IMaterial*> worlds, props;
std::vector<std::string> world::skyboxs = std::vector<std::string>();

void world::worldModulation() {

	VMProtectBeginMutation("world::worldModulation");

	if (!game::getLocalPlayer() || !game::isEnvironmentValid())
		return;

	static ConVar* r_DrawSpecificStaticProp = (ConVar*)interfaces::console->get_convar(XorStr("r_DrawSpecificStaticProp"));

	*(int*)((DWORD)&r_DrawSpecificStaticProp->fnChangeCallbacks + 0xC) = NULL;

	// IsUsingStaticPropDebugModes : thx pandora
	r_DrawSpecificStaticProp->set_value(config::visual.world.enable ? 0 : -1);

	// reset mat collection
	worldModulationResetMaterials();

	// modulate world
	for (auto mat : worlds) {

		if (config::visual.world.enable) {
			mat->ColorModulate((float)config::visual.world.worldColor.r() / 255.0f, (float)config::visual.world.worldColor.g() / 255.0f, (float)config::visual.world.worldColor.b() / 255.0f);
			mat->AlphaModulate((float)config::visual.world.worldColor.a() / 255.0f);
		}
		else {
			mat->ColorModulate(1.f, 1.f, 1.f);
			mat->AlphaModulate(1.f);
		}
	}

	// modulate props
	for (auto mat : props) {

		if (config::visual.world.enable) {
			mat->ColorModulate((float)config::visual.world.propsColor.r() / 255.0f, (float)config::visual.world.propsColor.g() / 255.0f, (float)config::visual.world.propsColor.b() / 255.0f);
			mat->AlphaModulate((float)config::visual.world.propsColor.a() / 255.0f);
		}
		else {
			mat->ColorModulate(1.f, 1.f, 1.f);
			mat->AlphaModulate(1.f);
		}
	}

	VMProtectEnd();
}

void world::init() {

	VMProtectBeginMutation("world::init");

	VECTOR_PUSH(skyboxs, "sky_csgo_night02", tmp0)
	VECTOR_PUSH(skyboxs, "sky101", tmp1)
	VECTOR_PUSH(skyboxs, "sky105", tmp2)
	VECTOR_PUSH(skyboxs, "sky106", tmp3)
	VECTOR_PUSH(skyboxs, "sky191", tmp4)
	VECTOR_PUSH(skyboxs, "vertigoblue_hdr", tmp5)
	VECTOR_PUSH(skyboxs, "sky302", tmp6)
	VECTOR_PUSH(skyboxs, "sky303", tmp7)
	VECTOR_PUSH(skyboxs, "space_10", tmp8)
	VECTOR_PUSH(skyboxs, "space", tmp9)
	VECTOR_PUSH(skyboxs, "mr_15", tmp10)
	VECTOR_PUSH(skyboxs, "sky184", tmp11)

	VMProtectEnd();
}

void world::changeWorldSky() {

	VMProtectBeginMutation("world::changeWorldSky");

	if (!game::getLocalPlayer() || !game::isEnvironmentValid())
		return;

	static ConVar* r_3dsky = (ConVar*)interfaces::console->get_convar(XorStr("r_3dsky"));

	*(int*)((DWORD)&r_3dsky->fnChangeCallbacks + 0xC) = NULL;

	r_3dsky->set_value(config::visual.sky.enable ? 0 : 1);

	// normally I just do it once, but here, it's needed
	using changeSkyFn = void(__fastcall*)(const char*);

	auto changeSky = (changeSkyFn)(interfaces::patternScan(common::engineModule, XorStr("55 8B EC 81 EC ? ? ? ? 56 57 8B F9 C7 45")));

	if (config::visual.sky.enable)
		changeSky(skyboxs.at(config::visual.sky.sky).c_str());
	else
		changeSky(XorStr("vertigoblue_hdr"));

	VMProtectEnd();
}

void world::worldModulationResetMaterials() {

	VMProtectBeginMutation("world::worldModulationResetMaterials");

	worlds.clear();
	props.clear();

	for (auto h = interfaces::materialSystem->FirstMaterial();
		h != interfaces::materialSystem->InvalidMaterial();
		h = interfaces::materialSystem->NextMaterial(h)) {

		IMaterial* mat = interfaces::materialSystem->GetMaterial(h);

		if (!mat)
			continue;

		if (mat->IsErrorMaterial())
			continue;

		hash32_t textureGroupHash = FNV1a::get(mat->GetTextureGroupName());

		if (textureGroupHash == HASH(TEXTURE_GROUP_WORLD))
			worlds.push_back(mat);

		if (textureGroupHash == HASH("StaticProp textures"))
			props.push_back(mat);

	}

	VMProtectEnd();
}