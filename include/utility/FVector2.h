#pragma once
#include "raylib.h"

struct FVector2 : Vector2
{
    FVector2(float x = 0, float y = 0) : Vector2{x, y} {};
    
    FVector2(const Vector2& v2):Vector2(v2){};
    // Overload operatori
    FVector2 operator+(const FVector2& other) const
    {
        return FVector2(x + other.x, y + other.y);
    }

    FVector2 operator-(const FVector2& other) const
    {
        return FVector2(x - other.x, y - other.y);
    }

    FVector2 operator*(const float scalar) const
    {
        return FVector2(x * scalar, y * scalar);
    }

    float Magnitude();


    //======= Funzioni Utility ======= 
    float Dot(const FVector2& other)const;

    FVector2 Nomalized() const;

    static float SqrDistance(const FVector2& A, const FVector2& B);
    static float Distance(const FVector2& A, const FVector2& B);

};