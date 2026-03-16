# RLCPP

TODO LIST (Lesson):
>> Gestione Input (Classe Input Manager) - DONE
>> Gestire Collisioni (AxisAlignedBoundingBox)
 bool CheckCollision(RectCollider, RectCollider){
        AABB
        controlla che ci sia Overlap su X
        controlla che ci sia Overlap su Y
        Se c'e` overlap su entrambe allora true 
        altrimenti false

    }

    bool CheckCollision(CircleCollider, CircleCollider){
        Somma dei raggi < Distanza tra centri
    }


    bool CheckCollision(RectCollider, CircleCollider){
        Prendo il punto piu` vicino al centro del cerchio 
        //closest.x = max(box.x, min(circle.xc, box.x + box.w))

        calcolo la distanza dal centro
        delta_x = circle.xc - closest.x

        sqrt(delta_x^2 + delta_y^2)

        return distance < circle.radius

    }

    Fare solo l'ultimo check 
    su paddle 1 e ball;

    
> Ragionare a componenti
    - Classe component base
    - Il gameobject ha una "collection" di componenti
    - ogni update fa l'update dei suoi componenti 
< UI basic    






TODO LIST (HOME)
Fork the repo and do homework there

11/03/2026
- Al momento i nostri gameobject hanno una speed hardcodata. Male, passarla in qualche modo
- Al momento i nostri gameobject possono uscire dallo schermo. Male, mettere bordi
- Guardate il commento nel main.cpp (riga 26)






/////


Servono Classi collider
    RectCollider (x,y,w,h)
    CircleCollider (xc,yc, radius)

proposta di implementazione: 
    Paddle: public Gameobject, public RectCollider
    Ball: public Gameobject, public CircleCollider



Serve un Collision manager: che deve controllare le collisioni con tutti gli oggetti 

controllare tutte le coppie di collisione con le sue 3 funzioni


principalmente 3 funzioni

    bool CheckCollision(RectCollider, RectCollider){
        AABB
        controlla che ci sia Overlap su X
        controlla che ci sia Overlap su Y
        Se c'e` overlap su entrambe allora true 
        altrimenti false

    }

    bool CheckCollision(CircleCollider, CircleCollider){
        Somma dei raggi < Distanza tra centri
    }


    bool CheckCollision(RectCollider, CircleCollider){
        Prendo il punto piu` vicino al centro del cerchio 
        //closest.x = max(box.x, min(circle.xc, box.x + box.w))

        calcolo la distanza dal centro
        delta_x = circle.xc - closest.x

        sqrt(delta_x^2 + delta_y^2)

        return distance < circle.radius

    }


proposta di implementazione2:
Servono Classi collider
    RectCollider (x,y,w,h)
    CircleCollider (xc,yc, radius)
Che pero` sono component
Quindi una cosa del genere: 
class Paddle : public Gameobject {

    std::unique_ptr<Collider> collider; (che dentro ha un rectCollider ) 

}
class Ball : public Gameobject {

    std::unique_ptr<Collider> collider; (che dentro ha un circle Collider) 

}

CollisionManager
Ha la lista di collider e fa i controllo di collisione su questi componenti
come funzioni sopra


///////
Una possibile implementazione: 
struct Component{


    void start() = 0;
    void update() = 0; 
    void draw() = 0; 
}
struct colliderComponent : public Component{

}
class Ball : public Gameobject {

    std::vector<std::unique_ptr<Component>>

    update(){
        chiamo anche update componenti
        //se non esiste il manager
    }

    draw(){
        chiamo anche draw componenti
    }
}

ColliderManager{ 
    std::vector<colliderComponent> 


}
