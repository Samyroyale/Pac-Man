#include "mainwindow.h"
#include "item.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("pac-man"));
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    scene = new QGraphicsScene(50, 50, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setScene(scene);
    set_board();
    timer = new QTimer(this);
    flash = new QTimer(this);
    timer->start(6);
    flash->start(200);
    connect(timer,SIGNAL(timeout()),this,SLOT(ghostmv()));
    connect(flash,SIGNAL(timeout()),this,SLOT(powerball_flash()));
}


void MainWindow::powerball_flash() {
    if(pball.empty()) {
        flash->stop();
        return;
    }
    if(flashtik) {
        for(int i=0;i<pball.size();++i)
            pball.at(i)->hide();
        flashtik=0;
    } else {
        for(int i=0;i<pball.size();++i)
            pball.at(i)->show();
        flashtik=1;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(islose){
        return;
    }
    if(event->key() == Qt::Key_W){
        switch(pac->get_dir()) {
        case _down: case _stop:
            pac->set_nextdir(_stop);
            pac->set_changept(-1);
            pac->moveup();
            break;
        case _left:
            if(pac->get_py()>0) {
                int nowx = pac->get_px() - 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy-1][nowx] == '0') {
                        pac->set_nextdir(_up);
                        pac->set_changept(nowx);
                        break;
                    }
                    --nowx;
                }
            }
            break;
        case _right:
            if(pac->get_py()>0) {
                int nowx = pac->get_px() + 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy-1][nowx] == '0') {
                        pac->set_nextdir(_up);
                        pac->set_changept(nowx);
                        break;
                    }
                    ++nowx;
                }
            }
            break;
        }
    }

    else if(event->key() == Qt::Key_A){
        switch(pac->get_dir()) {
        case _right: case _stop:
            pac->set_nextdir(_stop);
            pac->set_changept(-1);
            pac->moveleft();
            break;
        case _up:
            if(pac->get_px()>0) {
                int nowx = pac->get_px(), nowy = pac->get_py() - 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx-1] == '0') {
                        pac->set_nextdir(_left);
                        pac->set_changept(nowy);
                        break;
                    }
                    --nowy;
                }
            }
            break;
        case _down:
            if(pac->get_px()>0) {
                int nowx = pac->get_px(), nowy = pac->get_py() + 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx-1] == '0') {
                        pac->set_nextdir(_left);
                        pac->set_changept(nowy);
                        break;
                    }
                    ++nowy;
                }
            }
            break;
        }
    }
    else if(event->key() == Qt::Key_S){
        switch(pac->get_dir()) {
        case _up: case _stop:
            pac->set_nextdir(_stop);
            pac->set_changept(-1);
            pac->movedown();
            break;
        case _left:
            if(pac->get_py()<21) {
                int nowx = pac->get_px() - 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy+1][nowx] == '0') {
                        pac->set_nextdir(_down);
                        pac->set_changept(nowx);
                        break;
                    }
                    --nowx;
                }
            }
            break;
        case _right:
            if(pac->get_py()<21) {
                int nowx = pac->get_px() + 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy+1][nowx] == '0') {
                        pac->set_nextdir(_down);
                        pac->set_changept(nowx);
                        break;
                    }
                    ++nowx;
                }
            }
            break;
        }
    }
    else if(event->key() == Qt::Key_D){
        switch(pac->get_dir()) {
        case _left: case _stop:
            pac->moveright();
            break;
        case _up:
            if(pac->get_px()<30) {
                int nowx = pac->get_px(), nowy = pac->get_py() - 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx+1] == '0') {
                        pac->set_nextdir(_right);
                        pac->set_changept(nowy);
                        break;
                    }
                    --nowy;
                }
            }
            break;
        case _down:
            if(pac->get_px()<30) {
                int nowx = pac->get_px(), nowy = pac->get_py() + 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx+1] == '0') {
                        pac->set_nextdir(_right);
                        pac->set_changept(nowy);
                        break;
                    }
                    ++nowy;
                }
            }
            break;
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
