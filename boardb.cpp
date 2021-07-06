#include "boardb.h"
boardB::boardB(){
    static const QPixmap picA(":/picture/boardB.png");
    this->setPixmap(picA.scaled(100,30));
}

bool boardB::collide(){
    return true;
}
boardB::~boardB(){}
