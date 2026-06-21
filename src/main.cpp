#include "pong/PongGame.h"


int main(){
    PongGame g {FVector2{800,600}};
    g.InitGame();
    g.Run();

    return 0;
}
