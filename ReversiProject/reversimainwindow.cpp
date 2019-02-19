#include "reversimainwindow.h"
#include "ui_reversimainwindow.h"

#include <QTimer>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QWidget>
#include <QDebug>
#include <QPoint>
#include <QLabel>

ReversiMainWindow::ReversiMainWindow(QWidget *parent, int humanplayer, int search_depth) :
    QMainWindow(parent),
    ui(new Ui::ReversiMainWindow),
    reversiai1(search_depth, 15, 15, 1),
    reversiai2(7, 252, 206, 1)
{
    ui->setupUi(this);
    this->setWindowTitle("Reversi");
    //
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);
    chess_size = 8;
    board_size = 80;
    dist = 3;
    this->humanplayer = humanplayer;
    aiplayer1 = -humanplayer;
    aiplayer2 = 1;
    clicked = false;
    // 显示得分的字样
    humanlabel = new QLabel(this);
    ailabel = new QLabel(this);
    humanlabel->setGeometry((chess_size+2)*board_size, (chess_size - 2)*board_size, 2*board_size, 2*board_size);
    ailabel->setGeometry((chess_size+2)*board_size, 2*board_size, 2*board_size, 2*board_size);
    humanlabel->setAlignment(Qt::AlignCenter);          // 设置对齐方式为居中
    ailabel->setAlignment(Qt::AlignCenter);
    QFont ft;                                           // 设置字体
    ft.setFamily("Microsoft YaHei");                    // 设置文字字体 "SimSun"
    ft.setPointSize(20);                                // 字体大小
//    ft.setBold(true);                                 // 设置文字为粗体
    humanlabel->setFont(ft);
    ailabel->setFont(ft);
    updateScore();
    this->update();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeroutslot()));
    timer->start(100);
}

// 绘制
void ReversiMainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 抗锯齿
    painter.setRenderHint(QPainter::Antialiasing, true);
    // 绘制棋盘
    for (int i = 1; i <= chess_size; i++)
        for (int j = 1; j <= chess_size; j++)
            painter.drawRect(i*board_size, j*board_size, board_size, board_size);
    QBrush brush;
    // 样式风格
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    vector<vector<int> > chess = reversi.get_chess();
    // 先画黑棋
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    for (int i = 1; i <= chess_size; i++)
        for (int j = 1; j <= chess_size; j++)
            if (chess[i-1][j-1] == -1)
                painter.drawEllipse(i*board_size+dist, j*board_size+dist, board_size-2*dist, board_size-2*dist);
    if (reversi.get_turn() == -1 && humanplayer == -1)
        painter.drawEllipse(10.5*board_size, 8*board_size+dist, board_size-2*dist, board_size-2*dist);
    else if (reversi.get_turn() == -1)
        painter.drawEllipse(10.5*board_size, 1*board_size+dist, board_size-2*dist, board_size-2*dist);
    // 后画白棋
    brush.setColor(Qt::white);
    painter.setBrush(brush);
    for (int i = 1; i <= chess_size; i++)
        for (int j = 1; j <= chess_size; j++)
            if (chess[i-1][j-1] == 1)
                painter.drawEllipse(i*board_size+dist, j*board_size+dist, board_size-2*dist, board_size-2*dist);
    if (reversi.get_turn() == 1 && humanplayer == 1)
        painter.drawEllipse(10.5*board_size, 8*board_size+dist, board_size-2*dist, board_size-2*dist);
    else if (reversi.get_turn() == 1)
        painter.drawEllipse(10.5*board_size, 1*board_size+dist, board_size-2*dist, board_size-2*dist);
    // 对于玩家可下子位置的提示
    if (reversi.get_turn() == humanplayer && reversi.valid_move(mousex, mousey))
    {
        brush.setColor(Qt::gray);
        painter.setBrush(brush);
        painter.drawEllipse((mousex+1)*board_size+dist, (mousey+1)*board_size+dist, board_size-2*dist, board_size-2*dist);
    }
}

// AI 落子, 每隔一段时间检测是否轮到AI落子
// 调用绘图函数
void ReversiMainWindow::timeroutslot()
{
    // AI下子
    if(reversi.get_turn() == aiplayer1)
    {
        pair<int, int> move_pos = reversiai1.run_AI(reversi);
        int x = move_pos.first;
        int y = move_pos.second;
        if (reversi.valid_move(x, y))
        {
            reversi.put_chess(x, y);
            updateScore();
        }
    }
//    else
//    {
//        pair<int, int> move_pos = reversiai2.run_AI(reversi);
//        int x = move_pos.first;
//        int y = move_pos.second;
//        if (reversi.valid_move(x, y))
//        {
//            reversi.put_chess(x, y);
//            updateScore();
//        }
//    }
    // 人类下子
    else if(clicked && reversi.valid_move(putx, puty))
    {
        reversi.put_chess(putx, puty);
        updateScore();
        clicked = false;
    }
    this->update();
}

// 当轮到人下棋时, 保存点击
void ReversiMainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    if (!clicked && x % board_size  >= dist && x % board_size < board_size - dist &&
        y % board_size >= dist && y % board_size < board_size - dist )
    {
        x = x / board_size - 1;
        y = y / board_size - 1;
        // 如果现在轮到玩家, 并且位置合法, 这下一步棋
        if (reversi.get_turn() == humanplayer && reversi.valid_move(x, y))
        {
            putx = x;
            puty = y;
            clicked = true;
//            reversi.put_chess(x, y);
//            updateScore();
        }
    }
    return ;
}

void ReversiMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();
    mousex = pt.rx();
    mousey = pt.ry();
    if (mousex % board_size  >= dist && mousex % board_size < board_size - dist &&
        mousey % board_size >= dist && mousey % board_size < board_size - dist )
    {
        mousex = mousex / board_size - 1;
        mousey = mousey / board_size - 1;
    }
    else
    {
        mousex = chess_size + 1;
        mousey = chess_size + 1;
    }
}

void ReversiMainWindow::updateScore()
{
    vector<vector<int> > chess = reversi.get_chess();
    int scorew = 0;
    int scoreb = 0;
    for (int i = 0; i < chess_size; i++)
        for (int j = 0; j < chess_size; j++)
        {
            if (chess[i][j] == 1) scorew += 1;
            else if (chess[i][j] == -1) scoreb += 1;
        }
    // 显示分数
    if (humanplayer == 1)
    {
        humanlabel->setText(QString("Human:") + QString::number(scorew));
        ailabel->setText(QString("AI:") + QString::number(scoreb));
    }
    else
    {
        humanlabel->setText(QString("Human:") + QString::number(scoreb));
        ailabel->setText(QString("AI:") + QString::number(scorew));
    }
}

ReversiMainWindow::~ReversiMainWindow()
{
    delete ui;
}
