#pragma once
#include "raylib.h"

struct FVector2 : Vector2
{
    FVector2(float x = 0, float y = 0) : Vector2{x, y} {};

    // Overload operatori
    FVector2 operator+(const FVector2& other) const{
        return FVector2(x + other.x, y + other.y);
    }
    
    //======= Funzioni Utility ======= 
    float Dot(const FVector2& other)const;

    static float SqrDistance(const FVector2& A, const FVector2& B);
    static float Distance(const FVector2& A, const FVector2& B);

};