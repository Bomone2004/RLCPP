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

        // Creiamo i gameobject e salviamo i puntatori raw prima di trasferire la ownership al vector
        auto b = std::make_unique<Ball>(this, FVector2{33,33}, 5, RAYWHITE, 100);
        auto p = std::make_unique<Paddle>(this,FVector2{ 100, 100}, RAYWHITE, 50, FVector2{10, 40});

        ball = b.get();   // Salviamo il raw pointer prima del move
        paddle = p.get(); // Salviamo il raw pointer prima del move

        GameObjects.push_back(std::move(b));  // Trasferimento ownership
        GameObjects.push_back(std::move(p));  // Trasferimento ownership
    }

    virtual void Update(float DeltaTime) override;
    virtual void Draw() override;

private:
    // Controlla la collisione tra paddle (RectCollider) e ball (CircleCollider)
    void CheckCollisions();
};