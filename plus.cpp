#include "plus.h"
plus::plus(){
    static const QPixmap pic(":/picture/plus.jpeg");
    this->setPixmap(pic.scaled(40,40));
}
