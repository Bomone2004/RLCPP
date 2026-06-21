#include "raylib.h"
#include "core/GameObject.h"
#include "core/ColliderComponent.h"

void GameObject::Start()
{
    for (auto& component : components)
    {
        component->Start();
    }
}

void GameObject::Update(float deltaTime)
{
    for (auto& component : components)
    {
        component->Update(deltaTime);
    }
}

void GameObject::Draw()
{
    for (auto& component : components)
    {
        component->Draw();
    }
}

void GameObject::SetPosition(const FVector2& newPos){
    position = newPos;
    if (AIV_Collision::Collider* col = GetCollider())
    {
        col->position = newPos + col->offset;
    }
}

void GameObject::SetVelocity(const FVector2& newVelocity)
{
    velocity = newVelocity;
}
void GameObject::SetActive(bool newState){
    active = newState;
}

void GameObject::OnCollisionEnter(AIV_Collision::FCollisionInfo CollisionInfo)
{
    AIV_Collision::Collider* col = GetCollider();
    if(col != nullptr && col->shouldDrawDebug){
        TraceLog(LOG_WARNING,"Collision Enter");
    }
}
void GameObject::OnCollisionExit(AIV_Collision::FCollisionInfo CollisionInfo){
    AIV_Collision::Collider* col = GetCollider();
    if(col != nullptr && col->shouldDrawDebug){
        TraceLog(LOG_WARNING,"Collision Exit");
    }
}
void GameObject::OnCollisionStay(AIV_Collision::FCollisionInfo CollisionInfo)
{
    AIV_Collision::Collider* col = GetCollider();
    if(col != nullptr && col->shouldDrawDebug){
        TraceLog(LOG_WARNING,"Collision Stay");
    }
}

FVector2 GameObject::GetPosition() const{
    return position;
}
FVector2 GameObject::GetVelocity() const{
    return velocity;
}
AIV_Collision::Collider* GameObject::GetCollider() const
{
    ColliderComponent* colliderComponent = GetComponent<ColliderComponent>();
    return colliderComponent ? colliderComponent->GetCollider() : nullptr;
}

bool GameObject::IsActive()const{
    return active;
}

void GameObject::Destroy(){
    active = false;
}
