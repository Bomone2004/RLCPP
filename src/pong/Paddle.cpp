#include "pong/Paddle.h"
#include "core/InputManager.h"
#include "pong/PongGame.h"

void Paddle::Start()
{

}

void Paddle::Update(float deltatime)
{
    if (!game) return;

    const InputManager* inputManager = dynamic_cast<PongGame*>(game)->GetInputManager();

    velocity = {0, 0};
    
    if (inputManager->GetActionState(Action::MOVE_UP) && GetPosition().y  > 0)
    {
        velocity.y = -1;
    }
    else if (inputManager->GetActionState(Action::MOVE_DOWN) && GetPosition().y + Bounds.y < GetScreenHeight())
    {
        velocity.y = 1;
    }

    SetPosition(position + velocity.Nomalized() * speed * deltatime);
}

void Paddle::Draw()
{
    DrawRectangle(position.x, position.y, Bounds.x,Bounds.y, ObjColor);
}