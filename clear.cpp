#include "clear.h"

clear::clear(){
    static const QPixmap pic(":/picture/clear.png");
    this->setPixmap(pic.scaled(40,40));
}
