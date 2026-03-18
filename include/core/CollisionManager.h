#pragma once
#include "core/Collider.h"
#include "core/GameObject.h"
#include "core/Collider.h"
#include <vector>
#include <memory>

class CollisionManager
{
    std::vector<std::weak_ptr<GameObject>> gameobj;

public:

    void RegisterCollider(std::shared_ptr<GameObject> GameObject);

    void UnregisterCollider(std::shared_ptr<GameObject> GameObject);

    void Update();
    
private:

    bool CheckForCollisionPair(const AIV_Collision::Collider* a,const AIV_Collision::Collider* b);
};