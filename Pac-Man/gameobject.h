#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>



class Game;



class GameObject : public QGraphicsPixmapItem
{
public:
    enum ObjectType {Ball, Wall, Gate, Pacman, Ghost, Blank, PowerBall};
    enum Dir {Up = 0, Down = 1, Left = 2, Right = 3, Stop = 4};
    static const int Width = 20;

    GameObject(ObjectType, QPixmap);
    ~GameObject();
    ObjectType get_type();
    int get_x();
    int get_y();
    int get_score();
    void set_score(int);
    void set_dir(Dir);
    void set_next_dir(Dir);
    Dir get_dir();
    Dir get_next_dir();

    friend class Game;
    friend class Ghost;

protected:
    int _x, _y;
    Dir dir;
    Dir next_dir;
    ObjectType type;
    int score;
};


/* Pacman */
class Pacman : public GameObject
{
public:
    Pacman();
    void move();
    Game *game;

    friend class Game;

private:
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
    void eat_ball(int, int);
    bool overlapable(int, int);

    QVector<QPixmap> anim[4];
    int anim_index;
};



class Ghost : public GameObject
{
public:
    enum Color {Red = 0, Yellow = 1, Pink = 2, Green = 3};
    enum Status {Normal, Panic, Running};
    const static int GhostNum = 4;
    Game *game;

    Ghost(int);
    void move();
    Color get_color();

    friend class Game;
    friend class Pacman;

private:
    void moveup();
    void movedown();
    void moveleft();
    void moveright();

    void setdir_randomly();
    void go_out_cage();
    void chase_pacman();
    void dodge_pacman();
    void go_to_cage();
    QPair<int, int> (*chase_strategy)(Ghost*);
    bool overlapable(int, int);

    Color color;
    Status status;
    QVector<QPixmap> anim[4];
    QVector<QPixmap> panic_anim;
    QVector<QPixmap> running_anim;
    int anim_index;
    int release_time;
    bool is_released;
    int panic_time;
};

QPair<int, int> strategy1(Ghost*);
QPair<int, int> strategy2(Ghost*);
QPair<int, int> strategy3(Ghost*);
QPair<int, int> strategy4(Ghost*);

#endif // GAMEOBJECT_H
