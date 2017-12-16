#pragma once
#include <vector>
#include <functional>

// Class used to dispose of any variables at the end of the frame (making sure all calculations are valid this frame)
template<typename T>
class GarbageDestroyer
{
private:
	// Vector containing all the garbage to delete
	std::vector<T> garbage;

	// The singleton instance
	static GarbageDestroyer<T>* instance;

	// Default constructor
	GarbageDestroyer()
	{

	}
public:
	// Get the singleton instnace
	static GarbageDestroyer<T>* GetInstance();

	void Destroy(T t_object, function<void(T)> t_destroy_function = nullptr)
	{
		if (t_destroy_function != nullptr)
		{
			t_destroy_function(t_object);
		}

		garbage.push_back(t_object);
	}

	// Delete all registered garbage (only call at the end of the run frame)
	void ClearGarbage()
	{
		if (!garbage.empty())
		{
			delete garbage.back();
			garbage.pop_back(); 
		}
	}
};

//------------------Implementation-------------------//
//Initialize the singleton instance to a nullptr
template<typename T>
GarbageDestroyer<T>* GarbageDestroyer<T>::instance = nullptr;

template<typename T>
GarbageDestroyer<T>* GarbageDestroyer<T>::GetInstance()
{
	// There is no instance so create it
	if (!instance)
	{
		instance = new GarbageDestroyer<T>;
	}

	//Return the singleton instance
	return instance;
}