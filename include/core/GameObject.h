#pragma once

#include "utility/FVector2.h"
#include "core/Collider.h"
#include "core/Component.h"
#include <memory>
#include <vector>
#include <utility>

class Game;

class GameObject{
protected:
    FVector2 position;
    FVector2 velocity;
    FVector2 pivotOffset;
    bool active;
    float speed;

    std::vector<std::shared_ptr<Component>> components;

    Game* game;

public:
    GameObject(Game* g, FVector2 position = {0,0}, float speed = 0): game(g), position(position),
    velocity(FVector2{0,0}),
    speed(speed),
    active(true){}

    virtual ~GameObject(){}

    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void Draw();

    virtual void OnCollisionEnter(AIV_Collision::FCollisionInfo CollisionInfo);
    virtual void OnCollisionExit(AIV_Collision::FCollisionInfo CollisionInfo);
    virtual void OnCollisionStay(AIV_Collision::FCollisionInfo CollisionInfo);

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        auto component = std::make_shared<T>(this, std::forward<Args>(args)...);
        T* raw = component.get();
        components.push_back(component);
        return raw;
    }

    template<typename T>
    T* GetComponent() const
    {
        for (const auto& component : components)
        {
            if (T* found = dynamic_cast<T*>(component.get()))
            {
                return found;
            }
        }
        return nullptr;
    }

    //=======Setter=======
    void SetPosition(const FVector2& newPos);
    void SetVelocity(const FVector2& newVelocity);
    void SetActive(bool newState);

    //=======Getter=======
    FVector2 GetPosition() const;
    FVector2 GetVelocity() const;

    AIV_Collision::Collider* GetCollider() const;

    bool IsActive()const;


    void Destroy();
};
