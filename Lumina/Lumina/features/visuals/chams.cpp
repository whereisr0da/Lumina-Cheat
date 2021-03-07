#include "chams.h"

#include "../../hook/functions/drawModelExecute.h"
#include "../../sdk/interfaces.h"
#include "../../common/config.h"
#include "../../common/common.h"
#include "../../features/backtrack/backtrack.h"

#include <fstream>

namespace chams {

	const char* materialsNames[6];

	int materialSize = 6;
	IMaterial* materialPointers[6];

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
		VECTOR_PUSH(materialsInternals, "glowOverlay", tmp4)
		VECTOR_PUSH(materialsInternals, "models/inventory_items/trophy_majors/silver_plain.vmt", tmp5)

		// obligated to do it like this because of xor
		materialsNames[0] = StringHeavy("TEXTURED");
		materialsNames[1] = StringHeavy("FLAT");
		materialsNames[2] = StringHeavy("MESHES");
		materialsNames[3] = StringHeavy("METALIC");
		materialsNames[4] = StringHeavy("GLOW OVERLAY");
		materialsNames[5] = StringHeavy("CHROME");

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

		texturedMaterial.erase(texturedMaterial.length());

		std::string flatMaterial = StringHeavy("\"UnlitGeneric\" {\n");
		flatMaterial.append(StringHeavy("	\"$flat\" \"1\"\n"));
		flatMaterial.append(StringHeavy("	\"%noToolTexture\"     \"1\"\n"));
		flatMaterial.append(StringHeavy("}"));

		std::ofstream(materialPath + StringHeavy("flat.vmt")) << flatMaterial;

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

		lsdMaterial.erase(lsdMaterial.length());


		std::string glowOverlayMaterial = StringHeavy("\"VertexLitGeneric\" {\n");
		glowOverlayMaterial.append(StringHeavy("	\"$additive\" \"1\"\n"));
		glowOverlayMaterial.append(StringHeavy("	\"$envmap\" \"models/effects/cube_white\"\n"));
		glowOverlayMaterial.append(StringHeavy("	\"$envmaptint\" \"[0 0 0]\"\n"));
		glowOverlayMaterial.append(StringHeavy("	\"$envmapfresnel\" \"1\"\n"));
		glowOverlayMaterial.append(StringHeavy("	\"$envmapfresnelminmaxexp\" \"[0 1 2]\"\n"));
		glowOverlayMaterial.append(StringHeavy("	\"$alpha\" \"0.8\"\n"));
		glowOverlayMaterial.append(StringHeavy("}"));

		std::ofstream(materialPath + StringHeavy("glowOverlay.vmt")) << glowOverlayMaterial;

		glowOverlayMaterial.erase(glowOverlayMaterial.length());

		VMProtectEnd();

#ifdef _DEBUG
		common::ps(XorStr("chams::init : done"));
#endif
	}

	bool drawModelExecute(void* context, void* state, const ModelRenderInfo_t& renderInfo, void* matrix, const char* modelName, bool arms, bool sleeve) {

		VMProtectBeginMutation("chams::drawModelExecute");

		bool drawOriginal = true;

		// means !renderInfo.pModel
		if (!modelName)
			return drawOriginal;

		ecx = context;
		currentState = state;
		currentMatrix = matrix;

		bool isHands = arms && !sleeve;
		bool isSleeves = arms && sleeve;

		// hands and sleeves doesn't have an entity
		if ((isHands || isSleeves) && (game::getLocalPlayer() && game::getLocalPlayer()->isAlive())) {

			// draw hands
			CHAMS(config::visual.handChams, isHands, renderInfo, currentMatrix)
			// draw sleeves
			CHAMS_ELSE(config::visual.sleeveChams, isSleeves, renderInfo, currentMatrix)
		}
		else {

			if (renderInfo.entity_index == INVALID_EHANDLE_INDEX)
				return drawOriginal;

			Entity* entity = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntity(renderInfo.entity_index));

			if (!entity)
				return drawOriginal;

			bool isPlayerEnemy = (entity->isPlayer() && entity->isAlive()) && game::getLocalPlayer()->m_iTeamNum() != entity->m_iTeamNum();

			if (isPlayerEnemy && config::cheats.backtrack && config::visual.enemyChamsBacktrack.enable) {

				auto record = &backtrack::records[entity->index()];

				// checks that record exists for the enemy
				if (record && record->size() > 1 && backtrack::valid_tick(record->front().simulation_time)) {

					int factor = (config::cheats.backtrackVisibility / 100) * record->size();

					for (size_t i = 1; i < factor; i++){

						// draw backtrack
						CHAMS(config::visual.enemyChamsBacktrack, isPlayerEnemy, renderInfo, record->at(i).matrix)
					}
				}
			}

			// draw player
			CHAMS(config::visual.enemyChamsVisible, isPlayerEnemy, renderInfo, currentMatrix)
		}

		VMProtectEnd();

		return drawOriginal;
	}

	void drawMaterial(chams_t* chams, const ModelRenderInfo_t& renderInfo, void* matrix) {

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
		returnCall(interfaces::modelRender, ecx, currentState, renderInfo, matrix);

		// overlay part
		if (chams->enableOverlay)
		{
			// glow overlay
			auto glowOverlay = interfaces::materialSystem->FindMaterial(materialsInternals.at(chams->overlayMaterial).c_str(), XorStr("Other textures"), true, nullptr);

			glowOverlay->IncrementReferenceCount();

			bool materialVariableFound = false;

			auto tint = glowOverlay->FindVar(XorStr("$envmaptint"), &materialVariableFound);

			if (materialVariableFound)
			{
				interfaces::modelRender->ForcedMaterialOverride(glowOverlay);

				interfaces::renderView->SetColorModulation(chams->overlayColor.Base());

				tint->setColor(chams->overlayColor.rBase(), chams->overlayColor.gBase(), chams->overlayColor.bBase());

				interfaces::renderView->SetBlend(chams->overlayColor.aBase());

				// draw overlay
				returnCall(interfaces::modelRender, ecx, currentState, renderInfo, matrix);
			}
		}

		// reset
		interfaces::modelRender->ForcedMaterialOverride(nullptr);
		interfaces::renderView->SetColorModulation(defaultColor);

		VMProtectEnd();
	}
}