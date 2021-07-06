#include "monster.h"

monster::monster(){
    static const QPixmap pic(":/picture/monster.png");
    this->setPixmap(pic.scaled(40,40));
}


