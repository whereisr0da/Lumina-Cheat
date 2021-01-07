#include "fireEventClientSide.h"

/*
bool __fastcall fireEventClientSideHook(void* thisptr, void* edx, IGameEvent* event)
{
	auto returnCall = reinterpret_cast<fireEventClientSideFn>(hook::eventManagerHook.get_original(8));

	if (event)
	{
		if (!strcmp(event->GetName(), "bomb_planted")) //event name from the list
		{
			int userid = event->GetInt("userid"); //userid != entityid 
			int entid = gInts.Engine->GetPlayerForUserID(userid); //index 9 in EngineClient


			if (entid == gInts.Engine->GetLocalPlayer()) //index 12 in EngineClient
				printf("I just planted the bomb!");
		}
	}

	return returnCall(thisptr, edx, event);
}
*/