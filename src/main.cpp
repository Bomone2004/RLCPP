#include "raylib.h"
#include "utility/FVector2.h"
#include "core/Game.h"
// FULL OBJECT ORIENTED
// Classe Game -> da cui ereditiamo per fare le nostre classi game
//      class Pong : public Game{};
        // draw
        // input
        // update
        // tutti gli oggetti di gioco

// class GameObject
        // posizione
        // velocity
        // radius (collisioni)
            // update
            // draw

// estendere il vector2

//-Include cartella
//  -utility
//  -core


int main(){
    Game g(FVector2{800,450}, "RLCPP");

    g.Run();


    return 0;
}