#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    srand((unsigned int)time(NULL));

    scene = new QGraphicsScene;
    player = new role;

    scene->setSceneRect(0,0,600,400);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(600,400);

    scene->addItem(player);
    QPixmap pic(":/picture/pusheen.jpg");
    player->setPixmap(pic.scaled(100,100));
    player->setPos(0,250);

    timer = new QTimer;
    timer->start(10);

    for(int i = 0; i < 8; ++i){
        board* ptr;
        if(i == 6) ptr = new boardB;
        else ptr = new boardA;
        ptr->setPos(rand()%500, (7-i)*50);
        ptr->connect(timer,SIGNAL(timeout()),ptr,SLOT(moveBoard()));
        scene->addItem(ptr);
        boardVec.push_back(ptr);
    }

    txt = new QGraphicsTextItem;
    txt->setPlainText("Score:");
    scene->addItem(txt);
    txt->setPos(500,50);

    point = new QGraphicsTextItem;
    point->setPlainText("0");
    scene->addItem(point);
    point->setPos(550,50);



    connect(timer,SIGNAL(timeout()),this,SLOT(jump()));
    connect(timer,SIGNAL(timeout()),this,SLOT(bulletfly()));
    connect(timer,SIGNAL(timeout()),this,SLOT(genMonster()));
    connect(timer,SIGNAL(timeout()),this,SLOT(moveMonster()));
    connect(timer,SIGNAL(timeout()),this,SLOT(moveRock()));
    connect(timer,SIGNAL(timeout()),this,SLOT(movePro()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
        case Qt::Key_A:
            if(player->x() - 50 < 0)
                player->setPos(player->x()-50+600, player->y());
            else
                player->setPos(player->x()-50, player->y());
            break;
        case Qt::Key_D:
            if(player->x() + 50 > 600)
                player->setPos(player->x()+50-600, player->y());
            else
                player->setPos(player->x()+50, player->y());
            break;
        case Qt::Key_Space:
            pause = !pause;
        break;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e){
    if(pause)
        return;
    bullet *b = new bullet;

    b->setPixmap(QPixmap(":/picture/magicBall.jpg").scaled(10,20));
    b->setPos(player->x() + player->pixmap().width() / 2, player->y() - player->pixmap().height());
    //b->connect(timer,SIGNAL(timeout()),this,SLOT(fly()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(b));
    bulletVec.push_back(b);
}

void MainWindow::jump(){
    if(pause) return;
    if(player->direction){
        player->setPos(player->x(),player->y()-1);
        if(player->y() <= 100){
            player->direction = false;
        }
    }
    else{
        player->setPos(player->x(),player->y()+1);
        int i;
        for(i = 0 ; i < boardVec.size(); ++i){
            if(!player->direction && player->collidesWithItem(boardVec[i]) and player->y() + 50 <= boardVec[i]->y()){
                if(boardVec[i]->collide()){
                    gameOver();
                }
                break;
            }
        }
        if(i != boardVec.size()){
            ++score;
            point->setPlainText(std::to_string(score).c_str());
            for(auto b : boardVec){
                b->moveTimes = (350 - boardVec[i]->y()) / 5;
            }
            for(auto m : monsterVec){
                m->moveTimes = (350 - boardVec[i]->y()) / 5;
            }
            if(cl) cl->moveTimes = (350 - boardVec[i]->y()) / 5;
            if(pl) pl->moveTimes = (350 - boardVec[i]->y()) / 5;
            player->direction = true;
        }
        if(player->y() >= 400)
            gameOver();
    }
    for(auto m : monsterVec){
        if(player->collidesWithItem(m))
            gameOver();
    }
}

void MainWindow::fly(bullet *b){
    b->setPos(b->x(),b->y()-3);
    int i;
    for(i = 0; i < monsterVec.size(); ++i)
        if(b->collidesWithItem(monsterVec[i]))
            break;
    if(i != monsterVec.size()){
        monsterVec[i]->scene()->removeItem(monsterVec[i]);
        delete monsterVec[i];
        std::swap(monsterVec[i],monsterVec.back());
        monsterVec.pop_back();
        b->scene()->removeItem(b);
        delete b;
        bulletVec.erase(std::find(bulletVec.begin(),bulletVec.end(),b));
        return;
    }
    if(b->y() < 0){
        b->scene()->removeItem(b);
        delete b;
        bulletVec.erase(std::find(bulletVec.begin(),bulletVec.end(),b));
    }
}

void MainWindow::bulletfly(){
    for(auto b : bulletVec)
        fly(b);
}

void MainWindow::genMonster(){
    if(pause) return;
    if(monsterVec.size() <= 1 && !(rand() % 1000)){
        monster* m = new monster;
        scene->addItem(m);
        m->setPos(rand()%400, 50);
        monsterVec.push_back(m);
    }
    if(!rk && !(rand() % 2500)){
        rk = new rock();
        scene->addItem(rk);
        rk->setPos(rand() % 500, 0);
    }
    if(!cl && !(rand() % 1000)){
        cl = new clear();
        scene->addItem(cl);
        cl->setPos(rand() % 500, 0);
    }
    if(!pl && !(rand() % 1000)){
        pl = new plus();
        scene->addItem(pl);
        pl->setPos(rand() % 500, 0);
    }
}

void MainWindow::moveMonster(){
    for(int i = 0; i < monsterVec.size(); ++i){
//        int rnd = rand() % 3;
//        if(rnd== 1)
//            monsterVec[i]->setPos(monsterVec[i]->x()+1,monsterVec[i]->y());
//        else if(rnd == 2)
//            monsterVec[i]->setPos(monsterVec[i]->x()-1,monsterVec[i]->y());
        if(monsterVec[i]->moveTimes <= 0)
                return;
        monsterVec[i]->setPos(monsterVec[i]->x(),monsterVec[i]->y()+5);
        --monsterVec[i]->moveTimes;
        if(monsterVec[i]->y() >= 400){
            monsterVec[i]->scene()->removeItem(monsterVec[i]);
            delete monsterVec[i];
            std::swap(monsterVec[i],monsterVec.back());
            monsterVec.pop_back();
            i = 0;
        }
    }
}

void MainWindow::moveRock(){
    if(rk){
        rk->setPos(rk->x(),rk->y()+5);
        if(rk->collidesWithItem(player))
            gameOver();
        if(rk->y() >= 400){
            rk->scene()->removeItem(rk);
            delete rk;
            rk = NULL;
        }
    }
}

void MainWindow::movePro(){
    if(pl && pl->moveTimes > 0){
        --pl->moveTimes;
        pl->setPos(pl->x(), pl->y()+5);
        if(pl->collidesWithItem(player)){
            score += 10;
            point->setPlainText(std::to_string(score).c_str());
            pl->scene()->removeItem(pl);
            delete pl;
            pl = NULL;
        }
        if(pl && pl->y() >= 400){
            pl->scene()->removeItem(pl);
            delete pl;
            pl = NULL;
        }
    }
    if(cl && cl->moveTimes > 0){
        --cl->moveTimes;
        cl->setPos(cl->x(), cl->y()+5);
        if(cl->collidesWithItem(player)){
            for(auto m : monsterVec){
                m->scene()->removeItem(m);
                delete m;
            }
            monsterVec.clear();
            if(rk){
                rk->scene()->removeItem(rk);
                delete rk;
                rk = NULL;
            }
            cl->scene()->removeItem(cl);
            delete cl;
            cl = NULL;
        }
        if(cl && cl->y() >= 400){
            cl->scene()->removeItem(cl);
            delete cl;
            cl = NULL;
        }
    }
}

void MainWindow::gameOver(){
    pause = true;
    QGraphicsPixmapItem *over = new QGraphicsPixmapItem;
    QPixmap overPic(":/picture/gameover.jpeg");
    over->setPixmap(overPic.scaled(200,150));
    scene->addItem(over);
    over->setPos(200,150);
//    exitGame();
//    QApplication *app;
//    app->exit(0);
}

void MainWindow::exitGame(){
    QApplication *app;
    app->exit(0);
}
