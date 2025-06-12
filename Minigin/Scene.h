#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"

class Scene final
{
public:
	explicit Scene(std::uint64_t id);
	void Add(std::unique_ptr<GameObject> object);
	void Remove(std::unique_ptr<GameObject> object);
	void RemoveAll();

	std::uint64_t GetId() const { return m_Id; };

	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render() const;

	~Scene() noexcept;
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) noexcept;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private: 
	void DeleteObjects();

	std::vector<std::unique_ptr<GameObject>> m_Objects{};

	const std::uint64_t m_Id;
};
#endif // !SCENE_H


