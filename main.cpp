#include <iostream>
#include "Board.h"
#include "Judge.h"
#include "Player.h"

int main(int argc, char** argv) {
    Judge* judge = Judge::GetInstance();
    judge->StartGame();
}

// TODO
// 필드, 변수, 함수 네임 점검
// cpplint, gtest
// 입출력 예외 처리
