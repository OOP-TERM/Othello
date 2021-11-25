#include <string>
#include "Player.h"

#include <iostream>

using std::endl;
using std::cout;


/*오셀로 시작할 때 보드에 자신의 돌을 두 개씩 엇갈린 상태로 놓으므로
 기본 점수는 2부터 시작하게 된다.*/
Player::Player(std::string name, char color) : name_(name),
color_(color), score_(2){}                  

std::string Player::getName() {
    return this->name_;
}

char Player::getColor() {
    return this->color_;
}
int Player::getScore() {
    return this->score_;
}

void Player::setScore(int score) {
    this->score_ = score;
}