#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>

class Scene;
namespace SceneManager
{
	Scene& CreateScene(std::uint64_t id);

	void SetActiveScene(Scene* scene);
	void SetActiveScene(std::uint64_t id);
	Scene* GetScene(std::uint64_t id);

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render();
}
#endif // !SCENEMANAGER_H