#pragma once
#include "raylib.h"
#include <string>
#include "utility/FVector2.h"

class Game
{
    //width, height FVector2
    //titolo string
    private:
    FVector2 ScreenSize;
    std::string Title;
    bool shouldClose;
    Color clearColor;

    public:
    
    Game(FVector2 screenSize, const std::string& title) : ScreenSize(screenSize), Title(title), shouldClose(false), clearColor(RAYWHITE)
    {
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
    virtual void InitGame() = 0;
    protected:
    virtual void Update(float DeltaTime);
    virtual void Draw();

    public:
    FVector2 GetScreenSize() const;
};
