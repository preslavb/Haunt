#ifndef _COROUTINE_MANAGER_H
#define _COROUTINE_MANAGER_H

#include <vector>
#include "Coroutine.h"

//----------------- Declaration ---------------------------//

// Class to manage all coroutines of type T. Needs to be updated seperately for every return type used in the program.
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

	// Remove a coroutine from the manager
	void StopCoroutine(Coroutine<T>* t_coroutine);
};

//----------------- Implementation ------------------------//

// Initialize the instance of the singleton
template<typename T>
CoroutineManager<T>* CoroutineManager<T>::instance = nullptr;

// Constructor
template<typename T>
CoroutineManager<T>::CoroutineManager()
{
}

// Update all coroutines with return type T
template<typename T>
void CoroutineManager<T>::Update()
{
	// Get the first element iterator of the coroutines vector
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

template<typename T>
void CoroutineManager<T>::StopCoroutine(Coroutine<T>* t_coroutine)
{
	// Iterate through the coroutines storage. If the given coroutine is found, erase it from the coroutines vector
	for (vector<Coroutine<T>>::iterator coroutine = coroutinesStorage.begin(); coroutine != coroutinesStorage.end(); ++coroutine)
	{
		if (&(*coroutine) == t_coroutine)
		{
			coroutinesStorage.erase(coroutine);
		}
	}
}

#endif
