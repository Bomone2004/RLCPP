#include "utility/FVector2.h"
#include <cmath>
float FVector2::Dot(const FVector2& other) const
{
    return x*other.x + y*other.y; 
}

float FVector2::SqrDistance(const FVector2& A, const FVector2& B)
{
    float dx = A.x - B.x;
    float dy = A.y - B.y;
    return dx*dx + dy*dy;
}
float FVector2::Distance(const FVector2& A, const FVector2& B){
    return std::sqrt(SqrDistance(A,B));
}