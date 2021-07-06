#ifndef ROLE_H
#define ROLE_H
#include <QObject>
#include <QGraphicsPixmapItem>

class role : public QObject, public QGraphicsPixmapItem{
public:
    bool direction = true;
//public slots:
//    void jump();
};

#endif // ROLE_H
