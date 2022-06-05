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

    //! Function translates column letters to number
    int getCol(char col) const;
    //! Function translates row number character to number
    int getRow(char row) const;
    //! Function finding best move for computer
    int minimax(int depth, bool maximizer, int alpha, int beta);
    //! Function taking field coordinates from player
    void pickField();
public:
    //! Constructor
    Board(int size, int inLine);
    //! Function displays game board
    void printBoard();
    //! Function for players move
    void move(char player);
    //! Checks if game ended with a tie
    bool ifTie();
    //! Checks if any player has won
    bool ifWin(char player);
    //! Function searching for the best possible move for computer
    int findBestMove();
    //! Function clears the board
    void clear();

};


#endif //TICTACTOE_BOARD_H
