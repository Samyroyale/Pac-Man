#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPair>
#include "gameobject.h"



#define BALL_SCORE      10
#define POWERBALL_SCORE 30
#define INTERVAL        10


class Game : public QGraphicsScene
{
    Q_OBJECT

public:
    enum GameStatus {Playing, Win, Lose, Pause};
    Game(int, int, int, int, QString);
    ~Game();
    void start();
    void stop();
    void pacman_next_direction(GameObject::Dir);
    int get_score();

    GameObject ***map;              /
    GameObject *gate;
    QVector<GameObject*> powerball;
    GameStatus stat;

    friend class Pacman;



private slots:
    void pacman_handler();
    void powerball_flash();


private:
    int map_height, map_width;
    int map_size;
    int ball_num, eat_num, score;
    int geo_x, geo_y;


    QTimer *pacman_timer;
    QTimer *powerball_flash_timer;
    bool flash_tick;

};

#endif // GAME_H
