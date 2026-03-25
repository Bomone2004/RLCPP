#include "pong/Ball.h"
#include "pong/PongGame.h"
#include "utility/ColorUtility.h"
#include <iostream>
void Ball::Start()
{
    float GetRandX = (float)GetRandomValue(-100,100);
    float GetRandY = (float)GetRandomValue(-10,10);

    if(GetRandX == 0)
    {
        GetRandX = 1;
    }

    velocity = {GetRandX,GetRandY};

    velocity = velocity.Nomalized();
}


void Ball::Update(float DeltaTime)
{
    if (!game) return;

    if (GetPosition().y - radius < 0 || GetPosition().y + radius > GetScreenHeight())
    {
        velocity.y *= -1.1;
        ChangeColor();
    }

    if (GetPosition().x + radius > GetScreenWidth() || GetPosition().x - radius < 0)
    {
        velocity.x *= -1.1;
        ChangeColor();
    }
    
    SetPosition(position + velocity.Nomalized() * speed * DeltaTime);
}

void Ball::ChangeColor()
{
    ObjColor = Aiv_Color::GetRandomColor();
}

void Ball::Draw()
{
    GameObject::Draw();
    DrawCircle(position.x+pivotOffset.x, position.y +pivotOffset.y, radius,ObjColor);
}


void Ball::OnCollisionEnter(AIV_Collision::FCollisionInfo CollisionInfo){

    GameObject::OnCollisionEnter(CollisionInfo);
    if(CollisionInfo.Overlap.x< CollisionInfo.Overlap.y)
    {
        velocity.x =- velocity.x;
        velocity.y *= 1.1;
    }
    else
    {
        velocity.y = -velocity.y;

    }
    if(speed < 500){
        speed *= 1.2;
    }
}
