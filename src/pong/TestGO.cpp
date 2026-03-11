#include "pong/TestGO.h"

#include "pong/PongGame.h"


void TestGameObject::Update(float DeltaTime)
{
    if (!game) return;

    const InputManager* inputManager = dynamic_cast<PongGame*>(game)->GetInputManager();

    velocity = {0, 0};
    
    if (inputManager->GetActionState(Action::MOVE_UP))
    {
        velocity.y = -1;
    }
    else if (inputManager->GetActionState(Action::MOVE_DOWN))
    {
        velocity.y = 1;
    }

    if (inputManager->GetActionState(Action::MOVE_RIGHT))
    {
        velocity.x = 1;
    }
    else if (inputManager->GetActionState(Action::MOVE_LEFT))
    {
        velocity.x = -1;
    }

    SetPosition(position + velocity.Nomalized() * 10.0f * DeltaTime);
}

void TestGameObject::Draw(){
    DrawCircle(position.x, position.y, radius,ObjColor);
}