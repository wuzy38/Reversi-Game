#ifndef REVERSIMAINWINDOW_H
#define REVERSIMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "reversi.h"
#include "reversiai.h"

namespace Ui {
class ReversiMainWindow;
}

class ReversiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReversiMainWindow(QWidget *parent = 0, int humanplayer = -1, int search_depth = 7);
    ~ReversiMainWindow();

public slots:
    void timeroutslot();

protected:
    // 绘制
    void paintEvent(QPaintEvent *);
    // 点击
    void mousePressEvent(QMouseEvent *);
    // 实际落子
//    void mouseReleaseEvent(QMouseEvent *event);
    // 监听鼠标
    void mouseMoveEvent(QMouseEvent *event);

    void updateScore();


private:
    Ui::ReversiMainWindow *ui;
    QTimer *timer;
    int chess_size;             // 棋盘大小
    int board_size;             // 棋格大小
    int dist;                   // 棋子和线的距离
    Reversi reversi;
    ReversiAi reversiai1;
    ReversiAi reversiai2;
    int aiplayer1;
    int aiplayer2;
    int humanplayer;
    int mousex;
    int mousey;
    bool clicked;
    int putx;
    int puty;
    QLabel *humanlabel;
    QLabel *ailabel;
};

#endif // REVERSIMAINWINDOW_H
