#ifndef voice_h

#define voice_h

#include <string>
#include "../../security/hash.h"

namespace voice {

    extern bool is_playing_sound;
    extern int sound_end_timestamp;
    extern hash32_t last_sound_played;

    void play(std::size_t sound_id);
    void stop();
    void tick();
};

#endif // !voice_h