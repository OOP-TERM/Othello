#include <iostream>
#include "Board.h"
#include "Judge.h"
#include "Player.h"

int main(int argc, char** argv) {
  std::string p1_name, p2_name;
  char p1_color, p2_color;
  int size, row, col;

  Board* board = Board::GetInstance();
  Judge* judge = Judge::GetInstance();

  std::cout << "Enter the size of board: ";
  std::cin >> size;
  board->SetSize(size);
  judge->SetBoard(board);

  std::cout << "Enter Player1's name: ";
  std::cin >> p1_name;
  std::cout << "Enter Player1's color: ";
  std::cin >> p1_color;
  Player* p1 = new Player(p1_name, p1_color);

  std::cout << "Enter Player2's name: ";
  std::cin >> p2_name;
  std::cout << "Enter Player2's color: ";
  std::cin >> p2_color;
  Player* p2 = new Player(p2_name, p2_color);

  judge->SetPlayers(p1, p2);
  // board->PrintBoard();
  // judge->ModStoneStatus(2, 4, 'B');
  std::cout << std::endl;

  board->PrintBoard();
  judge->GetScore();
  std::cout << p1->GetScore() << "   :   " << p2->GetScore() << std::endl;

  // 'B'인 플레이어 찾기
  // 좌표 입력 받기

  // while (!judge->GameFinish()) {
  //   std::cout << "Where will you put?: " << std::endl;
  //   if (p1->GetColor() )
  //   if (p2->GetColor() )
  //   judge->CheckCnt();
  //   judge->CheckValid();    

  // }
  std::cout << judge->CheckWinner() << std::endl;

  std::cout << judge->IsGameContinue('B') << std::endl;
  board->PrintBoard();
}
