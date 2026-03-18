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

// Trasferisce la ownership del componente al vector interno tramite std::move
void GameObject::AddComponent(std::unique_ptr<Component> comp){
    components.push_back(std::move(comp));
}

// Itera su tutti i componenti e chiama il loro Update
void GameObject::UpdateComponents(float deltaTime){
    for(auto& c : components){
        c->Update(deltaTime);
    }
}

// Itera su tutti i componenti e chiama il loro Draw
void GameObject::DrawComponents(){
    for(auto& c : components){
        c->Draw();
    }
}