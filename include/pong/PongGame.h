#pragma once
#include "core/Game.h"
#include "pong/Ball.h"
#include "pong/Paddle.h"
#include "pong/ScoreUI.h"
#include <functional>

enum class GameState
{
    Menu,
    Game,
    Victory
};

enum class GameMode
{
    TwoPlayers,
    OnePlayerVsCPU
};

class PongGame: public Game
{

    int P1Points;
    int P2Points;
    const int winScore = 5;

    GameState currentState;
    GameMode mode;
    int menuSelection;
    int victorySelection;

    Ball* ball;

public:
    std::function<void(int, int)> ScoreChangeDelegate;

public:
    PongGame(FVector2 screenSize):Game(screenSize, "Pong")
    {
        P1Points = 0;
        P2Points = 0;
        currentState = GameState::Menu;
        mode = GameMode::TwoPlayers;
        menuSelection = 0;
        victorySelection = 0;
        ball = nullptr;
    }


    const InputManager* GetInputManager() const;
    FVector2 GetBallPosition() const;

    virtual void InitGame() override;
    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

    int GetPoints(int playerIndex) const;

    void ScorePoints(int playerIndex);

    using ScoreDelegate= std::function<void(int leftScore, int rightScore)>;
    using GameOverDelegate = std::function<void()>;
    void SetScoreDelegate(ScoreDelegate delegate);
private:
    void StartMatch();
    void ResetMatch();

    void UpdateMenu();
    void UpdateVictory();
    void DrawMenu();
    void DrawVictory();

    void NotifyGameEnd();
    void NotifyScoreChanged();
    ScoreDelegate onScoreChanged;
    GameOverDelegate onGameEnd;

};
