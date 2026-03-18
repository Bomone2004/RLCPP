#pragma once
#include "core/GameObject.h"

class Paddle : public GameObject
{
    Color ObjColor;
    FVector2 Bounds;

public:
    Paddle(Game* g, FVector2 Pos, Color c, float speed, FVector2 bounds):GameObject(g, Pos, speed),ObjColor(c), Bounds(bounds){}
    ~Paddle(){}

    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

    FVector2 GetBounds() const { return Bounds; } // Getter per costruire il RectCollider (w, h)
};