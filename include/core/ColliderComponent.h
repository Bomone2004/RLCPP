#pragma once
#include "core/Component.h"
#include "core/Collider.h"
#include "utility/FVector2.h"
#include <memory>

class ColliderComponent : public Component
{
    std::shared_ptr<AIV_Collision::Collider> collider;

public:
    ColliderComponent(GameObject* owner, std::shared_ptr<AIV_Collision::Collider> col, FVector2 offset = {0, 0});

    AIV_Collision::Collider* GetCollider() const;

    virtual void Start() override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};
