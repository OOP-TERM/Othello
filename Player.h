#ifndef PLAYER_H_
#define PLAYER_H_
#include <string>

class Player {
 public:
    Player();
    void SetName(std::string name);
    void SetColor(char color);
    void SetScore(int score);
    std::string GetName();
    char GetColor();
    int GetScore();
 private:
    std::string name_;
    char color_;
    int score_;
};


#endif  // PLAYER_H_"
