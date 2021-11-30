#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Judge.h"

Judge* Judge::instance_ = nullptr;

Judge* Judge::GetInstance() {
  if (instance_ == nullptr) { instance_ = new Judge(); }
  return instance_;
}

Judge::Judge() {
  this->row_ = 0;
  this->col_ = 0;
  this->turn_ = 0;
  Player* p1 = new Player();
  Player* p2 = new Player();
  this->p1_ = p1;
  this->p2_ = p2;
  this->candidate_;
  this->board_ = Board::GetInstance();
}

void Judge::StartGame() {
  std::cout << "Welcome to Othello\n" << std::endl;
  this->CreateBoard();
  this->SetPlayers();
  std::vector<std::vector<char>> matrix = board_->Getmatrix();
  int size = matrix.size();
  char turn_flag = 'B';

  while (true) {
    std::cout << std::endl;

    if (!(this->IsGameContinue(turn_flag))) {
      break;
    }
    if (this->candidate_.size() == 0) {  // 후보군이 없으므로 턴이 넘어가야함.
      board_->PrintBoard();
      std::cout << "\nOops! Player " << this->GetPlayerName(turn_flag)
      << " has no space to put stone." << std::endl;

      turn_flag = this->ChangeTurn(turn_flag);
      std::cout << "It's Player " << this->GetPlayerName(turn_flag)
      << "'s turn again." << std::endl;
      this->SetScore();
      continue;
    }

    board_->PrintBoard();
    this->SetScore();
    std::cout << "\n" << p1_->GetName() << "(" << p1_->GetColor() << ") "
    << p1_->GetScore() << " : ";
    std::cout << p2_->GetScore() << " " << p2_->GetName() << "("
    << p2_->GetColor() << ")" << std::endl;
    std::cout << "Player " << this->GetPlayerName(turn_flag) << "'s Turn"
    << std::endl;

    while (!(this->PlayerInput())) {
      std::cout << "It's not a right choice." << std::endl;
    }

    this->ModStoneStatus(this->row_, this->col_, turn_flag);
    board_->RestoreBoard();
    turn_flag = this->ChangeTurn(turn_flag);
  }

  std::string result = this->CheckWinner();
  std::cout << "\n" << p1_->GetName() << "(" << p1_->GetColor() << ") "
  << p1_->GetScore() << " : ";
  std::cout << p2_->GetScore() << " " << p2_->GetName() << "("
  << p2_->GetColor() << ")" << std::endl;
  if (result == "Draw") {
    std::cout << result << "! There is no winner!" << std::endl;
  } else {
    std::cout << "Congratulations! Player " << result << " wins!" << std::endl;
  }
}

bool Judge::IsGameContinue(char color) {
  // 한 차례에 양쪽 모두 서로 차례를 넘겨야 하는 경우
  // checkCnt = 0이 두번 연속일 때
  // 위의 경우가 아니면 false
  std::vector <std::vector <char>> matrix = board_->Getmatrix();
  int size = matrix.size();

  if (board_->IsFullBoard()) { return false; }
  // 돌을 놓을 수 있는 공간이 없을 경우
  if (board_->HasOnlyOneType()) { return false; }
  // 한가지 색의 돌만 존재하는 경우

  (this->candidate_).clear();
  std::vector<std::pair<int, int>>().swap(this->candidate_);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (CheckValid(i, j, color)) {
        (this->candidate_).push_back(std::make_pair(i, j));
      }
    }
  }

  std::cout << "Possible Coordinates (*)" << std::endl;
  std::cout << "| ";
  for (int i = 0; i < (this->candidate_).size(); i++) {
    std::cout << this->candidate_[i].first << "  "
    << this->candidate_[i].second << " | ";
  }
  std::cout << "\n" << std::endl;

  if ((this->candidate_).size() == 0) {
    this->turn_++;
  } else { this->turn_ = 0; }
  if (this->turn_ == 2) { return false; }
  // 놓을 수 있는 후보군이 2번 연속 없는 경우
  return true;
}

bool Judge::CheckValid(int row, int col, char color) {
  /* 현재 player가 놓을 수 있는 위치를 계산 */
  int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};  // 8 방향 점검
  int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
  // 아래, 위, 왼, 오, 왼아, 왼위, 오아, 오위
  std::vector<std::vector<char>> matrix = board_->Getmatrix();
  int size = matrix.size();
  char op_color = '.';

  if (matrix[row][col] != '.') { return false; }
  if (color == 'B') {
    op_color = 'W';
  } else { op_color = 'B'; }

  for (int i = 0; i < 8; i++) {
    int tmp_row = row;
    int tmp_col = col;
    int cnt = 0;
    bool is_true = false;

    for (int j = 0; j < size; j++) {
      tmp_row += dx[i];
      tmp_col += dy[i];

      if ((tmp_row < 0) || (tmp_row >= size) || (tmp_col < 0)
      || (tmp_col >= size)) {
        break;
      }
      if (matrix[tmp_row][tmp_col] == color) {
        is_true = true;
        break;
      }
      if (matrix[tmp_row][tmp_col] == op_color) { cnt++; }
      if ((matrix[tmp_row][tmp_col] == '.')
      || (matrix[tmp_row][tmp_col] == '*')) {
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

void Judge::SetPlayers() {
  std::string tmp = "";
  char p1_color;

  std::cout << "Enter Player1's name : ";
  std::cin >> tmp;
  p1_->SetName(tmp);
  tmp = "";
  while (true) {
    std::cout << "Player1 can choose color (B or W) : ";
    std::cin >> tmp;
    if ((tmp.front() == 'B') || (tmp.front() == 'W')) {
      break;
    } else {
      std::cout << "You have to choose either B or W." << std::endl;
    }
  }
  p1_color = tmp.front();
  p1_->SetColor(p1_color);

  std::cout<< "Enter Player2's name : ";
  std::cin >> tmp;
  p2_->SetName(tmp);
  if (p1_color == 'B') {
    p2_->SetColor('W');
    std::cout << "Player2's color is W." << std::endl;
  } else {
    p2_->SetColor('B');
    std::cout << "Player2's color is B." << std::endl;
  }
}

void Judge::SetScore() {
  int b_cnt = 0;
  int w_cnt = 0;
  std::vector<std::vector<char>> matrix = board_->Getmatrix();

  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 'B') {
        b_cnt++; } else if (matrix[i][j] == 'W') { w_cnt++; }
    }
  }

  Player* p1 = p1_;
  Player* p2 = p2_;

  if (p1->GetColor() == 'B') {
    p1->SetScore(b_cnt);
    p2->SetScore(w_cnt);
  } else {
    p1->SetScore(w_cnt);
    p2->SetScore(b_cnt);
  }
}

void Judge::CreateBoard() {
  std::string input = "";
  int size = 0;

  std::cout << "Enter the size of board : ";
  std::cin >> input;
  size = atoi(input.c_str());
  while ((size % 2 == 1) || (size < 4)) {
    std::cout << "Enter an even number of 6 or more : ";
    std::cin >> input;
    size = atoi(input.c_str());
  }
  (this->board_)->SetSize(size);
}

bool Judge::PlayerInput() {
  std::string input_row = "";
  std::string input_col = "";
  std::cout << "Enter row and column ex) 2 4 : ";
  std::cin >> input_row >> input_col;

  this->row_ = atoi(input_row.c_str());
  this->col_ = atoi(input_col.c_str());
  std::vector<std::vector<char>> matrix = board_->Getmatrix();
  int size = matrix.size();

  if ((this->row_ >= 0) && (this->row_ < size) && (this->col_ >= 0)
  && (this->col_ < size) && (matrix[this->row_][this->col_] == '*')) {
    return true;
  }
  return false;
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

  if (color == 'B') {  // 놓으려는 플레이어의 돌 색깔이 black이면
    op_color = 'W';
  } else {
    op_color = 'B';
  }
  // 직접 돌을 넣은 위치의 board 상태를 최신화.
  this->SignStone(row, col, color);

  for (int i = 0; i < 8; i++) {
    int tmp_row = row;
    int tmp_col = col;
    int cnt = 0;
    bool is_true = false;

    for (int j = 0; j < size; j++) {
      tmp_row += dx[i];
      tmp_col += dy[i];

      if ((tmp_row < 0) || (tmp_row >= size) || (tmp_col < 0)
      || (tmp_col >= size)) { break; }
      if (matrix[tmp_row][tmp_col] == color) {
        is_true = true;
        break;
      }
      if (matrix[tmp_row][tmp_col] == op_color) {  // 뒤집어야 할 돌 대상
        cnt++;
      }
      if (matrix[tmp_row][tmp_col] == '.' || matrix[tmp_row][tmp_col] == '*') {
        break;
      }
    }

    if (is_true && (cnt > 0)) {  // 뒤집어야 할 돌이 있다는 것을 의미
      tmp_row = row;
      tmp_col = col;

      for (int j = 0; j < size; j++) {
        tmp_row += dx[i];
        tmp_col += dy[i];

        if ((tmp_row < 0) || (tmp_row >= size) || (tmp_col < 0)
        || (tmp_col >= size)) { break; }
        if (matrix[tmp_row][tmp_col] == color) {
          break;
        }
        this->SignStone(tmp_row, tmp_col, color);
      }
    }
  }
}

char Judge::ChangeTurn(char color) {
  if (color == 'B') {
    return 'W';
  } else { return 'B'; }
}

std::string Judge::GetPlayerName(char color) {
  if (p1_->GetColor() == color) {
    return p1_->GetName();
  } else {
    return p2_->GetName();
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
