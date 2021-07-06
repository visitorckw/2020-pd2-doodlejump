#ifndef BOARDB_H
#define BOARDB_H
#include "board.h"
class boardB : public board{
    Q_OBJECT
public:
    boardB();
    bool collide();
    ~boardB();
};
#endif // BOARDB_H
