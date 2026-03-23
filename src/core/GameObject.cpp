#include "raylib.h"
#include "core/GameObject.h"
#include<iostream>
#include<stdio.h>

void GameObject::SetPosition(const FVector2& newPos){
    position = newPos;
    if(GetCollider())
    {
        collider->position = newPos + collider->offset;
    
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
    if(collider->shouldDrawDebug){
        TraceLog(LOG_WARNING,"Collision Enter");
    }


}
void GameObject::OnCollisionExit(AIV_Collision::FCollisionInfo CollisionInfo){
    if(collider->shouldDrawDebug){
        TraceLog(LOG_WARNING,"Collision Exit");
    }
}
void GameObject::OnCollisionStay(AIV_Collision::FCollisionInfo CollisionInfo)
{
    if(collider->shouldDrawDebug){
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
    return collider.get();
}

bool GameObject::IsActive()const{
    return active;
}

void GameObject::Destroy(){
    active = false;
}

void GameObject::Draw(){
    collider->DrawDebug();
}