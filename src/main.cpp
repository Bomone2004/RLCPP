#include "pong/PongGame.h"


int main(){
    PongGame g {FVector2{1200,600}};
    //g.SetClearColor(BLACK); // Questo probabilmente dovrebbe stare dentro init game
    g.InitGame();
    g.Run();

    return 0;
}