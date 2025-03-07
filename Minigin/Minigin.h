#pragma once
#include <string>
#include <functional>
#include <chrono>


class Minigin
{
public:
	explicit Minigin(const std::string& dataPath);
	~Minigin();
	void Run(const std::function<void()>& load);

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;

private:
	const std::chrono::milliseconds m_MsPerFrame;
};
