#include "pong/PongGame.h"



const InputManager* PongGame::GetInputManager() const
{
    return inputManager.get();
}

FVector2 PongGame::GetBallPosition() const
{
    return ball ? ball->GetPosition() : GetScreenCenter();
}

void PongGame::InitGame()
{
    SetClearColor(BLACK);
    inputManager->BindKey(Action::MOVE_UP, KEY_W);
    inputManager->BindKey(Action::MOVE_DOWN, KEY_S);
    inputManager->BindKey(Action::MOVE_RIGHT, KEY_D);
    inputManager->BindKey(Action::MOVE_LEFT, KEY_A);

    inputManager->BindKey(Action::MOVE_UP_P2, KEY_UP);
    inputManager->BindKey(Action::MOVE_DOWN_P2, KEY_DOWN);
    inputManager->BindKey(Action::MOVE_RIGHT_P2, KEY_RIGHT);
    inputManager->BindKey(Action::MOVE_LEFT_P2, KEY_LEFT);

    inputManager->BindKey(Action::TURBO, KEY_SPACE);
    inputManager->BindKey(Action::TURBO_P2, KEY_RIGHT_SHIFT);

    inputManager->BindKey(Action::UI_UP, KEY_UP);
    inputManager->BindKey(Action::UI_DOWN, KEY_DOWN);
    inputManager->BindKey(Action::UI_CONFIRM, KEY_ENTER);

    inputManager->BindKey(Action::PAUSE, KEY_P);
    inputManager->BindKey(Action::RESTART, KEY_R);

    currentState = GameState::Menu;
}

float PongGame::GetPaddleCenterY(bool leftSide) const
{
    Paddle* paddle = leftSide ? leftPaddle : rightPaddle;
    return paddle ? paddle->GetPosition().y : GetScreenCenter().y;
}

float PongGame::GetPaddleHalfHeight(bool leftSide) const
{
    Paddle* paddle = leftSide ? leftPaddle : rightPaddle;
    return paddle ? paddle->GetHalfHeight() : 60.0f;
}

void PongGame::StartMatch()
{
    ResetMatch();
    currentState = GameState::Game;
}

void PongGame::ResetMatch()
{
    GameObjects.clear();
    collisionManager->Clear();

    P1Points = 0;
    P2Points = 0;

    GameObjects.push_back(std::make_shared<Ball>(this, FVector2{33,33}, 15, RAYWHITE, 350));
    GameObjects.push_back(std::make_shared<Paddle>(this, FVector2{100, 100}, RAYWHITE, 320, FVector2{30, 120}));

    auto paddleTwo = std::make_shared<Paddle>(this, FVector2{ScreenSize.x - 100, 100}, RAYWHITE, 320, FVector2{30, 120}, 1);
    if (mode == GameMode::OnePlayerVsCPU)
    {
        paddleTwo->SetAI(true);
    }
    GameObjects.push_back(paddleTwo);

    GameObjects.push_back(std::make_shared<ScoreUI>(this, FVector2{ScreenSize.x/2, 10}));

    ball = dynamic_cast<Ball*>(GameObjects[0].get());
    leftPaddle = dynamic_cast<Paddle*>(GameObjects[1].get());
    rightPaddle = dynamic_cast<Paddle*>(GameObjects[2].get());

    Game::InitGame();
    NotifyScoreChanged();
}

void PongGame::Update(float DeltaTime)
{
    if (currentState == GameState::Menu)
    {
        inputManager->Update();
        UpdateMenu();
        return;
    }

    if (currentState == GameState::Victory)
    {
        inputManager->Update();
        UpdateVictory();
        return;
    }

    if (currentState == GameState::Pause)
    {
        inputManager->Update();
        UpdatePause();
        return;
    }

    inputManager->Update();

    if (inputManager->GetActionDown(Action::PAUSE))
    {
        pauseSelection = 0;
        currentState = GameState::Pause;
        return;
    }

    if (inputManager->GetActionDown(Action::RESTART))
    {
        ResetMatch();
        return;
    }

    UpdateWorld(DeltaTime);
}

void PongGame::UpdateMenu()
{
    if (inputManager->GetActionDown(Action::UI_DOWN)) menuSelection++;
    if (inputManager->GetActionDown(Action::UI_UP)) menuSelection--;

    if (menuSelection < 0) menuSelection = 0;
    if (menuSelection > 2) menuSelection = 2;

    if (inputManager->GetActionDown(Action::UI_CONFIRM))
    {
        if (menuSelection == 0)
        {
            mode = GameMode::TwoPlayers;
            StartMatch();
        }
        else if (menuSelection == 1)
        {
            mode = GameMode::OnePlayerVsCPU;
            StartMatch();
        }
        else
        {
            Quit();
        }
    }
}

void PongGame::UpdateVictory()
{
    if (inputManager->GetActionDown(Action::UI_DOWN)) victorySelection++;
    if (inputManager->GetActionDown(Action::UI_UP)) victorySelection--;

    if (victorySelection < 0) victorySelection = 0;
    if (victorySelection > 2) victorySelection = 2;

    if (inputManager->GetActionDown(Action::UI_CONFIRM))
    {
        if (victorySelection == 0)
        {
            menuSelection = 0;
            currentState = GameState::Menu;
        }
        else if (victorySelection == 1)
        {
            StartMatch();
        }
        else
        {
            Quit();
        }
    }
}

void PongGame::UpdatePause()
{
    if (inputManager->GetActionDown(Action::PAUSE))
    {
        currentState = GameState::Game;
        return;
    }

    if (inputManager->GetActionDown(Action::RESTART))
    {
        ResetMatch();
        currentState = GameState::Game;
        return;
    }

    if (inputManager->GetActionDown(Action::UI_DOWN)) pauseSelection++;
    if (inputManager->GetActionDown(Action::UI_UP)) pauseSelection--;

    if (pauseSelection < 0) pauseSelection = 0;
    if (pauseSelection > 3) pauseSelection = 3;

    if (inputManager->GetActionDown(Action::UI_CONFIRM))
    {
        if (pauseSelection == 0)
        {
            currentState = GameState::Game;
        }
        else if (pauseSelection == 1)
        {
            ResetMatch();
            currentState = GameState::Game;
        }
        else if (pauseSelection == 2)
        {
            menuSelection = 0;
            currentState = GameState::Menu;
        }
        else
        {
            Quit();
        }
    }
}

void PongGame::Draw()
{
    if (currentState == GameState::Menu)
    {
        DrawMenu();
        return;
    }

    if (currentState == GameState::Victory)
    {
        DrawVictory();
        return;
    }

    if (currentState == GameState::Pause)
    {
        DrawPause();
        return;
    }

    Game::Draw();
}

void PongGame::DrawPause()
{
    BeginDrawing();
    ClearBackground(clearColor);

    const char* title = "PAUSED";
    DrawText(title, ScreenSize.x*0.5f - MeasureText(title, 70)/2, ScreenSize.y*0.15f, 70, RAYWHITE);

    const char* items[] = {"RESUME", "RESTART", "MENU", "QUIT"};
    for (int i = 0; i < 4; ++i)
    {
        Color color = (i == pauseSelection) ? YELLOW : GRAY;
        DrawText(items[i], ScreenSize.x*0.5f - MeasureText(items[i], 35)/2, ScreenSize.y*0.42f + i*55, 35, color);
    }

    const char* hint = "P to resume, R to restart";
    DrawText(hint, ScreenSize.x*0.5f - MeasureText(hint, 20)/2, ScreenSize.y*0.9f, 20, DARKGRAY);

    EndDrawing();
}

void PongGame::DrawMenu()
{
    BeginDrawing();
    ClearBackground(clearColor);

    const char* title = "PONG";
    DrawText(title, ScreenSize.x*0.5f - MeasureText(title, 90)/2, ScreenSize.y*0.18f, 90, RAYWHITE);

    const char* items[] = {"2 PLAYERS", "1 VS CPU", "QUIT"};
    for (int i = 0; i < 3; ++i)
    {
        Color color = (i == menuSelection) ? YELLOW : GRAY;
        DrawText(items[i], ScreenSize.x*0.5f - MeasureText(items[i], 40)/2, ScreenSize.y*0.45f + i*60, 40, color);
    }

    const char* hint = "Arrows to choose, Enter to confirm";
    DrawText(hint, ScreenSize.x*0.5f - MeasureText(hint, 20)/2, ScreenSize.y*0.9f, 20, DARKGRAY);

    EndDrawing();
}

void PongGame::DrawVictory()
{
    BeginDrawing();
    ClearBackground(clearColor);

    const char* winner = (P1Points > P2Points) ? "PLAYER 1 WINS" : "PLAYER 2 WINS";
    DrawText(winner, ScreenSize.x*0.5f - MeasureText(winner, 50)/2, ScreenSize.y*0.18f, 50, RAYWHITE);

    const char* score = TextFormat("%d - %d", P1Points, P2Points);
    DrawText(score, ScreenSize.x*0.5f - MeasureText(score, 40)/2, ScreenSize.y*0.32f, 40, RAYWHITE);

    const char* items[] = {"MENU", "PLAY AGAIN", "QUIT"};
    for (int i = 0; i < 3; ++i)
    {
        Color color = (i == victorySelection) ? YELLOW : GRAY;
        DrawText(items[i], ScreenSize.x*0.5f - MeasureText(items[i], 40)/2, ScreenSize.y*0.5f + i*60, 40, color);
    }

    EndDrawing();
}

int PongGame::GetPoints(int playerIndex) const {
    return (playerIndex==0)?P1Points:P2Points;
}

void PongGame::ScorePoints(int playerIndex)
{
    if(playerIndex == 0){
        P1Points++;
    }
    else{
        P2Points++;
    }

    NotifyScoreChanged();

    if(P1Points >= winScore || P2Points >= winScore){
        NotifyGameEnd();
    }
}

void PongGame::SetScoreDelegate(ScoreDelegate delegate)
{
    onScoreChanged = std::move(delegate);
}

void PongGame::NotifyGameEnd(){
    currentState = GameState::Victory;
    victorySelection = 0;
}
void PongGame::NotifyScoreChanged()
{
    if (onScoreChanged)
    {
        onScoreChanged(P1Points, P2Points);
    }
}
