//
// Created by jszym on 21/05/2022.
//

#include "Board.h"

#define PLAYER 'X'
#define PC 'O'
#define EMPTY ' '
#define MAXDEPTH 25

//! Constructor
Board::Board(int boardSize, int inLine) {
    length = inLine;
    size = boardSize;
    head = new char[size * size];
    for (int i = 0; i < size * size; i++) {
        head[i] = EMPTY;
    }
}
//! Function clears the board
void Board::clear() {
    for (int i = 0; i < size * size; i++) {
        head[i] = EMPTY;
    }
}

//! Function for players move
void Board::move(char player) {
    if (player != PLAYER && player != PC) {
        std::cerr << "Invalid player symbol\n";
    }
    pickField();
    printBoard();
}

//! Checks if any player has won
bool Board::ifWin(char player) {
    int count = 0;

    //check rows
    for (int row = 0; row < size; row++) {
        count = 0;
        for (int col = 0; col < size; col++) {
            if (head[row * size + col] == player) {
                count++;
            } else {
                count = 0;
            }
            if (count == length) {
                return true;
            }
        }
    }

    //check columns
    for (int col = 0; col < size; col++) {
        count = 0;
        for (int row = 0; row < size; row++) {
            if (head[row * size + col] == player) {
                count++;
            } else {
                count = 0;
            }
            if (count == length) {
                return true;
            }
        }
    }


    //check diagonally top-left->bottom-right
    for (int row = 0; row < size - (length - 1); row++) { //rows
        for (int col = 0; col < size - (length - 1); col++) { //columns
            count = 0;
            for (int i = 0; i < length; i++) {
                if (head[(row + i) * size + (col + i)] == player) {
                    count++;
                } else {
                    count = 0;
                }
                if (count == length) {
                    return true;
                }
            }
        }
    }


    //check diagonally top-right->bottom-left
    for (int row = 0; row < size - (length - 1); row++) { //rows
        for (int col = length - 1; col < size; col++) { //columns
            count = 0;
            for (int i = 0; i < length; i++) {
                if (head[(row + i) * size + (col - i)] == player) {
                    count++;
                } else {
                    count = 0;
                }
                if (count == length) {
                    return true;
                }
            }
        }
    }

    return false;
}

//! Checks if game ended with a tie
bool Board::ifTie() {
    for (int i = 0; i < size * size; i++) {
        if (head[i] == ' ') {
            return false;
        }
    }
    return true;
}

//! Function finding best move for computer
int Board::minimax(int depth, bool maximizer, int alpha, int beta) {

    // Depth limit
    if (depth >= MAXDEPTH) {
        if (ifTie())
            return 0;

        if (maximizer)
            return 100 - depth;

        if (!maximizer)
            return -100 + depth;
    }

    // Computer (maximize) won
    if (ifWin(PC))
        return 100 - depth;

    // Player (minimizer) won
    if (ifWin(PLAYER))
        return -100 + depth;

    if (ifTie())
        return 0;

    // Computers move (maximizing)
    if (maximizer) {
        int best = -1000;

        // For each field
        for (int i = 0; i < size * size; i++) {
            // Check if field is empty
            if (head[i] == EMPTY) {

                // Place a marker
                head[i] = PC;

                // Call recursively
                int val = minimax(depth + 1, !maximizer, alpha, beta);
                // Pick best score
                best = std::max(best, val);
                alpha = std::max(alpha, best);

                // Clear the field
                head[i] = EMPTY;
            }
            // Stop if better move has been already found
            if (alpha >= beta)
                break;
        }
        return best;
    }

    // Players move (minimizing)
    else {
        int best = 1000;

        // For each field
        for (int i = 0; i < size * size; i++) {
            // Check if field is empty
            if (head[i] == EMPTY) {

                // Place a marker
                head[i] = PLAYER;

                // Call recursively
                int val = minimax(depth + 1, !maximizer, alpha, beta);
                // Pick best score
                best = std::min(best, val);
                beta = std::min(beta, best);

                // Clear the field
                head[i] = EMPTY;
            }
            // Stop if better move has been already found
            if (alpha >= beta)
                break;
        }
        return best;
    }

}

//! Function searching for the best possible move for computer
int Board::findBestMove() {
    int bestMoveVal = -1000;
    int bestMove = -1;

    // Find best move for each field
    for (int i = 0; i < size * size; i++) {
        // Check if field is empty
        if (head[i] == EMPTY) {
            // Place a marker
            head[i] = PC;

            // Find best move for this field
            int moveVal = minimax(0, false, -1000, 1000);

            // Clear the field
            head[i] = EMPTY;

            // Pick the best move
            if (moveVal > bestMoveVal) {
                bestMove = i;
                bestMoveVal = moveVal;
            }
        }
    }

    head[bestMove] = PC;
    printBoard();

    return bestMove;
}

//! Function taking field coordinates from player
void Board::pickField() {
    char field[2];
    std::cout << "Wybierz pole (np. A1):";
    std::cin >> field;
    int col = getCol(field[0]);
    int row = getRow(field[1]);
    while (!std::cin.good() || !col || !row) {
        std::cout << "Wartosc niepoprawna\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Wybierz pole (np. A1):";
        std::cin >> field;
        col = getCol(field[0]);
        row = getRow(field[1]);
    }
    while (head[(row - 1) * size + (col - 1)] != EMPTY) {
        std::cout << "Pole zajete\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Wybierz inne pole:";
        std::cin >> field;
        col = getCol(field[0]);
        row = getRow(field[1]);
    }
    head[(row - 1) * size + (col - 1)] = 'X';
}

//! Function translates column letters to number
int Board::getCol(char col) const {
    char Letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

    for (int i = 0; i < size; i++) {
        if (col == Letters[i] || col == letters[i]) {
            return i + 1;
        }
    }
    return 0;
}

//! Function translates row number character to number
int Board::getRow(char row) const {
    char num[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < size; i++) {
        if (row == num[i]) {
            return i + 1;
        }
    }
    return 0;
}

//! Function displays game board
void Board::printBoard() {
    for (int i = 0; i < size; i++) {
        // Print vertical line
        if (i != 0) {
            for (int j = 0; j < size; j++) {
                if (j != 0) {
                    std::cout << "|";
                } else {
                    std::cout << "   ";
                }
                std::cout << "---";
            }
        } else {
            for (int j = 0; j < size; j++) {
                if (j == 0) {
                    std::cout << "  ";
                }
                std::cout << "  " << char(65 + j) << " ";
            }
        }
        std::cout << "\n";
        std::cout << i + 1 << "  ";
        // Print data
        for (int j = 0; j < size; j++) {
            if (j != 0) {
                std::cout << "|";
            }
            std::cout << " " << head[i * size + j] << " ";
        }
        std::cout << "\n";
    }
}