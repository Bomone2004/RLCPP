#pragma once

class GameObject;

// Classe base astratta per il pattern Component
// Ogni componente ha un riferimento al suo owner (il GameObject a cui appartiene)
// Le classi figlie devono implementare Start(), Update() e Draw()
class Component
{
protected:
    GameObject* owner; // Puntatore raw al GameObject proprietario (non owning)

public:
    Component(GameObject* owner) : owner(owner){}
    virtual ~Component(){}

    virtual void Start() = 0;   // Chiamato una volta all'inizializzazione
    virtual void Update(float deltaTime) = 0; // Chiamato ogni frame
    virtual void Draw() = 0;    // Chiamato ogni frame per il rendering

    GameObject* GetOwner() const { return owner; }
};
