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

bool Board::IsFull() {
  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[0].size(); j++) {
      if (matrix_[i][j] == '.') {
        return false;
      }
    }
  }
  return true;
}

bool Board::IsOnlyOne() {
  int p1 = 0;   // black 돌을 가진 플레이어라고 가정
  int p2 = 0;   // white 돌을 가진 플레이어라고 가정

  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[0].size(); j++) {
      if (matrix_[i][j] == '.') {
        continue;
      }
      if (matrix_[i][j] == 'B') {
        p1++;
      }
      if (matrix_[i][j] == 'W') {
        p2++;
      }
    }
  }
  if (p1 != 0 || p2 != 0) {
    return false;
  }
  return true;
}
