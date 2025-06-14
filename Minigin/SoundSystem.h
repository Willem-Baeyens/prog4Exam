#ifndef SOUNDSYSTEM_H 
#define SOUNDSYSTEM_H
#include <memory>
#include <string>
class ISoundSystem
{
public:
	virtual ~ISoundSystem() = default;
	virtual void PlayMusic(const std::string& file, int volume) = 0;
	virtual void PlaySound(const std::string& file, int volume) = 0;
};

class NullSoundSystem : public ISoundSystem
{
	virtual void PlaySound(const std::string& , int ) override {};
	virtual void PlayMusic(const std::string& , int ) override {};
};

class SDL_SoundSystem : public ISoundSystem
{
public:
	SDL_SoundSystem();
	~SDL_SoundSystem();

	SDL_SoundSystem(const SDL_SoundSystem& other) = delete;
	SDL_SoundSystem(SDL_SoundSystem&& other) = delete;
	SDL_SoundSystem& operator=(const SDL_SoundSystem& other) = delete;
	SDL_SoundSystem& operator=(SDL_SoundSystem&& other) = delete;

	virtual void PlayMusic(const std::string& file, int volume) override;
	virtual void PlaySound(const std::string& file, int volume) override;
private:
	class Impl;
	std::unique_ptr<Impl> m_Impl;
};
#endif // !SOUNDSYSTEM_H 


