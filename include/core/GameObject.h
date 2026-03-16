#pragma once

#include "utility/FVector2.h"
//#include <memory>

class Game;

class GameObject{
protected:
    FVector2 position;
    FVector2 velocity;
    //float radius; // TODO: Togliere raggio di collisione e spostarlo in classe a parte (o figlia o altro)
    bool active;
    float speed;    


    Game* game;

public: 
    GameObject(Game* g, FVector2 position = {0,0}, float speed = 0): game(g), position(position),
    velocity(FVector2{0,0}),
    speed(speed),
    active(true){}
    
    virtual ~GameObject(){}

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0; 
    virtual void Draw() = 0;
    //=======Setter=======
    void SetPosition(const FVector2& newPos);
    void SetVelocity(const FVector2& newVelocity);
    void SetActive(bool newState);

    //=======Getter=======
    FVector2 GetPosition() const;
    FVector2 GetVelocity() const;
    bool IsActive()const;


    void Destroy();
};