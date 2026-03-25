#pragma once
#include <algorithm>
#include <memory>
#include "utility/FVector2.h"
namespace AIV_Collision{
   struct FCollisionInfo{
       // std::weak_ptr<GameObject> other;
        FVector2 Overlap;

        FCollisionInfo(): Overlap(0,0){}
    };

    struct Collider 
    { 
        FVector2 position;
        FVector2 offset;
        Color color = GREEN;
        bool isColliding;
        bool shouldDrawDebug;
        virtual ~Collider() = default;
        virtual void DrawDebug() = 0;
    };
    
    struct RectCollider: public Collider{
        FVector2 extents; //w, h
        RectCollider(FVector2 size):extents(size){}

        virtual void DrawDebug() override;
    };
    
    struct CircleCollider: public Collider{ 
        float radius;
        CircleCollider(float r):radius(r){}

        virtual void DrawDebug() override;
    };

 
    /* TODO 18/03 

    Potrebbe essere il caso di gestire questa cosa con i template
    Base: Ipotizzare una possibile implementazione e valutare se possibile. (MOLTO IMPORTANTE)
    Avanzato: implementazione 
    
    
    */ 
   
    bool CheckCollision(const RectCollider& A , const RectCollider& B   ,FCollisionInfo& cInfo);
    bool CheckCollision(const CircleCollider& A, const CircleCollider& B,FCollisionInfo& cInfo);    
    bool CheckCollision(const RectCollider& R, const CircleCollider& C  ,FCollisionInfo& cInfo);
    bool CheckCollision(const CircleCollider& C,const RectCollider& R   ,FCollisionInfo& cInfo);




 
   

    /*
    class gameobject{ 
        ptr<AIV_Collision::Collider>  
    }
    
    

    class CollisionManager{ 
        std::vector<ptr<gameobject>> 

    public:
        void RegisterCollider(/*un Gameobject )

        void UnregisterCollider(/*un Gameobject)

        void Update(){
            foreach(collider){
                CheckForCollisionPair()

                // Ci si aprono delle strade (che vedremo)
            }
        }
    private:
        bool CheckForCollisionPair( coll A , coll B );

    }

    class Game{ 
        ptr<CollisionManager> mgr


        void Update()
        {
            // Quello che gia` fa
            mgr->Update();
        }
    }
    
    */
};