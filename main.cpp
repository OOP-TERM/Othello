#include <iostream>
#include <string>
#include <vector>
#include "Board.h"
#include "Judge.h"
#include "Player.h"

int main(int argc, char** argv) {
    Board* board = Board::GetInstance();

    board->setSize(8);
    board->printBoard();

    Judge* judge = Judge::GetInstance();
    judge->setBoard(board);
    
    Player* guest = new Player("juheon", 'B');
    Player* guest1 = new Player("shinhyoung", 'W');

    judge->setPlayers(guest, guest1);

    judge->checkScore();

    std::cout << guest -> getScore() << "   :   " << guest1 -> getScore() << std::endl;


}