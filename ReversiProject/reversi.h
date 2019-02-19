#ifndef REVERSI_H
#define REVERSI_H
#define INFVALUE 50000
#define WINVALUE 40000

#include <vector>
#include <utility>
using namespace std;

// 黑白棋棋盘
class Reversi
{
  private:
    int chess_size;                                                     // 棋盘大小
    vector<vector<int> > chess;                                         // 棋盘存储结构
    vector<pair<int, int> > childlist;                                  // 当前可下子位置
    int turn;                                                           // 表示当前下棋手,-1黑子,1白子
    bool over;                                                          // 表示游戏是否结束
    int winner;                                                         // 表示当前赢家
    int chess_num;                                                      // 转换棋权
    void change_turn() {turn *= -1;}
    // 计算当前可下子位置
    vector<pair<int, int> > get_sons();
  public:
    // 给定棋盘和棋手
    Reversi(int turn = -1, int chess_size = 8);
    void init(int chess_size, int turn, vector<vector<int> > chess);
    // 棋子数目
    int get_chessnum() { return chess_num; }
    // 空位数目
    int get_spacenum() { return chess_size * chess_size - chess_num; }
    // 返回下棋方
    int get_turn() { return turn; }
    // 获取棋盘数组
    vector<vector<int> > get_chess() { return chess; }
    // 返回可下子位置
    vector<pair<int, int> > get_childlist() { return childlist; }
    // 双方都无法下子时游戏结束
    bool is_over() { return over; }
    // 取得获胜方. 1 表示白子获胜, -1 表示黑子获胜, 0表示还未获胜或平局.
    int get_winner() { return winner; }
    // 判断(x, y)是否在棋盘内
    bool in_chess(int x, int y);
    // 棋子值
    int chess_value();
    // 估价值，为棋盘每个位置赋值不同的权值. c1表示行动力, c2表示稳定子, c3表示棋盘位置.
    int estimate_value(int c1 = 0, int c2 = 0, int c3 = 1);
    // 计算边缘行稳定性
    int cal_stability_row(int row);
    // 计算边缘列稳定性
    int cal_stability_col(int col);
    // 下子
    void put_chess(int x, int y);
    // 判断下子位置是否有效
    bool valid_move(int x, int y);
};



#endif // REVERSI_H
