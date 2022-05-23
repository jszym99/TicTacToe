//
// Created by jszym on 21/05/2022.
//

#include "Board.h"

Board::Board(int boardSize) {
    size = boardSize;
    head = new char[size*size];
    for(int i=0; i < size*size;i++){
        head[i] = ' ';
    }
}

void Board::pickField() {
    char field[2];
    std::cout << "Wybierz pole (np. A1): ";
    std::cin >> field;
    while(!std::cin.good())
    {
        std::cout << "Wartość niepoprawna\n";
        std::cin.clear();
        std::cin.ignore(INT_MAX,'\n');
        std::cout << "Wybierz pole (np. A1): ";
        std::cin >> field;
    }
}

int Board::getCol(char col){
    char Letters[] = {'A','B','C','D','E','F','G','H','I'};
    char letters[] = {'a','b','c','d','e','f','g','h','i'};

    for(int i = 0; i < size; i++){
        if(col == Letters[i] || col == letters[i]){
            return i+1;
        }
    }
    return 0;
}
int Board::getRow(char row){

}


void Board::printBoard() {
    for(int i = 0; i < size;i++){
        // Print vertical line
        if(i!=0){
            for(int j = 0; j < size;j++){
                if(j!=0){
                    std::cout << "|";
                }else{
                    std::cout << "   ";
                }
                std::cout << "---";
            }
        } else{
            for(int j = 0; j < size;j++){
                if(j==0){
                    std::cout << "  ";
                }
                std::cout << "  " << char(65+j) << " ";
            }
        }
        std::cout << "\n";
        std::cout << i+1 << "  ";
        // Print data
        for(int j = 0; j < size;j++){
            if(j!=0){
                std::cout << "|";
            }
            std::cout << " " << head[i*size+j] << " ";
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