#pragma once
#include "core/Collider.h"
#include "core/GameObject.h"
#include "core/Collider.h"
#include <vector>
#include <memory>

struct FCollisionPair { 
    std::weak_ptr<GameObject> ObjectA; 
    std::weak_ptr<GameObject> ObjectB; 

    FCollisionPair(std::weak_ptr<GameObject> A, std::weak_ptr<GameObject> B ): ObjectA(A), ObjectB(B) {}

    bool operator==(const FCollisionPair& other) const;

};

class CollisionManager
{
    std::vector<std::weak_ptr<GameObject>> gameobj;
    std::vector<FCollisionPair> currentCollisions;
    std::vector<FCollisionPair> previousCollisions;
public:

    void RegisterCollider(std::shared_ptr<GameObject> GameObject);

    void UnregisterCollider(std::shared_ptr<GameObject> GameObject);

    void Update();
    
private:

    bool CheckForCollisionPair(const AIV_Collision::Collider* a,const AIV_Collision::Collider* b, AIV_Collision::FCollisionInfo& cInfo);

    bool HasCollisionPair(const std::vector<FCollisionPair>& pairs, std::shared_ptr<GameObject> A, std::shared_ptr<GameObject> B );
};