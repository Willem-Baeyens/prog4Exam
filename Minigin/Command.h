#pragma once
#include <iostream>
#include <glm.hpp>

class GameObject;
class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class GameObjectCommand : public Command
{
public:
	GameObjectCommand(GameObject* gameObject);
	virtual ~GameObjectCommand() = default;
protected:
	GameObject* GetGameObject() const;
private:
	GameObject* m_GameObject;
};

class Move final : public GameObjectCommand
{
public:
	Move(GameObject* gameObject);
	Move(GameObject* gameObject, glm::vec3 direction = glm::vec3{1,0,0}, float speed = 10);

	virtual void Execute() override;
private:
	glm::vec3 m_Direction{ 0,0,0 };
	float m_Speed{ 0 };
};

