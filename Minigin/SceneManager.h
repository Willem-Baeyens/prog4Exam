#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include "GameObject.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render();
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_scenes;
};
#endif // !SCENEMANAGER_H