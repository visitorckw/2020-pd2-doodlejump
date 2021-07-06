#ifndef BOARDA_H
#define BOARDA_H
#include "board.h"

class boardA : public board{
    Q_OBJECT
public:
    boardA();
    bool collide();
    ~boardA();
};

#endif // BOARDA_H
