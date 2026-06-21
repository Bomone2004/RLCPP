#include "core/ColliderComponent.h"
#include "core/GameObject.h"

ColliderComponent::ColliderComponent(GameObject* owner, std::shared_ptr<AIV_Collision::Collider> col, FVector2 offset)
    : Component(owner), collider(col)
{
    collider->offset = offset;
    collider->position = owner->GetPosition() + offset;
}

AIV_Collision::Collider* ColliderComponent::GetCollider() const
{
    return collider.get();
}

void ColliderComponent::Start()
{
    collider->position = owner->GetPosition() + collider->offset;
}

void ColliderComponent::Update(float deltaTime)
{
    collider->position = owner->GetPosition() + collider->offset;
}

void ColliderComponent::Draw()
{
    collider->DrawDebug();
}
