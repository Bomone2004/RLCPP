#include "pong/Paddle.h"
#include "core/InputManager.h"
#include "pong/PongGame.h"

void Paddle::SetAI(bool enabled)
{
    aiControlled = enabled;
}

void Paddle::Start()
{
    Up = (playerIndex==0)?Action::MOVE_UP:Action::MOVE_UP_P2;
    Down= (playerIndex==0)?Action::MOVE_DOWN:Action::MOVE_DOWN_P2;
    Turbo = (playerIndex==0)?Action::TURBO:Action::TURBO_P2;
    GameObject::Start();
}

void Paddle::Update(float deltaTime)
{
    if (!game) return;

    if (aiControlled)
    {
        UpdateAI(deltaTime);
    }
    else
    {
        UpdatePlayer(deltaTime);
    }

    GameObject::Update(deltaTime);
}

void Paddle::UpdatePlayer(float deltaTime)
{
    const InputManager* inputManager = dynamic_cast<PongGame*>(game)->GetInputManager();

    velocity = {0, 0};

    if (inputManager->GetActionState(Up) && GetPosition().y - Bounds.y/2 > 0)
    {
        velocity.y = -1;
    }
    else if (inputManager->GetActionState(Down) && GetPosition().y + Bounds.y/2 < game->GetScreenSize().y)
    {
        velocity.y = 1;
    }

    float effectiveSpeed = inputManager->GetActionState(Turbo) ? speed * turboMultiplier : speed;

    SetPosition(position + velocity.Nomalized() * effectiveSpeed * deltaTime);
}

void Paddle::UpdateAI(float deltaTime)
{
    FVector2 ballPosition = dynamic_cast<PongGame*>(game)->GetBallPosition();
    float deadZone = 10.0f;

    velocity = {0, 0};

    if (ballPosition.y < GetPosition().y - deadZone && GetPosition().y - Bounds.y/2 > 0)
    {
        velocity.y = -1;
    }
    else if (ballPosition.y > GetPosition().y + deadZone && GetPosition().y + Bounds.y/2 < game->GetScreenSize().y)
    {
        velocity.y = 1;
    }

    SetPosition(position + velocity.Nomalized() * speed * deltaTime);
}

void Paddle::Draw()
{
    GameObject::Draw();
    DrawRectangle(position.x+pivotOffset.x, position.y +pivotOffset.y, Bounds.x,Bounds.y, ObjColor);
}
