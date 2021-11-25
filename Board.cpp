#include <iostream>
#include <string>
#include <vector>
#include "Board.h"

Board* Board::instance_ = NULL;
Board* Board::GetInstance() {
    if (instance_ == NULL) {
        instance_ = new Board();
    }
    return instance_;
}

void Board::setSize(int size) {     //벡터의 size by size 설정 및 '.'로 값 초기화
    matrix_ = std::vector<std::vector<char>> (size, std::vector<char>(size,'.'));
    int value = size / 2;
    matrix_[value][value] = 'B';
    matrix_[value-1][value-1] = 'B';
    matrix_[value][value-1] = 'W';
    matrix_[value-1][value] = 'W';
}

void Board::printBoard() {                  //보드의 상태를 출력하는 함수
    for(int i = 0; i < matrix_.size(); i++) {
        for (int j = 0; j < matrix_[0].size(); j++) {
                std::cout << matrix_[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void Board::putStone(int x, int y, char color) {            //x, y
    matrix_[x][y] = color;
}

std::vector<std::vector<char>> Board::getmatrix() {
    return this->matrix_;
}
Board::Board() {}


