#pragma once 
#include "core/Game.h"
#include "core/GameObject.h"
#include "core/InputManager.h"
#include "pong/TestGO.h"
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
        GameObjects.push_back(std::make_unique<TestGameObject>(this, FVector2{33,33}, 5, RAYWHITE));
    }

    const InputManager* GetInputManager() const;

    virtual void InitGame() override;

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;
};