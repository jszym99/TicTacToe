#include <iostream>
#include <string>
#include "Board.h"


int main() {
    int boardSize = 0;
    int inLine = 0;

    //Board size
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
    while(inLine < 3 || inLine > 5){
        std::cout << "Podaj dlugosc ciagu znakow (od 3 do 5)\n";
        std::cin >> inLine;
        while(!std::cin.good())
        {
            std::cout << "Podana wartosc nie jest liczba\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            std::cout << "Podaj dlugosc ciagu znakow (od 3 do 5)\n";
            std::cin >> inLine;
        }
    }
    Board board(boardSize, inLine);
    board.printBoard();
    while(!board.ifWin('X') && !board.ifWin('O') && !board.ifTie()){
        board.move('X');
        if(board.ifWin('X'))
            break;
        int bestMove = board.findBestMove();
        std::cout << "Best move: " << bestMove << std::endl;
        if(board.ifWin('O'))
            break;
    }

    //int col = getCol(field[0]);
    //int row = field[1]-48;
    //std::cout << col << " " << row << std::endl;

}
