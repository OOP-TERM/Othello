#include "Player.h"

/*오셀로 시작할 때 보드에 자신의 돌을 두 개씩 엇갈린 상태로 놓으므로
 기본 점수는 2부터 시작하게 된다.*/
Player::Player(std::string name, char color) : name_(name),
color_(color), score_(2){}

void Player::SetScore(int score) { score_ = score; }
std::string Player::GetName() { return name_; }
char Player::GetColor() { return color_; }
int Player::GetScore() { return score_; }