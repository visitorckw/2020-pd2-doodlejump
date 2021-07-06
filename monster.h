#ifndef MONSTER_H
#define MONSTER_H
#include <QObject>
#include <QGraphicsPixmapItem>
class monster : public QObject, public QGraphicsPixmapItem{
public:
    monster();
    int moveTimes = 0;
public slots:
};

#endif // MONSTER_H
