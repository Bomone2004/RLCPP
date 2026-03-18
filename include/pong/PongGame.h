#pragma once
#include "core/Game.h"
#include "core/GameObject.h"
#include "pong/TestGO.h"
#include <vector>
#include <memory>
class PongGame: public Game{

std::vector<std::unique_ptr<GameObject>> GameObjects;

Ball* ball;     // Puntatore raw (non owning) alla ball, per accesso diretto alla collisione
Paddle* paddle; // Puntatore raw (non owning) al paddle, per accesso diretto alla collisione

int scoreLeft;  // Punteggio giocatore sinistro
int scoreRight; // Punteggio giocatore destro

public:
    PongGame(FVector2 screenSize):Game(screenSize, "Pong"),
        ball(nullptr), paddle(nullptr), scoreLeft(0), scoreRight(0)
    {
        //Creare i nostri Gameobject;

        inputManager = std::make_unique<InputManager>();
        GameObjects.push_back(std::make_unique<Ball>(this, FVector2{33,33}, 5, RAYWHITE, 100));
        GameObjects.push_back(std::make_unique<Paddle>(this,FVector2{ 100, 100}, RAYWHITE, 50, FVector2{10, 40}));
    }

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

private:
    // Controlla la collisione tra paddle (RectCollider) e ball (CircleCollider)
    void CheckCollisions();
};