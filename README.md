# Reversi-Game
基于Min-Max算法的黑白棋游戏

## 设计原理
AI的分析过程有两个阶段。
1. 第一个阶段是前期搜索阶段，AI以固定搜索深度进行搜索。对于棋盘的局势优劣的计算是从行动力，稳定子，棋盘权重三个方面来分析的。  
这时AI通过深度搜索进行建树，并且依据Min-Max算法计算当前最优下子点，建树过程中根据Alpha-Beta进行剪枝缩小搜索空间。  
2. 第二个阶段是终盘搜索阶段，AI搜到棋盘下满的时刻。 并且根据胜负判断局势。  
这时由于棋盘中的棋子数量减少，AI可以直接搜到棋盘下满的情况，这就相当于可以得出胜负了，因此这时根据最后的胜负情况来判断局势优劣情况，同样依据Min-Max算法配合Alpha-Beta剪枝计算最优的下子点。

## 目录 
-ReversiProject_boxed.exe 项目可执行文件   
-ReversiProject 项目程序文件  
--reversi.h reversi.cpp    棋盘文件，主要是Reversi类的设计。实现了棋盘逻辑，包括下子，判断落子方，判断胜负等功能  
--reversiai.h reversiai.cpp    AI文件，主要是ReversiAi类的设计。实现了AI棋手，主要从行动力，稳定子，棋盘权重三个方面分析棋盘优劣，使用Min-Max算法搜索最优下子位置  
--reversimainwindow.h reversimainwindow.cpp reversimainwindow.ui    游戏界面文件，ReversiMainWindow类的设计。实现棋盘的显示  
--selectdialog.h selectdialog.cpp selectdialog.ui    开始界面文件，SelectDialog类的设计。用于选择先后手及难度  
