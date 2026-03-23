#pragma once
#include <algorithm>
#include <memory>
#include "utility/FVector2.h"
namespace AIV_Collision{
   struct FCollisionInfo{
       // std::weak_ptr<GameObject> other;
        float dx;
        float dy; 

    };

    struct Collider 
    { 
        FVector2 position;
        FVector2 offset;
        bool isColliding;
        virtual ~Collider() = default;
    };
    
    struct RectCollider: public Collider{
        FVector2 extents; //w, h
        RectCollider(FVector2 size):extents(size){}
    };
    
    struct CircleCollider: public Collider{ 
        float radius;
        CircleCollider(float r):radius(r){}
       
    };

 
    /* TODO 18/03 

    Potrebbe essere il caso di gestire questa cosa con i template
    Base: Ipotizzare una possibile implementazione e valutare se possibile. (MOLTO IMPORTANTE)
    Avanzato: implementazione 
    
    
    */ 
   
    bool CheckCollision(const RectCollider& A , const RectCollider& B);
    bool CheckCollision(const CircleCollider& A, const CircleCollider& B);    
    bool CheckCollision(const RectCollider& R, const CircleCollider& C);
    bool CheckCollision(const CircleCollider& C,const RectCollider& R);




 
   

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