#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "GameObject.h"

class Scene;

namespace SceneManager
{
	Scene& CreateScene(const std::string& name);

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render();
}
#endif // !SCENEMANAGER_H