#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>


/* Predefine the game object */
class Game;


/* Base class of ghosts, pacman */
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


protected:
    int _x, _y;                 // coordinate in map
    Dir dir;                    // current moving direction
    Dir next_dir;               // next direction by w, a, s, d key
    ObjectType type;
    int score;
};


/* Pacman */
class Pacman : public GameObject
{
public:
    Pacman();
    void move();
    Game *game;                 // the pacman game object

    friend class Game;

private:
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
    void eat_ball(int, int);
    bool overlapable(int, int); // check if pacman can go to map[i][j]

    QVector<QPixmap> anim[4];   // animations
    int anim_index;
};



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
     // function pointer of a chasing stragety
    bool overlapable(int, int);                 // check if ghost can go to map[i][j]

    Color color;
    Status status;
    QVector<QPixmap> anim[4];                   // animations
    QVector<QPixmap> panic_anim;
    QVector<QPixmap> running_anim;
    int anim_index;
    int release_time;           // time to get out the cage
    bool is_released;
    int panic_time;
};


#endif // GAMEOBJECT_H
