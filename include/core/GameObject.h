#pragma once

#include "utility/FVector2.h"
#include "core/Collider.h"
#include <memory>

class Game;

class GameObject{
protected:
    FVector2 position;
    FVector2 velocity;
    FVector2 pivotOffset;
    bool active;
    float speed;    

    std::shared_ptr<AIV_Collision::Collider> collider;

    Game* game;

public: 
    GameObject(Game* g, FVector2 position = {0,0}, float speed = 0): game(g), position(position),
    velocity(FVector2{0,0}),
    speed(speed),
    active(true){}
    
    virtual ~GameObject(){}

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0; 
    virtual void Draw();

    virtual void OnCollisionEnter(AIV_Collision::FCollisionInfo CollisionInfo);
    virtual void OnCollisionExit(AIV_Collision::FCollisionInfo CollisionInfo);
    virtual void OnCollisionStay(AIV_Collision::FCollisionInfo CollisionInfo);


    //=======Setter=======
    void SetPosition(const FVector2& newPos);
    void SetVelocity(const FVector2& newVelocity);
    void SetActive(bool newState);

    //=======Getter=======
    FVector2 GetPosition() const;
    FVector2 GetVelocity() const;
    
    AIV_Collision::Collider* GetCollider() const;

    bool IsActive()const;


    void Destroy();
};