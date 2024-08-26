#pragma once

#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/EngineComponentManager.h"
#include "AEAudio.h"

class AudioComponent : public EngineComponent
{
	AEAudioGroup mGroup;
	AEAudio mAudio;

	float volume = 0.25f;
	float pitch = 1;

	bool loop = true;
	bool playing = false;
public:
	AudioComponent() = delete;
	AudioComponent(GameObject* owner);
	~AudioComponent();

	void Update() override;

	void SetAudio(string s);
};