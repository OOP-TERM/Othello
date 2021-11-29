#ifndef _HOME_VSWNGJS_TERM_PLAYER_H_
#define _HOME_VSWNGJS_TERM_PLAYER_H_
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
    void GetInfo();
 private:
    std::string name_;
    char color_;
    int score_;
};
#endif  // _HOME_VSWNGJS_TERM_PLAYER_H_"
