#pragma once
#include "core/GameObject.h"
#include "core/ColliderComponent.h"
#include "core/InputAction.hpp"

class Paddle : public GameObject
{
    Color ObjColor;
    FVector2 Bounds;
    int playerIndex;
    bool aiControlled;
    float turboMultiplier;
    float aiDelayTimer;
    float aiStartDelay;
    Action Up;
    Action Down;
    Action Turbo;
public:
    Paddle(Game* g, FVector2 Pos, Color c, float speed, FVector2 bounds, int pi = 0 ):GameObject(g, Pos, speed),ObjColor(c), Bounds(bounds), playerIndex(pi), aiControlled(false), turboMultiplier(2.0f), aiDelayTimer(0.0f), aiStartDelay(0.5f)
    {
        pivotOffset = FVector2(-Bounds.x/2, -Bounds.y/2);
        ColliderComponent* colliderComponent = AddComponent<ColliderComponent>(std::make_shared<AIV_Collision::RectCollider>(Bounds), pivotOffset);
        colliderComponent->GetCollider()->shouldDrawDebug = false;
    }

    ~Paddle(){}

    void SetAI(bool enabled);
    void ResetAIDelay();
    float GetHalfHeight() const { return Bounds.y / 2.0f; }

    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

private:
    void UpdatePlayer(float deltaTime);
    void UpdateAI(float deltaTime);
};
