#ifndef REVERSIAI_H
#define REVERSIAI_H
#include "reversi.h"


struct Node
{
    int step;                   // 步数
    int alpha;                  // 继承自父亲
    int beta;
    int latest_x;               // 最新一次下的棋子位置
    int latest_y;
    Node(int step = 0, int alpha = -INFVALUE, int beta = INFVALUE, int latest_x = -1, int latest_y = -1)
    {
        this->step = step;
        this->alpha = alpha;
        this->beta = beta;
        this->latest_x = latest_x;
        this->latest_y = latest_y;
    }
};

class ReversiAi
{
    private:
        int search_depth;                                               // 实际搜索层数，前期与设定搜索层数一致，终盘时增大。
        int init_search_depth;                                          // 设定搜索层数
        int c1;                                                         // 行动力
        int c2;                                                         // 稳定子
        int c3;                                                         // 棋盘位置权重
    public:
        ReversiAi(int init_search_depth = 8, int c1 = 0, int c2 = 0, int c3 = 1);
        pair<int, int> run_AI(Reversi reversi);      // 1 表示白棋玩家，-1 表示黑棋玩家
        Node alphaBeta(Reversi &reversi, Node node);
};

#endif // REVERSIAI_H
