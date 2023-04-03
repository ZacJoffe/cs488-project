#include "SoundEngine.h"

SoundEngine & SoundEngine::getInstance() {
    static SoundEngine instance;
    return instance;
}

void SoundEngine::play(SoLoud::Wav & wav) {
    m_soloud_engine.play(wav);
}

SoundEngine::SoundEngine() {
    m_soloud_engine.init();
}

