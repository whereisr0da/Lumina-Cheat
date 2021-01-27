#include "chams.h"

#include "../../hook/functions/drawModelExecute.h"
#include "../../sdk/interfaces.h"
#include "../../common/config.h"
#include "../../common/common.h"

#include <fstream>

namespace chams {

	const char* materialsNames[4];

	/*const char* materialsInternals[4]; = {
		"textured",//"vgui/white_additive",//"textured", // textured
		"debug/debugdrawflat", // flat
		"tools/toolsskyfog.vmt", // 3d la
		"models/weapons/v_models/eq_healthshot/health_shot_clear.vmt"
	};*/

	int materialSize = 4;
	IMaterial* materialPointers[4];

	std::vector<std::string> materialsInternals = {};

	void* ecx;
	void* currentState;
	const ModelRenderInfo_t* mrenderInfo;
	void* currentMatrix;

	void init() {

		VMProtectBeginMutation("chams::init");

		VECTOR_PUSH(materialsInternals, "textured", tmp0)
		VECTOR_PUSH(materialsInternals, "debug/debugdrawflat", tmp1)
		VECTOR_PUSH(materialsInternals, "tools/toolsskyfog.vmt", tmp2)
		VECTOR_PUSH(materialsInternals, "models/weapons/v_models/eq_healthshot/health_shot_clear.vmt", tmp3)

		// obligated to do it like this because of xor
		materialsNames[0] = StringHeavy("TEXTURED");
		materialsNames[1] = StringHeavy("FLAT");
		materialsNames[2] = StringHeavy("LSD");
		materialsNames[3] = StringHeavy("METALIC");

		std::string materialPath = StringHeavy("csgo\\materials\\");

		std::string texturedMaterial = StringHeavy("\"VertexLitGeneric\" {\n");
		texturedMaterial.append(StringHeavy("	\"$basetexture\" \"vgui/white_additive\"\n"));
		texturedMaterial.append(StringHeavy("	\"$ignorez\"     \"0\"\n"));
		texturedMaterial.append(StringHeavy("	\"$envmap\"       \"\"\n"));
		texturedMaterial.append(StringHeavy("	\"$nofog\"        \"1\"\n"));
		texturedMaterial.append(StringHeavy("	\"$model\"        \"1\"\n"));
		texturedMaterial.append(StringHeavy("	\"$nocull\"       \"0\"\n"));
		texturedMaterial.append(StringHeavy("	\"$selfillum\"    \"1\"\n"));
		texturedMaterial.append(StringHeavy("	\"$halflambert\"  \"1\"\n"));
		texturedMaterial.append(StringHeavy("	\"$znearer\"      \"0\"\n"));
		texturedMaterial.append(StringHeavy("	\"$flat\"         \"1\"\n"));
		texturedMaterial.append(StringHeavy("}"));

		std::ofstream(materialPath + StringHeavy("textured.vmt")) << texturedMaterial;

		//materialPointers[0] = interfaces::materialSystem->FindMaterial(XorStr("textured"), XorStr("Model textures"), true, nullptr);

		//IMaterial* mat = interfaces::materialSystem->FindMaterial(materials[materialId], XorStr("Model textures"), true, nullptr);

		//materialPointers[0] = createMaterial("dev_0", texturedMaterial, XorStr("VertexLitGeneric"));

		texturedMaterial.erase(texturedMaterial.length());

		std::string flatMaterial = StringHeavy("\"UnlitGeneric\" {\n");
		flatMaterial.append(StringHeavy("	\"$flat\" \"1\"\n"));
		flatMaterial.append(StringHeavy("	\"%noToolTexture\"     \"1\"\n"));
		flatMaterial.append(StringHeavy("}"));

		//materialPointers[1] = createMaterial("dev_1", flatMaterial, XorStr("UnlitGeneric"));

		std::ofstream(materialPath + StringHeavy("flat.vmt")) << flatMaterial;

		//materialPointers[1] = interfaces::materialSystem->FindMaterial(XorStr("flat"), XorStr("Model textures"), true, nullptr);

		flatMaterial.erase(flatMaterial.length());

		std::string lsdMaterial = StringHeavy("\"VertexLitGeneric\" {\n");
		lsdMaterial.append(StringHeavy("	\"$pearlescent\" \"1\"\n"));
		lsdMaterial.append(StringHeavy("	\"$color[0]\" \"1\"\n"));
		lsdMaterial.append(StringHeavy("	\"$envmaptint\" \"[1 0 0]\"\n"));
		lsdMaterial.append(StringHeavy("	\"proxies\"\n"));
		lsdMaterial.append(StringHeavy("		\"Sine\"\n"));
		lsdMaterial.append(StringHeavy("		{\n"));
		lsdMaterial.append(StringHeavy("			\"sineperiod\" \"1\"\n"));
		lsdMaterial.append(StringHeavy("			\"sinemin\" \"0\"\n"));
		lsdMaterial.append(StringHeavy("			\"sinemax\" \"1\"\n"));
		lsdMaterial.append(StringHeavy("			\"timeoffset\" \"0\"\n"));
		lsdMaterial.append(StringHeavy("			\"resultvar\" \"$color[0]\"\n"));
		lsdMaterial.append(StringHeavy("		}\n"));
		lsdMaterial.append(StringHeavy("		\"Sine\"\n"));
		lsdMaterial.append(StringHeavy("		{\n"));
		lsdMaterial.append(StringHeavy("			\"sineperiod\" \"1\"\n"));
		lsdMaterial.append(StringHeavy("			\"sinemin\" \"0\"\n"));
		lsdMaterial.append(StringHeavy("			\"sinemax\" \"1\"\n"));
		lsdMaterial.append(StringHeavy("			\"timeoffset\" \"0\"\n"));
		lsdMaterial.append(StringHeavy("			\"resultvar\" \"$pearlescent\"\n"));
		lsdMaterial.append(StringHeavy("		}\n"));
		lsdMaterial.append(StringHeavy("}"));

		std::ofstream(materialPath + StringHeavy("lsd.vmt")) << lsdMaterial;

		//materialPointers[2] = interfaces::materialSystem->FindMaterial(XorStr("lsd"), XorStr("Model textures"), true, nullptr);

		//materialPointers[2] = createMaterial("dev_2", lsdMaterial, XorStr("VertexLitGeneric"));

		lsdMaterial.erase(lsdMaterial.length());

		VMProtectEnd();

#ifdef _DEBUG
		common::ps(XorStr("chams::init : done"));
#endif
	}

#define CHAMS(config, vector, info) if (config.enable && vector) { \
		drawMaterial(&(config), info); \
		drawOriginal = false; \
	} \

	bool drawModelExecute(void* context, void* state, const ModelRenderInfo_t& renderInfo, void* matrix) {

		VMProtectBeginMutation("chams::drawModelExecute");

		bool drawOriginal = true;

		auto model = reinterpret_cast<const model_t*>(renderInfo.pModel);

		if (!model)
			return drawOriginal;

		auto modelName = interfaces::modelInfo->GetModelName(model);

		if (!modelName)
			return drawOriginal;

		ecx = context;
		currentState = state;
		//mrenderInfo = &renderInfo;
		currentMatrix = matrix;

		if(renderInfo.entity_index == INVALID_EHANDLE_INDEX)
			return drawOriginal;

		Entity* entity = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntity(renderInfo.entity_index));

		if (!entity)
			return drawOriginal;

		//bool isWeapon = strstr(modelName, XorStr("models/weapons/v_")) && !strstr(modelName, XorStr("v_models"));
		//bool isWeaponWorld = strstr(modelName, XorStr("models/weapons/w_")) && !strstr(modelName, XorStr("w_models"));
		//bool isHands = strstr(modelName, XorStr("arms")) && !strstr(modelName, XorStr("sleeve"));
		//bool isSleeves = strstr(modelName, XorStr("arms")) && strstr(modelName, XorStr("sleeve"));
		bool isPlayer = entity->isPlayer() && entity->isAlive();//strstr(modelName, XorStr("models/player"));

		CHAMS(config::visual.enemyChamsVisible, isPlayer && game::getLocalPlayer()->m_iTeamNum() != entity->m_iTeamNum(), renderInfo)
		//CHAMS(config::visual.enemyChamsNotVisible, isPlayer && game::getLocalPlayer()->m_iTeamNum() != entity->m_iTeamNum(), renderInfo)
		//CHAMS(config::visual.handChams, isHands, renderInfo)
		//CHAMS(config::visual.sleeveChams, isSleeves, renderInfo)
		//CHAMS(config::visual.weaponChams, isWeapon, renderInfo)

		VMProtectEnd();

		return drawOriginal;
	}

	void drawMaterial(chams_t* chams, const ModelRenderInfo_t& renderInfo) {

		VMProtectBeginMutation("chams::drawMaterial");

		float defaultColor[3] = { 1.0f, 1.0f, 1.0f };

		IMaterial* mat = interfaces::materialSystem->FindMaterial(materialsInternals.at(chams->material).c_str(), XorStr("Model textures"), true, nullptr);
		
		mat->IncrementReferenceCount();

		interfaces::modelRender->ForcedMaterialOverride(mat);

		mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, chams->throughWall && (!chams->throughWallOnlyIfDead || (chams->throughWallOnlyIfDead && !game::getLocalPlayer()->isAlive())));

		interfaces::renderView->SetColorModulation(chams->color.Base());

		interfaces::renderView->SetBlend(chams->color.aBase());

		auto returnCall = reinterpret_cast<drawModelExecuteFn>(hook::modelRenderHook.get_original(21));
		
		// draw
		returnCall(interfaces::modelRender, ecx, currentState, renderInfo, currentMatrix);

		// reset
		interfaces::modelRender->ForcedMaterialOverride(nullptr);
		interfaces::renderView->SetColorModulation(defaultColor);

		VMProtectEnd();
	}

	/*
	IMaterial* createMaterial(std::string name, std::string buffer, std::string type)
	{
		
		auto matdata =
			"\"" + type + "\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"" + std::to_string(wireframe) + "\"\
        \n}\n";
		

		auto keyValues = static_cast<KeyValues*>(malloc(sizeof(KeyValues)));

		initKeyValues(keyValues, type.c_str());
		
		loadFromBuffer(keyValues, name.c_str(), buffer.c_str());

		auto material = interfaces::materialSystem->CreateMaterial(name.c_str(), keyValues);

		// don't know if it's good
		material->IncrementReferenceCount();

		return material;
	}

	void initKeyValues(KeyValues* kv_, std::string name_)
	{
		static auto address = interfaces::initKeyValuesMaterial;
		using Fn = void(__thiscall*)(void* thisptr, const char* name);
		reinterpret_cast<Fn>(address)(kv_, name_.c_str());
	}

	void loadFromBuffer(KeyValues* vk_, std::string name_, std::string buffer_)
	{
		static auto address = interfaces::loadFromBufferMaterial;

		using Fn = void(__thiscall*)(
			void* thisptr, const char* resourceName,
			const char* pBuffer, void* pFileSystem,
			const char* pPathID, void* pfnEvaluateSymbolProc);

		reinterpret_cast<Fn>(address)(
			vk_, name_.c_str(), buffer_.c_str(), nullptr, nullptr, nullptr);
	}*/
}