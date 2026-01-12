#pragma once

#include "functional"
#include "algorithm"
#include "vector"

template<typename... Args>
class Delegate
{
private:
	std::vector<std::function<void(Args...)>> funcs;
public:
	template<typename T>
	void bind(T* obj, void(T::* func)(Args...))
	{
		funcs.emplace_back([obj, func](Args... args)
			{
				(obj->*func)(args...);
			}
		);
	}
	template<typename T>
	void unbind(T* obj, void(T::*func)(Args...))
	{
		funcs.erase(std::remove(funcs.begin(), funcs.end(), func), funcs.end());
	}
	void invoke(Args... args)
	{
		for (auto& f : funcs)
		{
			f(args...);
		}
	}
};