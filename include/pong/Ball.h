#pragma once
#include "core/GameObject.h"
#include "raylib.h"

class Ball : public GameObject
{
    Color ObjColor;
    float radius;

public:
    Ball(Game* g, FVector2 Pos, float radius, Color c, float speed):GameObject(g, Pos,speed),ObjColor(c), radius(radius)
    {
        collider = std::make_shared<AIV_Collision::CircleCollider>(radius);
        collider->position = position;

    }
    ~Ball(){}

    virtual void Start() override;
    virtual void Update(float DeltaTime) override; 
    virtual void Draw() override;

protected:
    void ChangeColor();
};