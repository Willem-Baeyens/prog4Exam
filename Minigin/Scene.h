#ifndef SCENE_H
#define SCENE_H

#include "SceneManager.h"


class GameObject;
class Scene final
{
public:
	explicit Scene(const std::string& name);
	void Add(std::unique_ptr<GameObject> object);
	void Remove(std::unique_ptr<GameObject> object);
	void RemoveAll();

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) noexcept;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 

	void DeleteObjects();

	std::string m_Name;
	std::vector<std::unique_ptr<GameObject>> m_Objects{};

	static unsigned int m_IdCounter; 
};
#endif // !SCENE_H


