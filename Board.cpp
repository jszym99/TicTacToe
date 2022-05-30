//
// Created by jszym on 21/05/2022.
//

#include "Board.h"

#define PLAYER 'X'
#define PC 'O'
#define EMPTY ' '

Board::Board(int boardSize, int inLine) {
    length = inLine;
    size = boardSize;
    head = new char[size * size];
    for (int i = 0; i < size * size; i++) {
        head[i] = EMPTY;
    }
}

void Board::move(char player) {
    if (player != PLAYER && player != PC) {
        std::cerr << "Invalid player symbol\n";
    }
    pickField();
    printBoard();
}

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
        count = 0;
        for (int col = 0; col < size - (length - 1); col++) { //columns
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
        count = 0;
        for (int col = length - 1; col < size; col++) { //columns
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

bool Board::ifTie() {
    for(int i = 0; i < size*size; i++){
        if(head[i] == ' '){
            return false;
        }
    }
    return true;
}

int Board::minimax(int depth, bool isMax) {
    //int score = 0;

    // Computer (maximize) won
    if(ifWin(PC))
        return 10-depth;

    // Player (minimizer) won
    if(ifWin(PLAYER))
        return -10+depth;

    if(ifTie())
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i<size; i++)
        {
            for (int j = 0; j<size; j++)
            {
                // Check if cell is empty
                if (head[i*size+j]==EMPTY)
                {
                    // Make the move
                    head[i*size+j] = PC;

                    // Call minimax recursively and choose
                    // the maximum value
                    best = std::max(best,minimax(depth+1, !isMax) );

                    // Undo the move
                    head[i*size+j] = EMPTY;
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<size; i++)
        {
            for (int j = 0; j<size; j++)
            {
                // Check if cell is empty
                if (head[i*size+j] == EMPTY)
                {
                    // Make the move
                    head[i*size+j] = PLAYER;

                    // Call minimax recursively and choose
                    // the minimum value
                    best = std::min(best, minimax( depth+1, !isMax));

                    // Undo the move
                    head[i*size+j] = EMPTY;
                }
            }
        }
        return best;
    }

}

int Board::findBestMove()
{
    int bestVal = -1000;
    int bestMove = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // Check if field is empty
            if (head[i*size+j]==EMPTY)
            {
                // Make the move
                head[i*size+j] = PC;

                // compute evaluation function for this
                // move.
                int moveVal = minimax(0, false);

                // Undo the move
                head[i*size+j] = EMPTY;

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove = i*size+j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
           bestVal);

    head[bestMove] = PC;
    printBoard();

    return bestMove;
}

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
    //std::cout << col-1 << ", " << row-1 << std::endl;
    head[(row - 1) * size + (col - 1)] = 'X';
    //printBoard();
}

int Board::getCol(char col) {
    char Letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

    for (int i = 0; i < size; i++) {
        if (col == Letters[i] || col == letters[i]) {
            return i + 1;
        }
    }
    return 0;
}

int Board::getRow(char row) {
    char num[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < size; i++) {
        if (row == num[i]) {
            return i + 1;
        }
    }
    return 0;
}


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
        /*for(int j = 0; j < size;j++){
            if(j!=0){
                std::cout << "|";
            }
            std::cout << "     ";
        }
        std::cout << "\n";*/
    }
}