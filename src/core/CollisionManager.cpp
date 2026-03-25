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

bool CollisionManager::CheckForCollisionPair(const AIV_Collision::Collider* a, const AIV_Collision::Collider* b, AIV_Collision::FCollisionInfo& cInfo )
{
    //dynamic cast returns a valid ptr only IF conversion exists, otherwise nullptr
    auto* rectA = dynamic_cast<const AIV_Collision :: RectCollider*>(a);
    auto* rectB = dynamic_cast<const AIV_Collision :: RectCollider*>(b);

    if(rectA && rectB)
    {
        return AIV_Collision::CheckCollision(*rectA,*rectB, cInfo);
    }


    auto* circleA = dynamic_cast<const AIV_Collision :: CircleCollider*>(a);
    auto* circleB = dynamic_cast<const AIV_Collision :: CircleCollider*>(b);

    if(circleA && circleB)
    {
        return AIV_Collision::CheckCollision(*circleA,*circleB, cInfo);
    }


    if(rectA && circleB)
    {
        return AIV_Collision::CheckCollision(*rectA,*circleB, cInfo);
    }
    if(circleA && rectB)
    {
        return AIV_Collision::CheckCollision(*circleA,*rectB, cInfo);
    }

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