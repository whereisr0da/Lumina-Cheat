#include "voice.h"

#include "../../common/includes.h"
#include "../../common/common.h"
#include "../../ui/sound.h"

// using resources from : fluffyguy & mz & SilentSys
// source : https://www.unknowncheats.me/forum/counterstrike-global-offensive/258133-music-voice-chat.html
//          https://www.unknowncheats.me/forum/counterstrike-global-offensive/324404-playing-custom-files-voice-chat.html
//          https://github.com/SilentSys/SLAM/blob/master/SLAM/Form1.vb

// NOTE : Idk why, but I can't use Voice_RecordStart, it record my microphone IN the input file
//        so I will do it through cmd commands like SLAM

bool voice::is_playing_sound = false;
int voice::sound_end_timestamp = 0;

hash32_t voice::last_sound_played = 0;

void voice::tick() {

    VMProtectBeginMutation("voice::tick");

    // if the end-sound-time if passed
    if (is_playing_sound && interfaces::globals->curtime >= sound_end_timestamp) {

        // stop the microphone recording
        sound_end_timestamp = 0;
        stop();
    }

    VMProtectEnd();
}

void voice::play(std::size_t sound_id) {

    VMProtectBeginMutation("voice::play");

    if (!game::isEnvironmentValid())
        return;

    // if a sound is currently not stopped
    if(is_playing_sound)
        voice::stop();

    std::string original_sound_path = XorStr("csgo\\sound\\lumina\\vocal\\");

    // append the sound name
    original_sound_path.append(sound::sounds_short[sound_id]);

    if (!std::filesystem::exists(original_sound_path))
        return;

    std::string voice_input_path = XorStr("voice_input.wav");

    // get sound path hash
    hash32_t file_path_hash = FNV1a::get(original_sound_path.c_str());

    // this part is main to check if the next sound is already "installed" (name hash check)
    // in order to fast up this homemade shitty system
    // NOTE : stay safe, keep this boolean order
    if (std::filesystem::exists(voice_input_path)) {

        // check if the sound is new
        if (last_sound_played == 0 || file_path_hash != last_sound_played) {

            // delete the file old root/voice_input.wav
            std::filesystem::remove(voice_input_path);

            // copy the sound to root/voice_input.wav
            std::filesystem::copy_file(original_sound_path, voice_input_path);
        }
    }
    else {
        // copy the sound to root/voice_input.wav
        std::filesystem::copy_file(original_sound_path, voice_input_path);
    }

    // get wav file header to get its duration
    //WavFileHeader* wav_file_header = utils::ReadWavFileHeader(voice_input_path);

    //int wav_duration = utils::GetWavDuration(wav_file_header);

    // set the end-time to stop recording
    // TODO : care about the size of wav files
    sound_end_timestamp = interfaces::globals->curtime + 5;//wav_duration;

    //free(wav_file_header);

    // launch the sound
    interfaces::engineClient->ExecuteClientCmd(XorStr("voice_inputfromfile 1; voice_loopback 1; +voicerecord"));

    if(file_path_hash != last_sound_played)
        // save the current played sound hash
        last_sound_played = file_path_hash;

    is_playing_sound = true;

    VMProtectEnd();
}

void voice::stop(void) {

    VMProtectBeginMutation("voice::stop");

    // stop recording 
    interfaces::engineClient->ExecuteClientCmd(XorStr("-voicerecord; voice_inputfromfile 0; voice_loopback 0;"));

    sound_end_timestamp = 0;
    is_playing_sound = false;

    VMProtectEnd();
}