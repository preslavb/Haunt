#ifndef _COROUTINE_MANAGER_H
#define _COROUTINE_MANAGER_H

#include <vector>
#include "Coroutine.h"

template<typename T>
class CoroutineManager
{
private:
	// The instance of the singleton coroutine manager
	static CoroutineManager<T>* instance;

	// Vector for storing all of the coroutines
	vector<Coroutine<T>> coroutinesStorage;
public:
	// Singleton
	static CoroutineManager<T>* GetInstance();

	// Constructor for the coroutine manager
	CoroutineManager();

	// Update all of the stored coroutines
	static void Update();

	// Add a coroutine to the manager
	static Coroutine<T>* StartCoroutine(Coroutine<T> t_new_coroutine);
};

//----------------- Implementation ------------------------//

template<typename T>
CoroutineManager<T>* CoroutineManager<T>::instance = nullptr;

template<typename T>
CoroutineManager<T>::CoroutineManager()
{

}

template<typename T>
void CoroutineManager<T>::Update()
{
	// Get the first element iterator of the vector
	typename std::vector<Coroutine<T>>::iterator it = CoroutineManager<T>::GetInstance()->coroutinesStorage.begin();

	// Loop through all of the coroutines stored in storage and update them
	while (it != CoroutineManager<T>::GetInstance()->coroutinesStorage.end())
	{
		// If the next loop through the coroutine is the last one and the body is finished, erase it from the vector and use the new iterator provided by vector<T>.erase
		if (! it->Continue())
		{
			it = CoroutineManager<T>::GetInstance()->coroutinesStorage.erase(it);

			break;
		}

		// Otherwise, move on to the next iterator
		++it;
	}
}

// Singleton
template<typename T>
CoroutineManager<T>* CoroutineManager<T>::GetInstance()
{
	if (CoroutineManager<T>::instance == nullptr)
	{
		CoroutineManager<T>::instance = new CoroutineManager<T>();
	}
	return CoroutineManager<T>::instance;
}

template<typename T>
Coroutine<T>* CoroutineManager<T>::StartCoroutine(Coroutine<T> t_new_coroutine)
{
	// Add the coroutine object to the end of the vector
	CoroutineManager<T>::GetInstance()->coroutinesStorage.push_back(std::move(t_new_coroutine));

	// Return a pointer to the newly registered coroutine so that the value can be used by whoever called the coroutine
	return &CoroutineManager<T>::GetInstance()->coroutinesStorage.back();
}

#endif
