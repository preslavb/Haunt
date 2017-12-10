#pragma once
#include <vector>
#include <functional>

template<typename T>
class GarbageDestroyer
{
private:
	std::vector<T> garbage;

	static GarbageDestroyer<T>* instance;
public:
	GarbageDestroyer()
	{
		
	}

	static GarbageDestroyer<T>* GetInstance();

	void Destroy(T t_object, function<void(T)> t_destroy_function = nullptr)
	{
		if (t_destroy_function != nullptr)
		{
			t_destroy_function(t_object);
		}

		garbage.push_back(t_object);
	}

	void ClearGarbage()
	{
		if (!garbage.empty())
		{
			delete garbage.back();
			garbage.pop_back(); 
		}
	}
};

template<typename T>
GarbageDestroyer<T>* GarbageDestroyer<T>::instance = nullptr;

template<typename T>
GarbageDestroyer<T>* GarbageDestroyer<T>::GetInstance()
{
	if (!instance)
	{
		instance = new GarbageDestroyer<T>;
	}

	return instance;
}