#include <iostream>
#include "Board.h"

Board* Board::instance_ = nullptr;

Board* Board::GetInstance() {
  if (instance_ == nullptr) { instance_ = new Board(); }
  return instance_;
}

Board::Board() {}

void Board::SetSize(int size) {  // 벡터의 size by size 설정 및 '.'로 값 초기화
  matrix_ = std::vector<std::vector<char>>(size, std::vector<char>(size, '.'));
  matrix_[size / 2][size / 2] = 'B';
  matrix_[size / 2 - 1][size / 2 - 1] = 'B';
  matrix_[size / 2][size / 2 - 1] = 'W';
  matrix_[size / 2 - 1][size / 2] = 'W';
}

void Board::PutStone(int row, int col, char color) {  // x, y
  matrix_[row][col] = color;
}

void Board::PrintBoard() {  // 보드의 상태를 출력하는 함수
  std::cout << "\\  ";
  for (int i = 0; i < matrix_.size(); i++) {
    std::cout << i << "  ";
  }
  std::cout << std::endl;
  for (int i = 0; i < matrix_.size(); i++) {
    std::cout << i << "  ";
    for (int j = 0; j < matrix_[0].size(); j++) {
      std::cout << matrix_[i][j] << "  ";
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<char>> Board::Getmatrix() { return matrix_; }

bool Board::IsFullBoard() {
  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[0].size(); j++) {
      if (matrix_[i][j] == '.') {
        return false;
      }
    }
  }
  return true;
}

bool Board::HasOnlyOneType() {
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

void Board::RestoreBoard() {
  for (int i = 0; i < matrix_.size(); i++) {
    for (int j = 0; j < matrix_[i].size(); j++) {
      if (matrix_[i][j] == '*') {
        this->PutStone(i, j, '.');
      }
    }
  }
}

