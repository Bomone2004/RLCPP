#pragma once 
#include "core/GameObject.h"


class ScoreUI : public GameObject{

    int scoreLeft;
    int scoreRight;
public:
    ScoreUI(Game* g, FVector2 position = {0,0}):GameObject(g, position,0), scoreLeft(0), scoreRight(0){}

    virtual void Start() override;
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override; 
    
};
