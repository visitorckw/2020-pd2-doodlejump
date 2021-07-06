#include "board.h"

void board::moveBoard(){
    if(moveTimes <= 0)
        return;
    setPos(x(),y()+5);
    --moveTimes;
    if(y() >= 400){
        setPos(rand()%600, 0);
    }
}

board::~board(){}
