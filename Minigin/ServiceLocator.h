#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include "SoundSystem.h"
#include <memory>

class ServiceLocator final
{
public:
	[[nodiscard]] static ISoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(std::unique_ptr<ISoundSystem> soundSystem);
private:
	static std::unique_ptr<ISoundSystem> sm_SoundSystem;
};
#endif // !SERVICELOCATOR_H

