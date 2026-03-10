#include "pong/TestGO.h"




void TestGameObject::Update(float DeltaTime){

}

void TestGameObject::Draw(){
    DrawCircle(position.x, position.y, radius,ObjColor);
}