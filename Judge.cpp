#include <iostream>
#include <string>
#include <vector>
#include <utility>
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


bool Judge::IsGameContinue(char color) {
  // 한 차례에 양쪽 모두 서로 차례를 넘겨야 하는 경우
  // checkCnt = 0이 두번 연속일 때
  // 위의 경우가 아니면 false
  std::vector <std::vector <char>> matrix = board_->Getmatrix();
  int size = matrix.size();

  if (board_->IsFull()) {   //돌을 놓을 수 있는 공간이 없을 경우
    return false;
  }
  if (board_->IsOnlyOne()) {    // 한가지 색의 돌만 존재하는 경우
    return false;
  }
  this->candidate_.clear();
  std::vector<std::pair<int, int>>().swap(this->candidate_);

  for (int row = 0; row < size; row++) {
    for (int col = 0; col < size; col++){
      if (CheckValid(row, col, color)) {
        this->candidate_.push_back(std::make_pair(row, col));
      }
    }
  }
  std::cout << std::endl;

  std::cout << "놓을 수 있는 경우의 수" << std::endl;
  for (int i = 0; i < this->candidate_.size(); i++) {
    std::cout << this->candidate_[i].first << "  " << this->candidate_[i].second << "\t";
  }
  std::cout << std::endl;

  if (this->candidate_.size() == 0) {         //놓을 수 있는 후보군이 없는 경우
    this->turn_++;
  }
  else{
    this->turn_ = 0;
  }
  if (this->turn_ == 2) {                     //놓을 수 있는 후보군이 2번 연속 없는 경우
    return false;
  }
  return true;
}


bool Judge::CheckValid(int row, int col, char color) {
    // 현재 player가 놓을 수 있는 위치를 계산
  int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};  // 8 방향 점검
  int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};  // 아래, 위, 왼, 오, 왼아, 왼위, 오아, 오위
  
  std::vector<std::vector<char>> matrix = board_->Getmatrix();
  int size = matrix.size();
  int r = 0;
  char op_color = '.';

  if (matrix[row][col] != '.') { return false; }
  
  if (color == 'B') { op_color = 'W'; }
  else { op_color = 'B'; }

  for (int i = 0; i < 8; i++) {
    int tmp_row = row;
    int tmp_col = col;
    int cnt = 0;
    int is_true = 0;

    for (int j = 0; j < size; j++) {
      tmp_row += dx[i];
      tmp_col += dy[i];

      if ((tmp_row < 0) || (tmp_row >= size) || (tmp_col < 0) || (tmp_col >= size)) {
        break;
      }
      if (matrix[tmp_row][tmp_col] == color) {
        is_true = 1;
        break;
      }
      if (matrix[tmp_row][tmp_col] == op_color) { cnt++; }
      if ((matrix[tmp_row][tmp_col] == '.') || (matrix[tmp_row][tmp_col] == '*')) {
        break;
      }
    }
    if (is_true && (cnt != 0)) {
      this->SignStone(row, col, '*');
      return true;
    }
  }
  return false;
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

char Judge::ChangeTurn(char color) {
  if (color == 'B') { return 'W'; }
  else { return 'B'; }
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