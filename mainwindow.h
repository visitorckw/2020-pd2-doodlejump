#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QApplication>
#include <bits/stdc++.h>
#include <unistd.h>

#include "role.h"
#include "bullet.h"
#include "board.h"
#include "boarda.h"
#include "boardb.h"
#include "monster.h"
#include "rock.h"
#include "plus.h"
#include "clear.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);
    void fly(bullet*);
    void gameOver();
    void exitGame();


public slots:
    void jump();
    void bulletfly();
    void genMonster();
    void moveMonster();
    void moveRock();
    void movePro();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    role *player;
    QTimer *timer;
    rock *rk = NULL;
    plus *pl = NULL;
    clear *cl = NULL;
    int score = 0;
    std::vector<board*>boardVec;
    std::vector<monster*>monsterVec;
    std::vector<bullet*>bulletVec;
    QGraphicsTextItem *txt;
    QGraphicsTextItem *point;
    bool pause = false;

};

#endif // MAINWINDOW_H
