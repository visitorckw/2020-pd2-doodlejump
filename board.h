#ifndef BOARD_H
#define BOARD_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class board : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    virtual bool collide() = 0;
    virtual ~board();
    int moveTimes = 0;
public slots:
    void moveBoard();
};

#endif // BOARD_H
