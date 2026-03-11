#pragma once
#include "utility/FVector2.h"

class GameObject{
protected:
    FVector2 position;
    FVector2 velocity;
    float radius; // TODO: Togliere raggio di collisione e spostarlo in classe a parte (o figlia o altro)
    bool active;

public: 
    GameObject(FVector2 position = {0,0}, float radius =0):position(position),
    velocity(FVector2{0,0}),
    radius(radius),
    active(true){}
    
    virtual ~GameObject(){}

    virtual void Update(float deltaTime) = 0; 
    virtual void Draw() = 0;
    //=======Setter=======
    void SetPosition(const FVector2& newPos);
    void SetVelocity(const FVector2& newVelocity);
    void SetRadius(float newRadius);
    void SetActive(bool newState);

    //=======Getter=======
    FVector2 GetPosition() const;
    FVector2 GetVelocity() const;
    float GetRadius() const;
    bool IsActive()const;


    void Destroy();

    bool CheckCollision(const GameObject& other) const; // TODO: Se togliamo il raggio, spostare codice per collisione
};