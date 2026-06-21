#include "core/Collider.h"
#include <cmath>
namespace AIV_Collision{


        bool CheckCollision(const RectCollider& A , const RectCollider& B,FCollisionInfo& cInfo){
            bool overlap = A.position.x < B.position.x + B.extents.x &&
                            A.position.x + A.extents.x > B.position.x &&
                            A.position.y < B.position.y + B.extents.y &&
                            A.position.y + A.extents.y> B.position.y;

            if(overlap){
                float overlapX = std::min(A.position.x + A.extents.x, B.position.x + B.extents.x) - std::max(A.position.x, B.position.x);
                float overlapY = std::min(A.position.y + A.extents.y, B.position.y + B.extents.y) - std::max(A.position.y, B.position.y);
                cInfo.Overlap = FVector2(overlapX, overlapY);
            }

            return overlap;
        }



        bool CheckCollision(const CircleCollider& A, const CircleCollider& B,FCollisionInfo& cInfo){
                float radii = A.radius + B.radius;
                float distanceSqr = FVector2::SqrDistance(A.position, B.position);
                bool overlap = distanceSqr < radii*radii;

                if(overlap){
                    float distance = FVector2::Distance(A.position, B.position);
                    float penetration = radii - distance;
                    FVector2 direction = (distance > 0.0f) ? (B.position - A.position) * (1.0f/distance) : FVector2(1, 0);
                    cInfo.Overlap = FVector2(std::abs(direction.x) * penetration, std::abs(direction.y) * penetration);
                }

                return overlap;
        }


                        
        bool CheckCollision(const RectCollider& R, const CircleCollider& C,FCollisionInfo& cInfo){
                FVector2 closestPoint; 
                closestPoint.x = std::max(R.position.x , std::min(C.position.x, R.position.x + R.extents.x));
                closestPoint.y = std::max(R.position.y , std::min(C.position.y, R.position.y + R.extents.y));


                FVector2 Delta;
                Delta.x = C.position.x - closestPoint.x;
                Delta.y = C.position.y - closestPoint.y;
                
                float overlapX = C.radius - std::abs(Delta.x);
                float overlapY = C.radius - std::abs(Delta.y);

                cInfo.Overlap = FVector2(overlapX, overlapY);
                return  Delta.Magnitude()< C.radius;

        }
        bool CheckCollision(const CircleCollider& C,const RectCollider& R,FCollisionInfo& cInfo){
                return CheckCollision(R,C,cInfo);
        }


        void RectCollider::DrawDebug(){
                if(shouldDrawDebug){
                        DrawRectangleLines(position.x-1, position.y-1,extents.x+2, extents.y+2, color);
                }
        }
        void CircleCollider::DrawDebug(){
                if(shouldDrawDebug){
                        DrawCircleLines(position.x, position.y,radius+1, color);
                }
        }
}