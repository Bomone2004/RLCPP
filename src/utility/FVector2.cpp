#include "utility/FVector2.h"

float FVector2::Dot(const FVector2& other) const
{
    return x*other.x + y*other.y; 
}
