#ifndef _COROUTINE_H
#define _COROUTINE_H

#include <experimental\resumable>
#include <iso646.h>

// Template specifying what type of value we are going to be returning
template<typename T>
// A coroutine to update every frame from the CoroutineManager
struct Coroutine
{
	// The promise for a value
	struct promise_type
	{
		// The current calculated value
		T CurrentValue;

		// Constructor and destructor for the promise
		promise_type()
		{
		}
		~promise_type()
		{
		}

		// What to do when first entering the body
		auto initial_suspend()
		{
			return std::experimental::suspend_always{};
		}

		// What to do when the coroutine has finished execution of the body
		auto final_suspend()
		{
			return std::experimental::suspend_always{};
		}

		// When asked for a value, return a Coroutine object with the current state of the promise
		auto get_return_object()
		{
			return Coroutine{ handle_type::from_promise(*this) };
		}

		// Yield a value and suspend the execution of the body
		auto yield_value(T t_value)
		{
			CurrentValue = t_value;
			return std::experimental::suspend_always{};
		}

		// Return a value and suspend the execution of the body
		auto return_value(T t_value)
		{
			return std::experimental::suspend_never{};
		}

		// What to do if we encounter an exception
		void unhandled_exception()
		{
			std::exit(1);
		}
	};
	// A handler to store the state of the promise on suspension
	using handle_type =	std::experimental::coroutine_handle<promise_type>;
public:
	// Constructor for the coroutine object and the state handler instance
	Coroutine(handle_type h)
		: Instance(h)
	{
	}
	handle_type Instance;

	// Coroutine object destructor
	~Coroutine()
	{
		if (Instance) Instance.destroy();
	}

	// Set the coroutine to a non-copyable, movable object
	Coroutine(const Coroutine &) = delete;
	Coroutine(Coroutine &&g) : Instance(g.Instance)
	{
		g.Instance = nullptr;
	};

	Coroutine& operator = (const Coroutine &) = delete;
	Coroutine& operator = (Coroutine&& t_other)
	{
		Instance = t_other.Instance;

		t_other.Instance = nullptr;

		return *this;
	}

	// The value of the current yield/return
	T CurrentValue()
	{
		return Instance.promise().CurrentValue;
	}

	// Continue with the execution of the coroutine
	bool Continue()
	{
		// If the coroutine body hasn't finished executing, continue suspending and resuming
		if (not Instance.done())
		{
			Instance.resume();
			auto still_going = not Instance.done();
			return still_going;
		}
		else
		{
			return false;
		}
	}
};

#endif
