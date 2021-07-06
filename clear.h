#ifndef CLEAR_H
#define CLEAR_H
#include <QObject>
#include <QGraphicsPixmapItem>
class clear : public QObject, public QGraphicsPixmapItem{
public:
    clear();
    int moveTimes = 0;
};
#endif // CLEAR_H
