#include "SoundSystem.h"
#include  <SDL_mixer.h>
#include <stdexcept>
#include <iostream>

class SDL_SoundSystem::Impl
{
public:
	Impl();
	~Impl();

	Impl(const Impl& other) = delete;
	Impl(Impl&& other) = delete;
	Impl& operator=(const Impl& other) = delete;
	Impl& operator=(Impl&& other) = delete;

	void PlayMusic(const std::string& file, int volume);
	void PlaySound(const std::string& file, int volume);
};



SDL_SoundSystem::SDL_SoundSystem():
	m_Impl{std::make_unique<Impl>()}
{
}

SDL_SoundSystem::~SDL_SoundSystem() = default;

void SDL_SoundSystem::PlayMusic(const std::string& file, int volume)
{

	m_Impl->PlayMusic(file, volume);
}

void SDL_SoundSystem::PlaySound(const std::string& file, int volume)
{

	m_Impl->PlaySound(file, volume);
}

SDL_SoundSystem::Impl::Impl()
{
	Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 2048);
}

SDL_SoundSystem::Impl::~Impl()
{
	Mix_CloseAudio();
}

void SDL_SoundSystem::Impl::PlayMusic(const std::string& file, int volume)
{
	Mix_VolumeMusic(volume);
	Mix_Music* music = Mix_LoadMUS(file.c_str());
	if (!music)
	{
		throw std::runtime_error(SDL_GetError());
	}
	if (Mix_PlayMusic(music,INT_MAX) == -1)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

void SDL_SoundSystem::Impl::PlaySound(const std::string& file, int volume)
{
	Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
	Mix_VolumeChunk(chunk, volume);
	Mix_PlayChannel(-1,chunk,0);
}
