#pragma once
#include "core/GameObject.h"
#include "core/InputAction.hpp"

class Paddle : public GameObject
{
    Color ObjColor;
    FVector2 Bounds;
    int playerIndex;
    Action Up;   
    Action Down; 
public:
    Paddle(Game* g, FVector2 Pos, Color c, float speed, FVector2 bounds, int pi = 0 ):GameObject(g, Pos, speed),ObjColor(c), Bounds(bounds), playerIndex(pi)
    {
        collider = std::make_shared<AIV_Collision::RectCollider>(Bounds);
        collider->position = position ;
        pivotOffset = FVector2(-Bounds.x/2, -Bounds.y/2);
        collider->offset = pivotOffset;
        collider->shouldDrawDebug = false;
        
    }

    ~Paddle(){}

    virtual void Start() override;
    virtual void Update(float DeltaTime) override; 
    virtual void Draw() override;
};