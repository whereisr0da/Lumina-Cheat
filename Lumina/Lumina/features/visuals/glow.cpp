#include "glow.h"

#include "../../common/includes.h"
#include "../../sdk/interfaces.h"
#include "../../common/config.h"
#include "../../common/common.h"

namespace glow {

	void execute() 
	{
		VMProtectBeginMutation("glow::execute");

		if (!config::visual.glow.enable)
			return;

		Entity* localPlayer = game::getLocalPlayer();

		if (!localPlayer || !game::isEnvironmentValid())
			return;

		if (localPlayer->isAlive() && config::visual.glow.onlyIfDead)
			return;

		for (auto i = 0; i < interfaces::glowManager->size; i++)
		{
			auto glow_object = &interfaces::glowManager->m_glObjectDefinitions[i];

			Entity* entity = (Entity*)glow_object->m_pEntity;

			if (!entity || glow_object->IsUnused())
				continue;

			if (!entity->isAlive() || entity->m_bDormant())
				continue;

			if (entity->Class()->m_ClassID == ClassId::ClassId_CCSPlayer && entity->m_iTeamNum() != localPlayer->m_iTeamNum())
			{
				Vector colorVector = Vector(config::visual.glow.glowColor.rBase(), config::visual.glow.glowColor.gBase(), config::visual.glow.glowColor.bBase());

				glow_object->m_vGlowColor = colorVector;
				glow_object->m_flGlowAlpha = config::visual.glow.glowColor.aBase();
				glow_object->m_flBloomAmount = config::visual.glow.bloom;
				glow_object->m_bRenderWhenOccluded = true;
				glow_object->m_bRenderWhenUnoccluded = false;
				//glow_object->m_bFullBloomRender = false;

				continue;
			}
		}

		VMProtectEnd();
	}
}