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
    // 3 oggetti 
    // 3 oggetti che collidono contemporaneamente 
    // A -collide-> B e C -collide-> B 
    // A smette di collidere con B , ma C continua a collidere con B
    // A sta collidendo con B -> MA B non sta collidendo con C

    // Il fulcro del problema e` che noi stiamo gestendo le collisioni basandoci su un singolo booleano 
    // quando in realta` dovremmo gestire questo sistema su collision pair

    // std::vector<> collisionPair
    // quando collidono aggiung questa coppia di oggetti al vector
    // quando la collisione tra i due fallisce li tolgo 
    // se quando controllo la collisione trovo la coppia nel vector, invece dell'oncollision enter chiamo lo stay
    // Il tipo di dato contenuto dal vector e` QUALCOSA: 
    // - deve avere info sui due gameobject 
    // - devo avere un modo per compararla con una coppia di gameobject
    
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