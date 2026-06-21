#include "pong/Ball.h"
#include "pong/PongGame.h"
#include "utility/ColorUtility.h"

void Ball::Start()
{
    ResetBall();
    GameObject::Start();
}


void Ball::Update(float DeltaTime)
{
    if (!game) return;

    if (GetPosition().y - radius < 0 || GetPosition().y + radius > game->GetScreenSize().y)
    {
        velocity.y *= -1.1;
        ChangeColor();
    }
    bool scored = false ;
    int scorePlayer;
    if (GetPosition().x + radius > game->GetScreenSize().x){
        velocity.x *= -1.1;
        ChangeColor();

        scored = true;
        scorePlayer = 0;

    } else if ( GetPosition().x - radius < 0)
    {
        velocity.x *= -1.1;

        scored = true;
        scorePlayer = 1;
    }

    if(scored){
        dynamic_cast<PongGame*>(game)->ScorePoints(scorePlayer);
        ResetBall();
    }

    SetPosition(position + velocity.Nomalized() * currentSpeed * DeltaTime);
    GameObject::Update(DeltaTime);
}

void Ball::ChangeColor()
{
    ObjColor = Aiv_Color::GetRandomColor();
}

void Ball::ResetBall()
{
    SetPosition(game->GetScreenCenter());
    currentSpeed = speed;
    float GetRandX = (float)GetRandomValue(-10,10)*10;
    float GetRandY = (float)GetRandomValue(-10,10);

    if(GetRandX == 0)
    {
        GetRandX = 1;
    }

    velocity = {GetRandX,GetRandY};

    velocity = velocity.Nomalized();
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
    if(currentSpeed < 500){
        currentSpeed *= 1.2;
    }
}
