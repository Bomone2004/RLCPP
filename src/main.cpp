#include "raylib.h"
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

struct FVector2: Vector2{

    FVector2(float x = 0, float y = 0) : Vector2{x, y} {};


    // Overload operatori
    FVector2 operator+(const FVector2& other) const{
        return FVector2(x + other.x, y + other.y);
    }
    
    //utility
    float Dot(const FVector2& other)const {
        return x*other.x + y*other.y;
    }
};

int main(){
    //open window 
    InitWindow(800, 450, "HelloRay");
    //game loop while 
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Hello Ray!", 300, 200, 30, GREEN);

        EndDrawing();
    }


    //close window
    CloseWindow();
    return 0;
}