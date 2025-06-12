#ifndef COMMAND_H
#define COMMAND_H


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
	explicit GameObjectCommand(GameObject* gameObject);
	virtual ~GameObjectCommand() = default;
protected:
	GameObject* GetGameObject() const;
private:
	GameObject* m_GameObject;
};

class Move final : public GameObjectCommand
{
public:
	explicit Move(GameObject* gameObject);
	Move(GameObject* gameObject, glm::vec2 direction = glm::vec2{1.f,0.f}, float speed = 10.f);

	virtual void Execute() override;
private:
	glm::vec2 m_Direction{ 1.f,0.f };
	float m_Speed{ 0.f };
}; 
#endif // !COMMAND_H

