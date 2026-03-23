#include "pong/PongGame.h"
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
    PongGame g {FVector2{1200,600}};
    //g.SetClearColor(BLACK); // Questo probabilmente dovrebbe stare dentro init game
    g.InitGame();
    g.Run();

    return 0;
}