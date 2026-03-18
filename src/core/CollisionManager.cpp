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
    /* 
    ogni collider comparare con un altro collider,
    ma senza fare comparazioni innutili,
    a comparare b e c, b solo con c, perche con a ho gia comparato, c con niente perche gia fatto
    */
    for(int i = 0; i < gameobj.size(); ++i)
    {
        for(int j = i + 1; j < gameobj.size(); ++j)
        {
            CheckForCollisionPair(gameobj.at(i).lock().get()->GetCollider(), gameobj.at(j).lock().get()->GetCollider());
        }
    }
    
}

bool CollisionManager::CheckForCollisionPair(const AIV_Collision::Collider* a, const AIV_Collision::Collider* b)
{
    return true;
}