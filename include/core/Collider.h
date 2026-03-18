#pragma once
#include <algorithm>
#include "utility/FVector2.h"
namespace AIV_Collision{

    struct Collider 
    { 
        FVector2 position;
    };
    
    struct RectCollider: public Collider{
        FVector2 extents; //w, h
    };
    
    struct CircleCollider: public Collider{ 
        float radius;
    };
    
    
    /*
    
    A.x A.y         A.x + W 
    ________________
    |               |
    |               |
    |               |
    |               |
    |_______________|
    A.y + H 
                B.x  B.y      B.x + W 
                ________________
                |               |
                |               |
                |               |
                |               |
                |_______________|
                B.y + H 
    
    */



    inline bool CheckCollision(const RectCollider& A , const RectCollider& B){
        // AA BB Secca
        bool overlap = A.position.x < B.position.x + B.extents.x && //rettangolo A e` a sinistra di B
                        A.position.x + A.extents.x > B.position.x &&
                        A.position.y < B.position.y + B.extents.y &&
                        A.position.y + A.extents.y> B.position.y;   
                    
        return overlap;
    }               

    inline bool CheckCollision(const CircleCollider& A, const CircleCollider& B){
        float distanceSqr = FVector2::SqrDistance(A.position, B.position);
        return distanceSqr < (A.radius + B.radius)*(A.radius + B.radius);
        /*
        float distance = FVector2::Distance(A.position, B.position);
        return distance < (A.radius + B.radius);
        */
    }
    
    inline bool CheckCollision(const RectCollider& R, const CircleCollider& C){
        FVector2 closestPoint; 
        closestPoint.x = std::max(R.position.x , std::min(C.position.x, R.position.x + R.extents.x));
        closestPoint.y = std::max(R.position.y , std::min(C.position.y, R.position.y + R.extents.y));


        FVector2 Delta;
        Delta.x = C.position.x - closestPoint.x;
        Delta.y = C.position.y - closestPoint.y;

        return  Delta.Magnitude()< C.radius;

    }
    
}