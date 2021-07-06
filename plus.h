#ifndef PLUS_H
#define PLUS_H
#include <QObject>
#include <QGraphicsPixmapItem>
class plus : public QObject, public QGraphicsPixmapItem{
public:
    plus();
    int moveTimes = 0;
};
#endif // PLUS_H
