#ifndef EVENT_H
#define EVENT_H
#include <vector>
#include <functional>
#include <algorithm>

template<class... ArgsTypes>
class Event
{
public:
	void BindFunction(const std::function<void(ArgsTypes...)>& function)
	{
		m_Function = function;
	}

	void Broadcast(ArgsTypes... args)
	{
		m_Function(args...);
	}

private:
	std::function<void(ArgsTypes...)> m_Function{};
};


template<class... ArgsTypes>
class MulticastEvent
{
public:
	void BindFunction(const std::function<void(ArgsTypes...)>& function)
	{
		m_Functions.push_back(function);
	}

	void Broadcast(ArgsTypes... args)
	{
		std::for_each(m_Functions.begin(), m_Functions.end(), [&args...](const std::function<void(ArgsTypes...)>& function) {function(args...); });
	}
private:
	std::vector<std::function<void(ArgsTypes...)>> m_Functions{};
};
#endif // !EVENT_H

//TODO consider cleanup after bound object gets deleted

