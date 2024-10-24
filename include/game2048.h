#ifndef GAME2048_H
#define GAME2048_H

#include <vector>

class Game2048 {
public:
    Game2048(int boardSize);                   // 构造函数
    void resetGame();             // 重置游戏
    void play();                  // 开始游戏

private:
    const int SIZE;               // 棋盘大小
    int score;                    // 当前得分

    std::vector<std::vector<int> > board; //棋盘

    void displayBoard();          // 显示棋盘
    bool isGameOver();            // 判断游戏是否结束
    void addRandomTile();         // 添加随机数字块
    bool moveLeft();              // 向左移动
    bool moveRight();             // 向右移动
    bool moveUp();                // 向上移动
    bool moveDown();              // 向下移动
    void rotateBoard();           // 逆时针旋转棋盘
};

#endif // GAME2048_H
