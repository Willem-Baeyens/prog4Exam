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

class Move : GameObjectCommand
{
public:
	virtual void Execute() override;

private:
	glm::vec3 m_Direction{ 1,0,0 };
	float m_Speed{ 10 };
};

