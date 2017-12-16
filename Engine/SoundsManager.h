#pragma once

#include "SDL/SDL_mixer.h"
#include <unordered_map>
#include "GameConstants.h"

// The sound effect and music manager class
class SoundsManager
{
private:
	// Singleton instance
	static SoundsManager* instance;

	// Constructor and destructor
	SoundsManager();
	~SoundsManager();

	// An instance of the background music to play in the game
	Mix_Music* backgroundMusic;

	// The sound effects map with the associated names
	std::unordered_map<LPCSTR, Mix_Chunk*> soundEffectsMap;
public:

	// Names of the textures, used to reference a specific texture in the texturesMap
	std::vector<LPCSTR> SoundEffectNames;

	// The path to the actual textures
	std::vector<LPCSTR> SoundEffectFiles;

	// Accessor for the singleton
	static SoundsManager* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SoundsManager();
		}

		return instance;
	}

	// Initialize the sound effects and load them in
	void Initialize();

	// Delete all sound effects
	void CleanUp();

	// Methods for playing the sound effects
	void PlaySoundEffect(LPCSTR t_string);
	void PlaySoundEffectContinuous(LPCSTR t_string);
	void StopSoundEffect(LPCSTR t_string);
};

