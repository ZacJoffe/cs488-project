#pragma once

#include <soloud.h>
#include <soloud_wav.h>

class SoundEngine {
public:
    static SoundEngine & getInstance();
    SoundEngine(SoundEngine const &) = delete;
    void operator=(SoundEngine const &) = delete;

    void play(SoLoud::Wav & wav);

private:
    SoundEngine();

    SoLoud::Soloud m_soloud_engine;
};

