#include "soundEsp.h"

#include "../../common/includes.h"
#include "../../common/common.h"

// modded from ekknod : https://github.com/ekknod/nv_v2

namespace soundEsp {

    static Entity* _target;
    static int _target_hitbox;
    static float  start_volume, min_volume;
    static ConVar* volume;

    float get_fov(Vector vangle, Vector angle)
    {
        VMProtectBeginMutation("soundEsp::get_fov");

        Vector a0, a1;

        math::angle_vectors(vangle, a0);
        math::angle_vectors(angle, a1);

        auto fov = RAD2DEG(acos(a0.Dot(a1) / (a0.Length())));

        VMProtectEnd();

        return fov;
    }

    Vector get_target_angle(Entity* localPlayer, Entity* target, int hitbox_id)
    {
        VMProtectBeginMutation("soundEsp::get_target_angle");

        Vector m, c;

        m = target->get_bone_position(hitbox_id);
        c = localPlayer->get_eye_pos();
        c.x = m.x - c.x; c.y = m.y - c.y; c.z = m.z - c.z;
        math::vec_normalize(&c);
        math::vector_angles(c, c);
        m = localPlayer->m_viewPunchAngle();
        c.x -= m.x * 2.0f, c.y -= m.y * 2.0f, c.z -= m.z * 2.0f;
        math::vec_clamp(&c);

        VMProtectEnd();

        return c;
    }


    bool get_target(Entity* localPlayer, Vector vangle)
    {
        VMProtectBeginMutation("soundEsp::get_target");

        float     best_fov;
        int       i;
        float     fov;
        int       j;

        int hitbox_list[6] = { 5, 4, 3, 0, 7, 8 };

        best_fov = 9999.0f;

        for (int i = 0; i < interfaces::globals->maxClients; i++) {

            auto entity = reinterpret_cast<Entity*>(interfaces::clientEntityList->GetClientEntity(i));

            if (!entity)
                continue;

            if (entity->m_bDormant() || entity == localPlayer || !entity->isAlive() || !entity->isPlayer())
                continue;

            if (localPlayer->m_iTeamNum() == entity->m_iTeamNum())
                continue;

            for (j = 6; j--;) {

                fov = get_fov(vangle, get_target_angle(localPlayer, entity, hitbox_list[j]));

                if (fov < best_fov) {

                    best_fov = fov;
                    _target = entity;
                    _target_hitbox = hitbox_list[j];
                }
            }
        }

        VMProtectEnd();

        return best_fov != 9999.0f;
    }

    void remove() {

        VMProtectBeginMutation("soundEsp::remove");

        if (volume->fValue != start_volume)
            volume->set_value(start_volume);

        VMProtectEnd();
    }

    void init() {

        VMProtectBeginMutation("soundEsp::init");

        volume = game::getConvarNullCallback(XorStr("volume"));

        start_volume = volume->fValue;

        if (start_volume >= 0.30f)
            start_volume = 0.25f;

        min_volume = 1.0f - start_volume;

        VMProtectEnd();
    }

    void worker(void* cmd) {

        VMProtectBeginMutation("soundEsp::worker");

        if (!config::cheats.volumeEsp)
            return;

        auto localPlayer = game::getLocalPlayer();

        if (!game::isEnvironmentValid() || !localPlayer)
            return;

        auto vangle = ((CUserCmd*)cmd)->viewangles;

        if (!get_target(localPlayer, vangle)) {

            if (volume->fValue != start_volume)
                volume->set_value(start_volume);

            return;
        }

        auto fov = get_fov(vangle, get_target_angle(localPlayer, _target, _target_hitbox));

        if (fov <= 6.0f) {

            auto vol = 1.0f - fov / 6.0f * min_volume;

            if (vol > 1.0f || vol <= start_volume)
                return;

            volume->set_value(vol);
        }

        else {
            if (volume->fValue != start_volume)
                volume->set_value(start_volume);
        }

        VMProtectEnd();
    }
}
