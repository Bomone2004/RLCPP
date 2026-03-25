#include "pong/Paddle.h"
#include "core/InputManager.h"
#include "pong/PongGame.h"

void Paddle::Start()
{
    Up = (playerIndex==0)?Action::MOVE_UP:Action::MOVE_UP_P2;
    Down= (playerIndex==0)?Action::MOVE_DOWN:Action::MOVE_DOWN_P2;
}

void Paddle::Update(float deltatime)
{
    if (!game) return;

    const InputManager* inputManager = dynamic_cast<PongGame*>(game)->GetInputManager();

    velocity = {0, 0};

    if (inputManager->GetActionState(Up) && GetPosition().y - Bounds.y/2  > 0)
    {
        velocity.y = -1;
    }
    else if (inputManager->GetActionState(Down) && GetPosition().y + Bounds.y/2 < GetScreenHeight())
    {
        velocity.y = 1;
    }

    SetPosition(position + velocity.Nomalized() * speed * deltatime);
}

void Paddle::Draw()
{
    GameObject::Draw();
    DrawRectangle(position.x+pivotOffset.x, position.y +pivotOffset.y, Bounds.x,Bounds.y, ObjColor);
}