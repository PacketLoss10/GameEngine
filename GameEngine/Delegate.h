#pragma once

template<typename T, typename... Args>
class Delegate
{
private:
	T* object = nullptr;
	void(T::* function)(Args...) = nullptr;
public:
	void bind(T* obj, void(T::* func)(Args...))
	{
		object = obj;
		function = func;
	}
	void invoke(Args... args)
	{
		if (object && function)
			(object->*function)(args...);
	}
};