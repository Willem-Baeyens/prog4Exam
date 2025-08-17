#ifndef MINIGIN_H
#define MINIGIN_H


#include <string>
#include <functional>

struct SDL_Window;

class Minigin
{
public:
	explicit Minigin(const std::string& dataPath,int screenWidth, int screenHeight,float renderScale);
	~Minigin() noexcept;
	void Run(const std::function<void()>& load);

	void Pause();

	Minigin(const Minigin& other) = delete;
	Minigin(Minigin&& other) = delete;
	Minigin& operator=(const Minigin& other) = delete;
	Minigin& operator=(Minigin&& other) = delete;

private:
	const float m_MaxFps{ 120.f };
	SDL_Window* m_Window{};
	bool m_Continue{ true };
};
#endif // !MINIGIN_H
