#include <iostream>
#include "Board.h"

Board* Board::instance_ = nullptr;
Board* Board::GetInstance() {
  if (instance_ == nullptr) { instance_ = new Board(); }
  return instance_;
}
Board::Board() {}
void Board::SetSize(int size) {     //벡터의 size by size 설정 및 '.'로 값 초기화
  matrix_ = std::vector<std::vector<char>>
   (size, std::vector<char>(size, '.'));
  int val = size / 2;
  matrix_[val][val] = 'B';
  matrix_[val - 1][val - 1] = 'B';
  matrix_[val][val - 1] = 'W';
  matrix_[val - 1][val] = 'W';
}
void Board::PutStone(int x, int y, char color) {            //x, y
  matrix_[x][y] = color;
}
void Board::PrintBoard() {                  //보드의 상태를 출력하는 함수
  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[0].size(); j++) {
      std::cout << matrix_[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}
std::vector<std::vector<char>> Board::Getmatrix() { return matrix_; }

