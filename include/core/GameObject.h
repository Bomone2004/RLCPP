#pragma once
#include "utility/FVector2.h"
#include "core/Component.h"
#include <vector>
#include <memory>

class Game;

class GameObject{
protected:
    FVector2 position;
    FVector2 velocity;
    float radius; // raggio di collisione
    bool active;
    float speed;


    Game* game;

    std::vector<std::unique_ptr<Component>> components; // Collection di componenti (ownership tramite unique_ptr)

public:
    GameObject(Game* g, FVector2 position = {0,0}, float speed = 0): game(g), position(position),
    velocity(FVector2{0,0}),
    radius(radius),
    active(true){}

    virtual ~GameObject(){}

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

    //=======Components=======
    // Aggiunge un componente al GameObject (trasferisce ownership tramite move semantics)
    void AddComponent(std::unique_ptr<Component> comp);

    // Cerca un componente per tipo tramite dynamic_cast (RTTI)
    // Ritorna nullptr se il componente non e` presente
    template<typename T>
    T* GetComponent() const {
        for(auto& c : components){
            T* found = dynamic_cast<T*>(c.get());
            if(found) return found;
        }
        return nullptr;
    }

    //=======Setter=======
    void SetPosition(const FVector2& newPos);
    void SetVelocity(const FVector2& newVelocity);
    void SetRadius(float newRadius);
    void SetActive(bool newState);

    //=======Getter=======
    FVector2 GetPosition() const;
    FVector2 GetVelocity() const;
    float GetRadius() const;
    bool IsActive()const;

    void Destroy();

protected:
    // Da chiamare dentro Update() delle classi figlie per aggiornare tutti i componenti
    void UpdateComponents(float deltaTime);
    // Da chiamare dentro Draw() delle classi figlie per disegnare tutti i componenti
    void DrawComponents();
};