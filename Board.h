//
// Created by jszym on 21/05/2022.
//

#ifndef TICTACTOE_BOARD_H
#include <iostream>
#define TICTACTOE_BOARD_H


class Board {
private:
    char * head;
    int size;
    int length;
    int getCol(char col);
    int getRow(char row);
public:
    Board(int size, int inLine);
    void printBoard();
    void pickField();
    void move(char player);
    bool ifWin(char player);
    bool ifTie();
    int minimax(int depth, bool isMax);
    int findBestMove();

};


#endif //TICTACTOE_BOARD_H
