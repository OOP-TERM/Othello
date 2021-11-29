#include <iostream>
#include "Board.h"
#include "Judge.h"
#include "Player.h"

int main(int argc, char** argv) {
    Judge* judge = Judge::GetInstance();
    judge->StartGame();
}
