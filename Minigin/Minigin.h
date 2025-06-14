#ifndef MINIGIN_H
#define MINIGIN_H


#include <string>
#include <functional>

class Minigin
{
public:
	explicit Minigin(const std::string& dataPath);
	~Minigin() noexcept;
	void Run(const std::function<void()>& load);

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;

private:
	const float m_MaxFps{ 120.f };
	SDL_Window* m_Window{};
};
#endif // !MINIGIN_H
