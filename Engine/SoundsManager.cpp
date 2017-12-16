#include "stdafx.h"
#include "SoundsManager.h"
#include "Errors.h"

// Initialize the singleton instnace to a null pointer
SoundsManager* SoundsManager::instance = nullptr;

SoundsManager::SoundsManager()
{
}


SoundsManager::~SoundsManager()
{
}

void SoundsManager::Initialize()
{
	// Load in the background music
	backgroundMusic = Mix_LoadMUS("Music/Background Music.wav");

	//If there was a problem loading the music
	if (backgroundMusic == nullptr)
	{
		fatalError("Background music failed to initialize");
	}

	// Lower the music volume so that the sound effects are audible, then play the music
	Mix_VolumeMusic(50);
	Mix_PlayMusic(backgroundMusic, -1);

	// Register all of the given files as sound effects
	for (int i = 0; i < max(SoundEffectNames.size(), SoundEffectFiles.size()); i++)
	{
		soundEffectsMap.insert(std::pair<LPCSTR, Mix_Chunk*>(SoundEffectNames[i], Mix_LoadWAV(SoundEffectFiles[i])));
	}
}

void SoundsManager::CleanUp()
{
	// Stop the music and remove it from the mixer
	Mix_FreeMusic(backgroundMusic);

	Mix_CloseAudio();
}

void SoundsManager::PlaySoundEffect(LPCSTR t_string)
{
	auto soundEffect = soundEffectsMap.find(t_string);

	//Play the sound effect if one was found
	soundEffect != soundEffectsMap.end() ? Mix_PlayChannel(std::distance(soundEffectsMap.begin(), soundEffect), soundEffect->second, 0) : 0;
}

void SoundsManager::PlaySoundEffectContinuous(LPCSTR t_string)
{
	auto soundEffect = soundEffectsMap.find(t_string);

	//Play the sound effect if one was found
	soundEffect != soundEffectsMap.end() && ! Mix_Playing(std::distance(soundEffectsMap.begin(), soundEffect)) ? Mix_PlayChannel(std::distance(soundEffectsMap.begin(), soundEffect), soundEffect->second, -1) : 0;
}

void SoundsManager::StopSoundEffect(LPCSTR t_string)
{
	auto soundEffect = soundEffectsMap.find(t_string);

	//Play the sound effect if one was found
	soundEffect != soundEffectsMap.end() ? Mix_HaltChannel(std::distance(soundEffectsMap.begin(), soundEffect)) : 0;
}