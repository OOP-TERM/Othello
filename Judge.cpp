#include <iostream>
#include <string>
#include "Player.h"
#include "Board.h"
#include "Judge.h"

using std::endl;
using std::cout;

Judge* Judge::instance_ = NULL;
Judge* Judge::GetInstance() {
    if (instance_ == NULL) {
        instance_ = new Judge();
    }
    return instance_;
}

// bool Judge::gameFinish() {}

// bool Judge::checkValid(int row, int col) {}

// bool Judge::checkCnt() {}

// bool Judge::playerInput() {}

// void Judge::signStone(int row, int col) {}

// void Judge::modStoneStatus() {}

void Judge::checkScore() {
    int B_score = 0;
    int W_score = 0;
    std::vector<std::vector<char>> matrix = (this->board_)->getmatrix();
    
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[0].size(); j++){
            if (matrix[i][j] == 'B') {
                B_score++;
            }
            else if (matrix[i][j] == 'W') {
                W_score++;
            } 
        }
    }
    Player* tmp1 = this -> p1_;
    Player* tmp2 = this -> p2_;
    if(tmp1->getColor() == 'B') {
        tmp1->setScore(B_score);
        tmp2->setScore(W_score);
    } else {
        tmp1->setScore(W_score);
        tmp2->setScore(B_score);
    }
}

// std::string Judge::checkWinner() {}


void Judge::setBoard(Board* board) {           //보드와 심판 연결
    this->board_ = board;
}
void Judge::setPlayers(Player* p1, Player* p2) {       //플레이어들과 심판 연결
    this->p1_ = p1;
    this->p2_ = p2;
}

Judge::Judge() {}