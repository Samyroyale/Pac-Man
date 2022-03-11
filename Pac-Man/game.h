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
#define GHOST_SCORE     50
#define INTERVAL        10
#define NORMAL_INTERVAL 10
#define PANNIC_INTERVAL 15
#define RUNNING_INTERVAL 5
#define PANNIC_TIME     1000
#define FLASH_INTERVAL 200


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

    GameObject ***map;
    GameObject *gate;
    Pacman *pacman;
    Ghost *ghost[Ghost::GhostNum];
    QVector<GameObject*> powerball;
    GameStatus stat;

    friend class Pacman;
    friend class Ghost;


private slots:
    void pacman_handler();
    void powerball_flash();
    void ghost_handler(int);

private:
    int map_height, map_width;
    int map_size;
    int ball_num, eat_num, score;
    int geo_x, geo_y;

    QTimer *ghost_timer[Ghost::GhostNum];
    QTimer *pacman_timer;
    QTimer *powerball_flash_timer;
    bool flash_tick;

};

#endif // GAME_H
