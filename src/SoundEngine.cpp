#include "SoundEngine.h"

SoundEngine & SoundEngine::getInstance() {
    static SoundEngine instance;
    return instance;
}

void SoundEngine::play(SoLoud::Wav & wav) {
    m_soloud_engine.play(wav);
}

void SoundEngine::playIfAvailable(SoLoud::Wav & wav) {
    if (m_soloud_engine.getActiveVoiceCount() == 0) {
        m_soloud_engine.play(wav);
    }
}

SoundEngine::SoundEngine() {
    m_soloud_engine.init();
}

