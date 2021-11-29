#include <iostream>
#include <string>
#include "Player.h"
#include "Board.h"
#include "Judge.h"

Judge* Judge::instance_ = nullptr;
Judge* Judge::GetInstance() {
  if (instance_ == nullptr) { instance_ = new Judge(); }
  return instance_;
}
Judge::Judge() {}
void Judge::SetBoard(Board* board) { board_ = board; } //보드와 심판 연결
void Judge::SetPlayers(Player* p1, Player* p2) {       //플레이어들과 심판 연결
  p1_ = p1;
  p2_ = p2;
}
bool Judge::GameFinish() {
  // 한 차례에 양쪽 모두 서로 차례를 넘겨야 하는 경우
  // checkCnt = 0이 두번 연속일 때
  // 위의 경우가 아니면 false
  return false;
}
bool Judge::CheckValid(int row, int col) {

}
bool Judge::CheckCnt() {
  int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
  int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
  // 8 방향 점검
  // 아래, 위, 왼, 오, 왼아, 왼위, 오아, 오위
}
void Judge::PlayerInput() {
  // std::string p1_name, p2_name;
  // char p1_color, p2_color;
  // int board_size, row, col;

  // std::cout << "Enter the size of board: " << std::endl;
  // std::cin >> board_size;
  // std::cout << "Enter Player1's name: " << std::endl;
  // std::cin >> p1_name;
  // std::cout << "Enter Player1's color: " << std::endl;
  // std::cin >> p1_color;
  // std::cout << "Enter Player2's name: " << std::endl;
  // std::cin >> p2_name;
  // std::cout << "Enter Player2's color: " << std::endl;
  // std::cin >> p2_color;

  // board_->SetSize(board_size);
  // p1_ = new Player(p1_name, p1_color);
  // p2_ = new Player(p2_name, p2_color);

  // while (!GameFinish()) {
  //   std::cout << "Where will you put?: " << std::endl;
  //   //
  // }
}
void Judge::SignStone(int row, int col, char color) {
  /*Board의 돌을 넣기 위해 board클래스에 좌표와 값을 보냄*/
  board_->PutStone(row, col, color);
}
void Judge::ModStoneStatus(int row, int col, char color) {
 /* 돌을 놓은 뒤 상대편 돌들 뒤집기 위한 함수*/
  int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
  int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};

  std::vector<std::vector<char>> matrix = board_->Getmatrix();
  int size = matrix.size();
  char op_color;
  if(color == 'B') {      //놓으려는 플레이어의 돌 색깔이 black이면
    op_color = 'W';
  }
  else {
    op_color = 'B';
  }
  //직접 돌을 넣은 위치의 board 상태를 최신화.
  this->SignStone(row, col, color);


  for (int drt = 0; drt < 8; drt++) {
    int tprow = row;
    int tpcol = col; 
    int count = 0;
    int istrue = 0;

    for (int i = 0; i < size; i++ ) {
      tprow += dx[drt];
      tpcol += dy[drt];

      if (tprow < 0 || tprow >= size || tpcol < 0 || tpcol >= size) {
        break;
      }
      if (matrix[tprow][tpcol] == color) {
        istrue = 1;
        break; 
      }
      if (matrix[tprow][tpcol] == op_color) {     //뒤집어야 할 돌 대상
        count++;
      }
      if (matrix[tprow][tpcol] == '.' || matrix[tprow][tpcol] == '*') {
        break;
      }
    }

    if(istrue && count > 0) {       //뒤집어야 할 돌이 있다는 것을 의미
      tprow = row;
      tpcol = col;
      for (int i = 0; i < size; i++) {
        tprow += dx[drt];
        tpcol += dy[drt];

        if (tprow < 0 || tprow >= size || tpcol < 0 || tpcol >= size) {
          break;
        }
        if (matrix[tprow][tpcol] == color) {
          break;
        }
        this->SignStone(tprow, tpcol, color);
      }
    }
  }
}
void Judge::GetScore() {
  int b_cnt = 0;
  int w_cnt = 0;
  std::vector<std::vector<char>> matrix = board_->Getmatrix();
    
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++){
      if (matrix[i][j] == 'B') { b_cnt++; }
      else if (matrix[i][j] == 'W') { w_cnt++; }
    }
  }

  Player* tmp1 = p1_;
  Player* tmp2 = p2_;
  if (tmp1->GetColor() == 'B') {
    tmp1->SetScore(b_cnt);
    tmp2->SetScore(w_cnt);
  } else {
    tmp1->SetScore(w_cnt);
    tmp2->SetScore(b_cnt);
  }
}
std::string Judge::CheckWinner() {
  if (p1_->GetScore() > p2_->GetScore()) {
    return p1_->GetName();
  } else if (p1_->GetScore() < p2_->GetScore()) {
    return p2_->GetName();
  } else {
    return "Draw";
  }
}