#pragma once

class GameObject;

class Component
{
protected:
    GameObject* owner;

public:
    Component(GameObject* owner) : owner(owner) {}
    virtual ~Component() = default;

    virtual void Start() {}
    virtual void Update(float deltaTime) {}
    virtual void Draw() {}
};
