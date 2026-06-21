#include "core/CollisionManager.h"

void CollisionManager::RegisterCollider(std::shared_ptr<GameObject> GameObject)
{
    if(GameObject->GetCollider() == nullptr){return ;}

    gameobj.push_back(GameObject);
}

void CollisionManager::UnregisterCollider(std::shared_ptr<GameObject> GameObject)
{
    //se ho ciclo i elementi
    //fare lock
    //se ho ogetto ed e valido allora la rimuovo

    for(int i = 0; i < gameobj.size() ; ++i)
    {   
        auto obj = gameobj.at(i).lock();

        if(obj == nullptr) {return;}

        if(obj == GameObject)
        {
            gameobj.erase(gameobj.begin() + i);
            return;
        }
        
    }
}

void CollisionManager::Clear()
{
    gameobj.clear();
    currentCollisions.clear();
    previousCollisions.clear();
}

void CollisionManager::Update()
{

    previousCollisions = currentCollisions; 
    currentCollisions.clear();

    for(int i = 0; i < gameobj.size(); ++i)
    {
        auto objA = gameobj.at(i).lock();
        if(!objA) continue; 
        for(int j = i + 1; j < gameobj.size(); ++j)
        {
            auto objB = gameobj.at(j).lock();
            if(!objB) continue; 
            AIV_Collision::FCollisionInfo cInfo;
            if(CheckForCollisionPair(objA.get()->GetCollider(), objB.get()->GetCollider(),cInfo))
            {
                currentCollisions.emplace_back(objA, objB);
                
                
                AIV_Collision::FCollisionInfo cInfoA;
                AIV_Collision::FCollisionInfo cInfoB;
                cInfoA.Overlap = cInfo.Overlap;
                cInfoB.Overlap = cInfo.Overlap;

                if(!HasCollisionPair(previousCollisions, objA, objB)){
                    objA->OnCollisionEnter(cInfoA);
                    objB->OnCollisionEnter(cInfoB);
                }
                else{
                    objA->OnCollisionStay(cInfoA);
                    objA->OnCollisionStay(cInfoB);
                }
            }  
        }
    }

    for(const auto& prevPair : previousCollisions)
    {
        if(!HasCollisionPair(currentCollisions, prevPair.ObjectA.lock(), prevPair.ObjectB.lock()))
        {
            auto objA = prevPair.ObjectA.lock();
            auto objB = prevPair.ObjectB.lock();

            if(objA && objB){
                AIV_Collision::FCollisionInfo empty; 
                objA->OnCollisionExit(empty);
                objB->OnCollisionExit(empty);

            }
        }
    }
    
}

namespace
{
    template<typename A, typename B>
    bool TryCollisionPair(const AIV_Collision::Collider* a, const AIV_Collision::Collider* b, AIV_Collision::FCollisionInfo& cInfo, bool& collided)
    {
        const A* castedA = dynamic_cast<const A*>(a);
        const B* castedB = dynamic_cast<const B*>(b);

        if (castedA && castedB)
        {
            collided = AIV_Collision::CheckCollision(*castedA, *castedB, cInfo);
            return true;
        }
        return false;
    }
}

bool CollisionManager::CheckForCollisionPair(const AIV_Collision::Collider* a, const AIV_Collision::Collider* b, AIV_Collision::FCollisionInfo& cInfo )
{
    using namespace AIV_Collision;

    bool collided = false;

    if (TryCollisionPair<RectCollider, RectCollider>(a, b, cInfo, collided)) return collided;
    if (TryCollisionPair<CircleCollider, CircleCollider>(a, b, cInfo, collided)) return collided;
    if (TryCollisionPair<RectCollider, CircleCollider>(a, b, cInfo, collided)) return collided;
    if (TryCollisionPair<CircleCollider, RectCollider>(a, b, cInfo, collided)) return collided;

    return false;
}

bool CollisionManager::HasCollisionPair(const std::vector<FCollisionPair> &pairs, std::shared_ptr<GameObject> A, std::shared_ptr<GameObject> B)
{
    if(!A|| !B) return false; 

    FCollisionPair searchPair(A, B);
    return std::find(pairs.begin(), pairs.end(), searchPair)!= pairs.end();
}
bool FCollisionPair::operator==(const FCollisionPair &other) const
{
    auto a1  = ObjectA.lock();
    auto a2 = other.ObjectA.lock();
    auto b1 = ObjectB.lock();
    auto b2  = other.ObjectB.lock();

    if(!a1 ||!a2 ||!b1 ||!b2) return false;

    return (a1 == a2 && b1 == b2)|| (a1 == b2 && b1 == a2);
}