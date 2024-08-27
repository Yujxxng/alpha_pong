#include "ResourceManager.h"

template<typename T>
inline T* ResourceManager::Get(const std::string& name)
{
	Extension ext = StringToExtension(name);

	if (res[ext].find(name) == res[ext].end())
	{
		std::unique_ptr<T> ptr(new T());
		res[ext].insert({ name, std::move(ptr) });
		res[ext][name]->Load(name);
	}

	res[ext][name]->counter++;

	return static_cast<T*>(res[ext][name].get());
}