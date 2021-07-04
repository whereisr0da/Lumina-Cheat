#include "sound.h"

#include "../common/common.h"

#include "../sdk/interfaces.h"

#include <fstream>
#include <filesystem>

namespace sound {

	std::vector<std::string> sounds_short = {};
	std::vector<std::string> sounds_long = {};

	void init() {

		VMProtectBeginMutation("sound::init");

		std::string sound_path_short = StringHeavy("csgo\\sound\\lumina\\short");
		std::string sound_path_long = StringHeavy("csgo\\sound\\lumina\\long");

		for (const auto& entry : std::filesystem::directory_iterator(sound_path_short)) {
			if(strstr(entry.path().filename().string().c_str(), XorStr(".wav")))
				sounds_short.push_back(entry.path().filename().string());
		}
			

		for (const auto& entry : std::filesystem::directory_iterator(sound_path_long)) {
			if (strstr(entry.path().filename().string().c_str(), XorStr(".wav")))
				sounds_long.push_back(entry.path().filename().string());
		}

		//VECTOR_PUSH(sounds, "oof.mp3", tmp0)
		//VECTOR_PUSH(sounds, "heasshotgirl.wav", tmp1)
		//VECTOR_PUSH(sounds, "marioFail.wav", tmp2)
		//VECTOR_PUSH(sounds, "cavapeter.wav", tmp3)
		//VECTOR_PUSH(sounds, "roblox.wav", tmp4)
		//VECTOR_PUSH(sounds, "byebye.mp3", tmp5)
		//VECTOR_PUSH(sounds, "bell.wav", tmp6)
		//VECTOR_PUSH(sounds, "open.wav", tmp7)
		//VECTOR_PUSH(sounds, "close.wav", tmp8)
		//VECTOR_PUSH(sounds, "cod.wav", tmp9)
		//VECTOR_PUSH(sounds, "fatality.wav", tmp10)
		//VECTOR_PUSH(sounds, "flick.wav", tmp11)
		//VECTOR_PUSH(sounds, "bell.wav", tmp12)
		//VECTOR_PUSH(sounds, "marioFail.wav", tmp13)
		//VECTOR_PUSH(sounds, "buttons\\arena_switch_press_02.wav", tmp14)
		//VECTOR_PUSH(sounds, "pw_ragequit.mp3", tmp15)
		//VECTOR_PUSH(sounds, "started.wav", tmp16)
		//VECTOR_PUSH(sounds, "bom.mp3", tmp17)
		//VECTOR_PUSH(sounds, "pong.wav", tmp18)
		//VECTOR_PUSH(sounds, "solong.wav", tmp19)
		//VECTOR_PUSH(sounds, "hello.wav", tmp20)
		//VECTOR_PUSH(sounds, "bowser.mp3", tmp21)
		//VECTOR_PUSH(sounds, "newchainssameshackles.mp3", tmp22)

		VMProtectEnd();
	}

	void playSoundShort(int id) {

		VMProtectBeginMutation("sound::playSoundShort");

		std::string sound_path_short = XorStr("lumina\\short\\");
		sound_path_short.append(sound::sounds_short[id]);

		// play the sound
		interfaces::surface->PlaySound(sound_path_short.c_str());

		VMProtectEnd();
	}

	void playOpeningSound() {

		VMProtectBeginMutation("sound::playOpeningSound");

		interfaces::surface->PlaySound(XorStr("lumina\\open.wav"));

		//PlaySoundA(openRaw, NULL, SND_ASYNC | SND_MEMORY);

		VMProtectEnd();
	}

	void playClosingSound() {

		VMProtectBeginMutation("sound::playClosingSound");

		interfaces::surface->PlaySound(XorStr("lumina\\close.wav"));

		VMProtectEnd();
	}
}