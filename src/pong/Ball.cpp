#include "pong/Ball.h"
#include "pong/PongGame.h"
#include "utility/ColorUtility.h"
#include <cmath>

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
        velocity.y = -velocity.y;
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

    PongGame* pong = dynamic_cast<PongGame*>(game);
    if (!pong) return;

    bool leftSide = GetPosition().x < pong->GetScreenSize().x * 0.5f;
    float paddleCenterY = pong->GetPaddleCenterY(leftSide);
    float paddleHalfHeight = pong->GetPaddleHalfHeight(leftSide);

    float offset = (GetPosition().y - paddleCenterY) / paddleHalfHeight;
    if (offset < -1.0f) offset = -1.0f;
    if (offset > 1.0f) offset = 1.0f;

    float maxBounceAngle = PI / 3.0f;
    float angle = offset * maxBounceAngle;
    float directionX = leftSide ? 1.0f : -1.0f;

    velocity = FVector2(directionX * std::cos(angle), std::sin(angle));
    velocity = velocity.Nomalized();

    if(currentSpeed < 750){
        currentSpeed *= 1.1;
    }
}
