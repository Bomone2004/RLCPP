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
            auto objA = gameobj.at(i).lock();
            auto objB = gameobj.at(j).lock();
            
            if(CheckForCollisionPair(objA.get()->GetCollider(), objB.get()->GetCollider()))
            {
                AIV_Collision::FCollisionInfo cInfo;
                cInfo.dx = objA.get()->GetPosition().x - objB.get()->GetPosition().x;
                cInfo.dy = objA.get()->GetPosition().y - objB.get()->GetPosition().y;
                AIV_Collision::FCollisionInfo cInfoA;
                AIV_Collision::FCollisionInfo cInfoB;
                cInfoA.dx = cInfo.dx;
                cInfoB.dx = -cInfo.dx;
                cInfoA.dy = cInfo.dy;
                cInfoB.dy = -cInfo.dy;


                //collision detected
                objA->OnCollisionEnter(cInfoA);
                objB->OnCollisionEnter(cInfoB);

                /* TODO 18/03 

                    1- Mandare delle informazioni:
                        struct CollisionInfo
                        popolata nel CheckForCollisionPair
                            - oggetto A 
                            - oggetto B 
                            Avanzata: 
                                punto di collisione

                    2- On collision enter va chiamata una volta sola.
                        Aggiungere on collision exit
                        Aggiungere On collision stay
                        E gestire queste chiamate

                        per testare questo fatelo con i colori
                            -> enter: rossa
                            -> stay: blu
                            -> exit: bianca

                */


            }
        }
    }
    
}

bool CollisionManager::CheckForCollisionPair(const AIV_Collision::Collider* a, const AIV_Collision::Collider* b )
{
    //dynamic cast returns a valid ptr only IF conversion exists, otherwise nullptr
    auto* rectA = dynamic_cast<const AIV_Collision :: RectCollider*>(a);
    auto* rectB = dynamic_cast<const AIV_Collision :: RectCollider*>(b);

    if(rectA && rectB)
    {
        return AIV_Collision  :: CheckCollision(*rectA,*rectB);
    }


    auto* circleA = dynamic_cast<const AIV_Collision :: CircleCollider*>(a);
    auto* circleB = dynamic_cast<const AIV_Collision :: CircleCollider*>(b);

    if(circleA && circleB)
    {
        return AIV_Collision :: CheckCollision(*circleA,*circleB);
    }


    if(rectA && circleB)
    {
        return AIV_Collision  :: CheckCollision(*rectA,*circleB);
    }
    if(circleA && rectB)
    {
        return AIV_Collision :: CheckCollision(*circleA,*rectB);
    }

    return false;
}