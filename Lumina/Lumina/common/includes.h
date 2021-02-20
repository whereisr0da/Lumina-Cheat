#ifndef includes_h

//#define FULL_DEBUG

#ifdef NDEBUG
//#pragma optimize("", off)
#define MUTATION
#endif

#include <Windows.h>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>
#include <cstdint>
#include <xstring>
#include <cstring>
#include <map>
#include <deque>
#include <d3dx9.h>
#include <corecrt_math.h>
#include <unordered_map>
#include <algorithm>

#ifdef MUTATION
#include <VMProtectSDK.h>
#define StringHeavy(s) (VMProtectDecryptStringA(s))
#else
// ;)
// find yourself why I did that
#include <VMProtectSDK.h>
#define StringHeavy(s) (VMProtectDecryptStringA(s))
//#define StringHeavy(s) (s)
//#define VMProtectBeginMutation(NAME) const char* FUNCTION_NAME = NAME
//#define VMProtectEnd() char* FUNCTION_NAME_END
#endif

#include "vfunc.h"

#include "../sdk/defines.h"

#include "../security/hash.h"

#include "../sdk/math/math.h"
#include "../sdk/math/Color.h"
#include "../sdk/math/CUtlVector.h"
#include "../sdk/math/Vector.h"
#include "../sdk/math/matrix3x4_t.h"
#include "../sdk/math/QAngle.h"
#include "../sdk/math/Vector2D.h"
#include "../sdk/math/Vector4D.h"
#include "../sdk/math/VMatrix.h"

#include "../sdk/structs/structs.h"
#include "../sdk/structs/misc.h"
#include "../sdk/structs/mystructs.h"

#include "../sdk/structs/datamap.h"

#include "../sdk/structs/IMaterial.h"

#include "../sdk/structs/CBoneChache.h"
#include "../sdk/structs/ClientClass.h"
#include "../sdk/structs/CNetChannel.h"
#include "../sdk/structs/IClientEntity.h"
#include "../sdk/structs/ConVar.h"
#include "../sdk/structs/INetChannelInfo.h"

#include "../sdk/interfaces/IBaseClientDll.h"
#include "../sdk/interfaces/ISurface.h"
#include "../sdk/interfaces/IVPanel.h"
#include "../sdk/interfaces/IMaterialSystem.h"
#include "../sdk/interfaces/IEngineClient.h"
#include "../sdk/interfaces/IGlobalVarsBase.h"
#include "../sdk/interfaces/IClientEntityList.h"
#include "../sdk/interfaces/IVDebugOverlay.h"
#include "../sdk/interfaces/IVModelInfo.h"
#include "../sdk/interfaces/IVModelRender.h"
#include "../sdk/interfaces/IVRenderView.h"
#include "../sdk/interfaces/CSPlayerResource.h"
#include "../sdk/interfaces/ICVar.h"
#include "../sdk/interfaces/IGameEventManager.h"
#include "../sdk/interfaces/ILocalize.h"
#include "../sdk/interfaces/CGlowObjectManager.h"
#include "../sdk/interfaces/IConsole.h"
#include "../sdk/interfaces/ISteamGameServer.h"
#include "../sdk/interfaces/IStudioRender.h"

#include "../sdk/netvars.h"

#include "../sdk/structs/Entity.h"

#include "utils.h"

#include "../sdk/offsets.h"

#include "../security/instr.h"
#include "../security/lazy.hpp"
#include "../security/xorstr.hpp"
#include "../security/eraser.hpp"

#include "../hook/hook.h"

#include "game.h"

#include "../hook/functions/paintTraverse.h"
#include "../hook/functions/lockCursor.h"
#include "../hook/functions/shutdown.h"
#include "../hook/functions/drawModelExecute.h"
#include "../hook/functions/frameStageNotify.h"
#include "../hook/functions/serverSideChecks.h"
#include "../hook/functions/doPostScreenEffects.h"
#include "../hook/functions/fireEventClientSide.h"
#include "../hook/functions/createMove.h"
#include "../hook/functions/shouldDrawFog.h"
#include "../hook/functions/levelInitPostEntity.h"

#include "config.h"

#endif // !includes_h