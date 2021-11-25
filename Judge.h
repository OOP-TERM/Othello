#ifndef _HOME_VSWNGJS_TERM_JUDGE_H_
#define _HOME_VSWNGJS_TERM_JUDGE_H_
#include <string>
#include "Player.h"
#include "Board.h"

/*게임 진행 당 필요한 심판은 1명이므로 sigleton pattern 적용*/
class Judge {
 public:
   static Judge* GetInstance();
   // bool gameFinish();
   // bool checkValid(int row, int col);
   // bool checkCnt();
   // void playerInput();
   // void signStone(int row, int col);
   // void modStoneStatus();
   void checkScore();
   // std::string checkWinner();

   void setBoard(Board* board);
   void setPlayers(Player* p1, Player* p2);

 private:
   Judge();
   static Judge* instance_;
   Board* board_;
   Player* p1_;
   Player* p2_;
};
#endif  // _HOME_VSWNGJS_TERM_JUDGE_H_"
