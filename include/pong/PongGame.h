#pragma once 
#include "core/Game.h"
#include "core/GameObject.h"
#include "core/InputManager.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"
#include <vector>
#include <memory>

class PongGame: public Game
{

std::unique_ptr<InputManager> inputManager;
std::vector<std::unique_ptr<GameObject>> GameObjects;

public:
    PongGame(FVector2 screenSize):Game(screenSize, "Pong")
    {
        //Creare i nostri Gameobject;

        inputManager = std::make_unique<InputManager>();
        GameObjects.push_back(std::make_unique<Ball>(this, FVector2{33,33}, 5, RAYWHITE, 100));
        GameObjects.push_back(std::make_unique<Paddle>(this,FVector2{ 100, 100}, RAYWHITE, 50, FVector2{10, 40}));
    }

    const InputManager* GetInputManager() const;

    virtual void InitGame() override;

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;
};