#include "SceneManager.h"
#include "Scene.h"

namespace SceneManager
{
	std::vector<std::unique_ptr<Scene>> Scenes;

	Scene& CreateScene(const std::string& name)
	{
		Scenes.emplace_back(std::make_unique<Scene>(Scene(name)));
		return *Scenes.back();
	}

	void Update()
	{
		for(auto& scene : Scenes)
		{
			scene->Update();
		}
	}

	void LateUpdate()
	{
		for (auto& scene : Scenes)
		{
			scene->LateUpdate();
		}
	}

	void FixedUpdate()
	{
		for (auto& scene : Scenes)
		{
			scene->FixedUpdate();
		}
	}

	void Render()
	{
		for (auto& scene : Scenes)
		{
			scene->Render();
		}
	}
}