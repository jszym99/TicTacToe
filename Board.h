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
    int getCol(char col);
    int getRow(char row);
public:
    Board(int size);
    void printBoard();
    void pickField();
};


#endif //TICTACTOE_BOARD_H
