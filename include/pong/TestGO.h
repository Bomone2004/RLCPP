#pragma once
#include "core/GameObject.h"
#include "raylib.h"

class TestGameObject: public GameObject
{

    Color ObjColor;
public:
    TestGameObject(Game* g, FVector2 Pos, float radius, Color c):GameObject(g, Pos, radius),ObjColor(c){}
    ~TestGameObject(){}

    virtual void Update(float DeltaTime) override; 
    virtual void Draw() override;
};