#include "boarda.h"

boardA::boardA(){
    static const QPixmap picA(":/picture/board.png");
    this->setPixmap(picA.scaled(100,30));
}

bool boardA::collide(){
    return false;
}
boardA::~boardA(){

}
