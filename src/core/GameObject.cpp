#include "raylib.h"
#include "core/GameObject.h"

void GameObject::SetPosition(const FVector2& newPos){
    position = newPos;
}

void GameObject::SetVelocity(const FVector2& newVelocity)
{
    velocity = newVelocity;
}
void GameObject::SetRadius(float newRadius){
    radius = newRadius;
}
void GameObject::SetActive(bool newState){
    active = newState;
}


FVector2 GameObject::GetPosition() const{
    return position;
}
FVector2 GameObject::GetVelocity() const{
    return velocity;
}
float GameObject::GetRadius() const{
    return radius;
}
bool GameObject::IsActive()const{
    return active;
}

void GameObject::Destroy(){
    active = false;
}