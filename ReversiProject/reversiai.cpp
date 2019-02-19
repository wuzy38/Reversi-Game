#include "reversiai.h"
#include <QDebug>

ReversiAi::ReversiAi(int init_search_depth, int c1, int c2, int c3)
{
    this->init_search_depth = init_search_depth;
    this->c1 = c1;
    this->c2 = c2;
    this->c3 = c3;
}

pair<int, int> ReversiAi::run_AI(Reversi reversi)      // 1 表示白棋玩家，-1 表示黑棋玩家
{
    Node node;
    int space_num = reversi.get_spacenum();
    int chess_num = reversi.get_chessnum();
    int chess_tor = 4;                      // 在棋子数量小于容忍度时, 加大搜索深度
    int space_tor = 15;                     // 在剩余空位小于容忍度时, 搜到底
    // 可以在空位较少的情况下增加搜索深度, 搜到底
    if (space_num <= space_tor) search_depth = init_search_depth + space_tor;
    else if (chess_num <= chess_tor) search_depth = init_search_depth + 2;
    else search_depth = init_search_depth;
    Node next_node = alphaBeta(reversi, node);
    qDebug() << next_node.alpha << "    " << next_node.latest_y+1 << " " << next_node.latest_x+1;
    return make_pair(next_node.latest_x, next_node.latest_y);
}

Node ReversiAi::alphaBeta(Reversi &reversi, Node node)
{
    if (node.step >= search_depth)  // 搜索结束
    {
        node.alpha = reversi.estimate_value(c1, c2, c3);
        node.beta = node.alpha;
        return node;
    }
    else if (reversi.is_over()) // 胜负已分
    {
        node.alpha = reversi.get_winner() * WINVALUE;
        node.beta = node.alpha;
        return node;
    }
    vector<pair<int, int> > childlist = reversi.get_childlist();
    int step = node.step;
    int player = reversi.get_turn();
    for (int i = 0; i < childlist.size(); i++)                          // 判断node应该走哪步
    {
        // childlist[i] 表示现在可以走的下一步棋。next_node 表示走了childlist这一步后, 敌手会走的棋
        Node child = node;
        child.latest_x = childlist[i].first;
        child.latest_y = childlist[i].second;
        child.step = step + 1;
        // 复制棋盘, 一个时间开销
        Reversi next_reversi = reversi;
        next_reversi.put_chess(child.latest_x, child.latest_y);
        Node next_node = alphaBeta(next_reversi, child);
        if (player == 1 && next_node.beta > node.alpha)                 // 最小值节点的beta就是它的值
        {
            node = child;
            node.alpha = next_node.beta;
            if (node.beta <= node.alpha) break;
        }
        else if(player == -1 && next_node.alpha < node.beta)
        {
            node = child;
            node.beta = next_node.alpha;
            if (node.beta <= node.alpha) break;
        }
    }
    // 由于无法知道父亲是什么节点, 返回时应该令alpha = beta
    if (player == 1) node.beta = node.alpha;
    else node.alpha = node.beta;
    return node;
}
