#include "Scene.h"
#include "GameObject.h"
#include <algorithm>



Scene::Scene(std::uint64_t id) :m_Id{ id } {}

void Scene::DeleteObjects()
{
	std::erase_if(m_Objects, [](const std::unique_ptr<GameObject>& object) {return object->IsFlaggedForDeletion(); });
}

Scene::~Scene() noexcept = default;

Scene::Scene(Scene&& other) noexcept :
	m_Objects{std::move(other.m_Objects)},m_Id{other.m_Id}
{
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject> object)
{
	std::for_each(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end(), 
		[](std::unique_ptr<GameObject>& object) {object->FlagForDeletion(); });
}

void Scene::RemoveAll()
{
	std::for_each(m_Objects.begin(), m_Objects.end(),
		[](std::unique_ptr<GameObject>& object) {object->FlagForDeletion(); });
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
	DeleteObjects();
}

void Scene::FixedUpdate()
{
	for (auto& object : m_Objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

