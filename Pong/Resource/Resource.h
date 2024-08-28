#pragma once
#include <string>

class Resource
{
	int counter = 0;
	bool persistent = false;
	
protected:
	void* data = nullptr;
	//Use static cast for this to become Texture*, Audio* ... when needed

public:
	virtual ~Resource() {}	//Otherwise you would NOT be deleting the specialized classes
	
	virtual void Load(const std::string& name) = 0;
	virtual void Unload() = 0;
	
	int GetCounter() { return counter; }
	friend class ResourceManager;
};

//Other Resources will inherit from it, implementing their own constructor, load / unload fn