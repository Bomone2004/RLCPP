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
            
            AIV_Collision::FCollisionInfo cInfo;
            if(CheckForCollisionPair(objA.get()->GetCollider(), objB.get()->GetCollider(),cInfo))
            {
                
                AIV_Collision::FCollisionInfo cInfoA;
                AIV_Collision::FCollisionInfo cInfoB;
                cInfoA.Overlap = cInfo.Overlap;
                cInfoB.Overlap = cInfo.Overlap;


                //collision detected
                if(!objA->GetCollider()->isColliding)
                {
                    objA->OnCollisionEnter(cInfoA);
                }
                else{
                    objA->OnCollisionStay(cInfoA);
                }
                if(!objB->GetCollider()->isColliding)
                {
                    objB->OnCollisionEnter(cInfoB);
                }
                else{
                    objA->OnCollisionStay(cInfoB);
                }

                objA->GetCollider()->isColliding = true;
                objB->GetCollider()->isColliding = true;

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
            else
            {
                if(objA->GetCollider()->isColliding)
                {
                    objA->OnCollisionExit(cInfo);
                }
                if(objB->GetCollider()->isColliding)
                {
                    objB->OnCollisionExit(cInfo);
                }
                objA->GetCollider()->isColliding = false;
                objB->GetCollider()->isColliding = false;
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