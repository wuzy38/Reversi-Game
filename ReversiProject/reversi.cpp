#include "reversi.h"

const int c_w[10] = {15, -9, 5, 4, -12, -4, -3, 5, 2, 1};
const int chess_weight[8][8] = {
    {c_w[0], c_w[1], c_w[2], c_w[3], c_w[3], c_w[2], c_w[1], c_w[0]},
    {c_w[1], c_w[4], c_w[5], c_w[6], c_w[6], c_w[5], c_w[4], c_w[1]},
    {c_w[2], c_w[5], c_w[7], c_w[8], c_w[8], c_w[7], c_w[5], c_w[2]},
    {c_w[3], c_w[6], c_w[8], c_w[9], c_w[9], c_w[8], c_w[6], c_w[3]},
    {c_w[3], c_w[6], c_w[8], c_w[9], c_w[9], c_w[8], c_w[6], c_w[3]},
    {c_w[2], c_w[5], c_w[7], c_w[8], c_w[8], c_w[7], c_w[5], c_w[2]},
    {c_w[1], c_w[4], c_w[5], c_w[6], c_w[6], c_w[5], c_w[4], c_w[1]},
    {c_w[0], c_w[1], c_w[2], c_w[3], c_w[3], c_w[2], c_w[1], c_w[0]}
};

// 计算当前可下子位置
vector<pair<int, int> > Reversi::get_sons()
{
    vector<pair<int, int> > childlist;
    for (int x = 0; x < chess.size(); x++)
        for (int y = 0; y < chess[x].size(); y++)
            if (chess[x][y] == 0)
            {
                bool flag = false;
                for (int i = -1; i <= 1 && !flag; i++)
                    for (int j = -1; j <= 1 && !flag; j++)
                    {
                        int count = 1;
                        while (in_chess(x+i*count, y+j*count) && chess[x+i*count][y+j*count] == -turn)
                            count += 1;
                        if (count > 1 && in_chess(x+i*count, y+j*count) && chess[x+i*count][y+j*count] == turn)
                        {
                            childlist.push_back(make_pair(x, y));
                            flag = true;
                        }
                    }
            }
    return childlist;
}

// 给定棋盘和棋手
Reversi::Reversi(int turn, int chess_size)
: chess(chess_size, vector<int>(chess_size, 0))
{
    this->chess_size = chess_size;
    chess[chess_size/2][chess_size/2] = 1;
    chess[chess_size/2-1][chess_size/2-1] = 1;
    chess[chess_size/2][chess_size/2-1] = -1;
    chess[chess_size/2-1][chess_size/2] = -1;
    this->turn = turn;
    over = false;
    winner = 0;
    chess_num = 4;
    childlist = get_sons();
}

void Reversi::init(int chess_size, int turn, vector<vector<int> > chess)
{
    this->chess_size = chess_size;
    this->chess = chess;
    this -> turn = turn;
    over = false;
    winner = 0;
    childlist = get_sons();
}

// 判断(x, y)是否在棋盘内
bool Reversi::in_chess(int x, int y)
{
    if (x >= 0 && x < chess_size && y >= 0 && y < chess_size) return true;
    return false;
}

// 棋子值
int Reversi::chess_value()
{
    int value = 0;
    for (int i = 0; i < chess_size; i++)
        for (int j = 0; j < chess_size; j++)
            value += chess[i][j];
    return value;
}

// 估价值，为棋盘每个位置赋值不同的权值
int Reversi::estimate_value(int c1, int c2, int c3)
{
    // 行动力 c1_value * c1
    int c1_value = turn * childlist.size();
    // 稳定子 只计算边界稳定子 c2_value * c2
    int c2_value = 0;
    // 在所在边上，要么一个方向是边界或自身稳定点，要么两个方向都是对方稳定点
    // 分成4段, 上下左右
    c2_value += (cal_stability_row(0)+cal_stability_row(chess_size-1));
    c2_value += (cal_stability_col(0)+cal_stability_col(chess_size-1));
    c2_value -= (chess[0][0] + chess[chess_size-1][chess_size-1]);
    c2_value -= (chess[0][chess_size-1] + chess[chess_size-1][0]);
    // 棋盘权重 c3_value * c3
    int c3_value = 0;
    for (int i = 0; i < chess_size; i++)
        for (int j = 0; j < chess_size; j++)
        {
            c3_value += chess[i][j] * chess_weight[i][j];
        }
    int value = c1 * c1_value + c2 * c2_value + c3 * c3_value;
    return value;
}

// 计算边缘行稳定性
int Reversi::cal_stability_row(int row)
{
    if (chess[row][0] != 0 && chess[row][chess_size-1] != 0)
    {

        int v0 = 1;
        int i = 1;
        for (i = 1; i < chess_size && chess[row][i] != 0; i++)
            if (chess[row][i] == chess[row][0])
                v0 += 1;
        if (i == chess_size)
            return v0 * chess[row][0] + (chess_size - v0) * chess[row][chess_size-1];
        else
        {
            int v1 = 1;
            for (int j = chess_size-2; j > 0 && chess[row][j] != 0; j--)
                if (chess[row][j] == chess[row][chess_size-1])
                    v1 += 1;
            return v0 * chess[row][0] + v1 * chess[row][chess_size-1];
        }
    }
    else if (chess[row][0] != 0)
    {
        int v0 = 1;
        for (int i = 1; i < chess_size && chess[row][i] != 0; i++)
            if (chess[row][i] == chess[row][0])
                v0 += 1;
        return v0*chess[row][0];
    }
    else if (chess[row][chess_size-1] != 0)
    {
        int v1 = 1;
        for (int i = chess_size-2; i > 0 && chess[row][i] != 0; i--)
            if (chess[row][i] == chess[row][chess_size-1])
                v1 += 1;
        return v1 * chess[row][chess_size-1];
    }
    else
        return 0;
}

// 计算边缘列稳定性
int Reversi::cal_stability_col(int col)
{
    if (chess[0][col] != 0 && chess[chess_size-1][col] != 0)
    {
        int v0 = 1;
        int i = 1;
        for (i = 1; i < chess_size && chess[i][col] != 0; i++)
            if (chess[i][col] == chess[0][col])
                v0 += 1;
        if (i == chess_size)
            return v0 * chess[0][col] + (chess_size - v0) * chess[chess_size-1][col];
        else
        {
            int v1 = 1;
            for (int j = chess_size-2; j > 0 && chess[j][col] != 0; j--)
                if (chess[j][col] == chess[chess_size-1][col])
                    v1 += 1;
            return v0 * chess[0][col] + v1 * chess[chess_size-1][col];
        }
    }
    else if (chess[0][col] != 0)
    {
        int v0 = 1;
        for (int i = 1; i < chess_size && chess[i][col] != 0; i++)
            if (chess[i][col] == chess[0][col])
                v0 += 1;
        return v0*chess[0][col];
    }
    else if (chess[chess_size-1][col] != 0)
    {
        int v1 = 1;
        for (int i = chess_size-2; i > 0 && chess[i][col] != 0; i--)
            if (chess[i][col] == chess[chess_size-1][col])
                v1 += 1;
        return v1 * chess[chess_size-1][col];
    }
    else
        return 0;
}

// 下子
void Reversi::put_chess(int x, int y)
{
    chess[x][y] = turn;
    chess_num += 1;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            int count = 1;
            while (in_chess(x+i*count, y+j*count) && chess[x+i*count][y+j*count] == -turn)
                count += 1;
            if (count > 1 && in_chess(x+i*count, y+j*count) && chess[x+i*count][y+j*count] == turn)
                for (int k = 1; k < count; k++)
                    chess[x+i*k][y+j*k] = turn;
        }
    change_turn();
    childlist = get_sons();
    if (childlist.empty())
    {
        change_turn();
        childlist = get_sons();
        if (childlist.empty())      // 双方都无法下子, 游戏结束
        {
            over = true;
            int score = chess_value();
            if (score > 0) winner = 1;
            else if (score < 0) winner = -1;
            else winner = 0;
        }
    }
    return ;
}

// 判断下子位置是否有效
bool Reversi::valid_move(int x, int y)
{
    for (int i = 0; i < childlist.size(); i++)
        if (childlist[i].first == x && childlist[i].second == y) return true;
    return false;
}
