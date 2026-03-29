#pragma once 
#include "core/Game.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"
#include "pong/ScoreUI.h"
#include <functional>

class PongGame: public Game
{

    int P1Points;
    int P2Points;

public:
    PongGame(FVector2 screenSize):Game(screenSize, "Pong")
    {
        //Creare i nostri Gameobject;

        GameObjects.push_back(std::make_unique<Ball>(this, FVector2{33,33}, 15, RAYWHITE,200));
        GameObjects.push_back(std::make_unique<Paddle>(this,FVector2{ 100, 100}, BLUE , 150, FVector2{30, 120}));
        //Player 2, controllato con le freccine (oppure I e K )
        GameObjects.push_back(std::make_unique<Paddle>(this,FVector2{ ScreenSize.x - 100, 100}, ORANGE , 150, FVector2{30, 120},1)); 
        GameObjects.push_back(std::make_unique<ScoreUI>(this,FVector2{ screenSize.x/2, 10} ));
   
    }
   

    const InputManager* GetInputManager() const;

    virtual void InitGame() override;

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

    int GetPoints(int playerIndex) const;

    void ScorePoints(int playerIndex);
    //SCORE DELEGTATE PART
    using ScoreDelegate = std::function<void(int leftScore, int rightScore)>;
    void SetScoreDelegate(ScoreDelegate delegate);
private:
    //SCORE DELEGTATE PART
    void NotifyScoreChanged();
    ScoreDelegate onScoreChanged;

};