#include "game2048.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

Game2048::Game2048(int board_size) : SIZE(board_size), score(0) {
    std::srand(static_cast<unsigned>(std::time(0))); // 初始化随机数种子
    board = std::vector<std::vector<int> >(SIZE, std::vector<int>(SIZE));
    resetGame();
}


void Game2048::resetGame() {
    // 初始化棋盘为空
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            board[i][j] = 0;

    score = 0;
    // 生成两个初始块
    addRandomTile();
    addRandomTile();
}

void Game2048::play() {
    char input;
    while (!isGameOver()) {
        displayBoard();
        std::cout << "Use W (up), A (left), S (down), D (right) to move. Press Q to quit.\n";
        std::cin >> input;

        if (input == 'Q' || input == 'q') {
            std::cout << "Game Quit. Final Score: " << score << "\n";
            break;
        }

        bool moved = false;
        switch (input) {
            case 'W':
            case 'w':
                moved = moveUp();
                break;
            case 'A':
            case 'a':
                moved = moveLeft();
                break;
            case 'S':
            case 's':
                moved = moveDown();
                break;
            case 'D':
            case 'd':
                moved = moveRight();
                break;
            default:
                std::cout << "Invalid input, please use W, A, S, D or Q.\n";
                continue;
        }

        if (moved) {
            addRandomTile();
        }
    }

    if (isGameOver()) {
        std::cout << "Game Over. Final Score: " << score << "\n";
    }
}

void Game2048::displayBoard() {
    std::cout << "Score: " << score << "\n";
    for (int i = SIZE - 1; i >= 0; --i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                std::cout << std::setw(5) << ".";
            } else {
                std::cout << std::setw(5) << board[i][j];
            }
        }
        std::cout << "\n";
    }
}

bool Game2048::isGameOver() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) return false;  // 还有空位
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return false;  // 可以向下合并
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return false;  // 可以向右合并
        }
    }
    return true;  // 没有可合并的块，游戏结束
}

void Game2048::addRandomTile() {
    std::vector<std::pair<int, int> > emptyTiles;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                emptyTiles.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!emptyTiles.empty()) {
        int index = std::rand() % emptyTiles.size();
        int value = (std::rand() % 10 == 0) ? SIZE : 2;  // 90% 概率为 2，10% 概率为 4
        board[emptyTiles[index].first][emptyTiles[index].second] = value;
    }
}

bool Game2048::moveLeft() {
    bool moved = false;
    for (int i = 0; i < SIZE; ++i) {
        std::vector<int> merged(SIZE, 0); 
        for (int j = 1; j < SIZE; ++j) {
            if (board[i][j] != 0) {
                int k = j;
                while (k > 0 && board[i][k - 1] == 0) {
                    board[i][k - 1] = board[i][k];
                    board[i][k] = 0;
                    k--;
                    moved = true;
                }
                if (k > 0 && board[i][k - 1] == board[i][k] && merged[k - 1] == 0) {
                    board[i][k - 1] *= 2;
                    score += board[i][k - 1];
                    board[i][k] = 0;
                    merged[k - 1] = 1;
                    moved = true;
                }
            }
        }
    }
    return moved;
}

bool Game2048::moveRight() {
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    return moved;
}

bool Game2048::moveUp() {
    rotateBoard();
    rotateBoard();
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    return moved;
}

bool Game2048::moveDown() {
    rotateBoard();
    bool moved = moveLeft();
    rotateBoard();
    rotateBoard();
    rotateBoard();
    return moved;
}

void Game2048::rotateBoard() {
    // 逆时针旋转棋盘90度
    int temp[SIZE][4];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[i][j] = board[j][SIZE - 1 - i];
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = temp[i][j];
        }
    }
}
