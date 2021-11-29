#ifndef _HOME_VSWNGJS_TERM_JUDGE_H_
#define _HOME_VSWNGJS_TERM_JUDGE_H_
#include <string>
#include "Player.h"
#include "Board.h"
/* 게임 진행 당 필요한 심판은 1명이므로 sigleton pattern 적용 */
class Judge {
 public:
   static Judge* GetInstance();
   void SetBoard(Board* board);
   void SetPlayers(Player* p1, Player* p2);
   void GetScore();
   bool GameFinish();
   bool CheckValid(int row, int col);
   bool CheckCnt();
   void PlayerInput();
   void SignStone(int row, int col, char color);
   void ModStoneStatus(int row, int col, char color);
   std::string CheckWinner();

 private:
   Judge();
   static Judge* instance_;
   Board* board_;
   Player* p1_;
   Player* p2_;
};
#endif  // _HOME_VSWNGJS_TERM_JUDGE_H_"
