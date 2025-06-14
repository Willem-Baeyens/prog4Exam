#include "ServiceLocator.h"

std::unique_ptr<ISoundSystem> ServiceLocator::sm_SoundSystem{ std::make_unique<NullSoundSystem>() };

ISoundSystem& ServiceLocator::GetSoundSystem()
{
    return *sm_SoundSystem;
}

void ServiceLocator::RegisterSoundSystem(std::unique_ptr<ISoundSystem> soundSystem)
{
    sm_SoundSystem = std::move(soundSystem);
}
