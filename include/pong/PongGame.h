#pragma once 
#include "core/Game.h"
#include "core/GameObject.h"
#include "pong/TestGO.h"
#include <vector>
#include <memory>
class PongGame: public Game{

std::vector<std::unique_ptr<GameObject>> GameObjects;

public:
    PongGame(FVector2 screenSize):Game(screenSize, "Pong")
    {
        //Creare i nostri Gameobject;

        GameObjects.push_back(std::make_unique<TestGameObject>(FVector2{33,33}, 5, RAYWHITE));
    }

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;
};