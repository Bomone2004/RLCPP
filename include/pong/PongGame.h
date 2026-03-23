#pragma once 
#include "core/Game.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"


class PongGame: public Game
{



public:
    PongGame(FVector2 screenSize):Game(screenSize, "Pong")
    {
        //Creare i nostri Gameobject;

        GameObjects.push_back(std::make_unique<Ball>(this, FVector2{33,33}, 15, RAYWHITE, 100));
        GameObjects.push_back(std::make_unique<Paddle>(this,FVector2{ 100, 100}, RAYWHITE, 50, FVector2{30, 120}));
    }

    const InputManager* GetInputManager() const;

    virtual void InitGame() override;

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;
};