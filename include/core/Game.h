#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <memory>
#include "utility/FVector2.h"
#include "core/Collider.h"
#include "core/GameObject.h"
#include "core/InputManager.h"
#include "core/CollisionManager.h"

class Game
{
    //width, height FVector2
    //titolo string
    protected:
    FVector2 ScreenSize;
    std::string Title;
    bool shouldClose;
    Color clearColor;

    std::unique_ptr<InputManager>inputManager;
    std::unique_ptr<CollisionManager> collisionManager;
    std::vector<std::shared_ptr<GameObject>> GameObjects;

    public:
    
    Game(FVector2 screenSize, const std::string& title) : ScreenSize(screenSize), Title(title), shouldClose(false), clearColor(RAYWHITE)
    {
        inputManager = std::make_unique<InputManager>();
        collisionManager = std::make_unique<CollisionManager>();
        InitWindow(ScreenSize.x, ScreenSize.y, Title.c_str());
        SetTargetFPS(60);
    };

    ~Game()
    {
        CloseWindow();
    }
    Game(const Game& other) = delete;
    Game& operator= (const Game& other) = delete;

    void Run();
    void Quit();
    void SetClearColor(Color cl);
    virtual void InitGame();
    protected:
    virtual void Update(float DeltaTime);
    virtual void Draw();
    

    public:
    FVector2 GetScreenSize() const;
};
