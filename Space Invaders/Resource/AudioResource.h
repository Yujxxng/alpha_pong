#pragma once
#include <string>
#include "Resource.h"
#include "AEAudio.h"

class AudioResource : public Resource
{
private:
	AudioResource();
	AEAudio audioData;

public:
	~AudioResource() override;
	
	void Load(const std::string& name) override;
	void Unload() override;
	
	AEAudio* GetData() const;

	friend class ResourceManager;
};

//Other Resources will inherit from it, implementing their own constructor, load / unload fn