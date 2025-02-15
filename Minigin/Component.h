#pragma once
class Component
{
public:
	virtual ~Component() = default;


	virtual void Render() const {};
	virtual void Update() {};
	virtual void FixedUpdate() {};
};
