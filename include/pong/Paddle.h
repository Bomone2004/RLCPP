#pragma once
#include "core/GameObject.h"

class Paddle : public GameObject
{
    Color ObjColor;
    FVector2 Bounds;

public:
    Paddle(Game* g, FVector2 Pos, Color c, float speed, FVector2 bounds):GameObject(g, Pos, speed),ObjColor(c), Bounds(bounds)
    {
        collider = std::make_shared<AIV_Collision::RectCollider>(bounds);
        collider->position = position;
        
    }

    ~Paddle(){}

    virtual void Start() override;
    virtual void Update(float DeltaTime) override; 
    virtual void Draw() override;
};