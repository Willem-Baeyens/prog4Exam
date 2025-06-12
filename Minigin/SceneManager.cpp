#include "SceneManager.h"
#include <vector>
#include "Scene.h"
#include <memory>
#include <stdexcept>

namespace SceneManager
{
	std::vector<std::unique_ptr<Scene>> Scenes;
	Scene* ActiveScene{nullptr};

	Scene& CreateScene(std::uint64_t id)
	{
		Scenes.emplace_back(std::make_unique<Scene>(Scene(id)));
		if (!ActiveScene)
		{
			SetActiveScene(Scenes.back().get());
		}
		return *Scenes.back();
	}


	void SetActiveScene(Scene* scene)
	{
		assert(scene);
		ActiveScene = scene;
	}

	void SetActiveScene(std::uint64_t id)
	{ 
		auto scene{ GetScene(id) };
		if (scene)
		{
			SetActiveScene(scene);
		}
	}

	Scene* GetScene(std::uint64_t id)
	{
		auto matchingIterator{ std::find_if(Scenes.begin(),Scenes.end(),[id](const std::unique_ptr<Scene>& scene) {return scene->GetId() == id; }) };
		if (matchingIterator != Scenes.end())
		{
			return matchingIterator->get();
		}
		else return nullptr;
	}

	void Update()
	{
		ActiveScene->Update();
	}
	
	void LateUpdate()
	{
		ActiveScene->LateUpdate();
	}
	
	void FixedUpdate()
	{
		ActiveScene->FixedUpdate();
	}
	
	void Render()
	{
		ActiveScene->Render();
	}
}