#ifndef MUSIC_PLAYER_HPP_
#define MUSIC_PLAYER_HPP_

#include "drivers.hpp"
#include "vector"
#include "tap/communication/sensors/buzzer/buzzer.hpp"
#include "notes.hpp"
#include "music_scores/playlist.hpp"
#include "tap/architecture/timeout.hpp"


using namespace tap;
using namespace tap::buzzer;

namespace music{

class MusicPlayer{
    public:
        MusicPlayer(src::Drivers *drivers, const vector<pair<float, float>>& score, unsigned tempo);

        bool finishedSong() const {return isFinished;}

        void execute();

        bool nextNote() const {return timeout.isExpired();}

        void resetSong() {
            resting = false;
            index = 0;
            init();
        }

        void init(){timeout.restart(1);}

    private:
        src::Drivers* drivers;
        const vector<pair<float, float>> yourSong;
        const unsigned tempo;
        size_t index;
        bool resting;
        bool isFinished;
        tap::arch::MilliTimeout timeout;
        
};
} //namespace music

#endif