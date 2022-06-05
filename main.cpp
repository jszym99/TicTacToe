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
    // Symbols in line
    while(inLine < 3 || inLine > 5){
        std::cout << "Podaj dlugosc ciagu znakow (od 3 do 5 oraz nie wieksza od rozmiaru planszy)\n";
        std::cin >> inLine;
        while(!std::cin.good())
        {
            std::cout << "Podana wartosc nie jest liczba\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            std::cout << "Podaj dlugosc ciagu znakow (od 3 do 5)\n";
            std::cin >> inLine;
        }
        while(inLine > boardSize)
        {
            std::cout << "Podana dlugosc jest za duza\n";
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            std::cout << "Podaj dlugosc ciagu znakow (od 3 do 5 oraz nie wieksza od rozmiaru planszy)\n";
            std::cin >> inLine;
        }
    }

    std::string cont;

    Board board(boardSize, inLine);
    while(1) {
        board.printBoard();
        while (!board.ifWin('X') && !board.ifWin('O') && !board.ifTie()) {

            // Players move
            board.move('X');
            if (board.ifWin('X')) {
                std::cout << "Wygrales!!!" << std::endl;
                break;
            }

            // If game ended with a tie
            if(board.ifTie()){
                std::cout << "Remis" << std::endl;
                break;
            }

            // Computers move
            board.findBestMove();

            if (board.ifWin('O')){
                std::cout << "Komputer wygral" << std::endl;
                break;
            }
        }
        std::cout << "Czy chcesz zagrac ponownie? [T/N]" << std::endl;
        std::cin >> cont;
        if(cont == "nie" || cont == "n" || cont == "Nie" || cont == "N"){
            break;
        }else{
            board.clear();
        }
    }
}
