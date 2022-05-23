#include <iostream>
#include <string>
#include "Board.h"


int main() {
    int boardSize = 0;
    while(boardSize < 3 || boardSize > 5){
        std::cout << "Podaj rozmiar planszy (od 3 do 5)\n";
        std::cin >> boardSize;
        while(!std::cin.good())
        {
            std::cout << "Podana wartosc nie jest liczba\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            std::cout << "Podaj rozmiar planszy\n";
            std::cin >> boardSize;
        }
    }
    Board board(boardSize);
    board.printBoard();
    board.pickField();

    //int col = getCol(field[0]);
    //int row = field[1]-48;
    //std::cout << col << " " << row << std::endl;

}
