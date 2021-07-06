#include "rock.h"

rock::rock(){
    static const QPixmap pic(":/picture/rock.jpg");
    this->setPixmap(pic.scaled(40,40));
}
