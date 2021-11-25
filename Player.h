#ifndef _HOME_VSWNGJS_TERM_PLAYER_H_
#define _HOME_VSWNGJS_TERM_PLAYER_H_
#include <string>

class Player {
 public:
    Player(std::string name, char color);
    std::string getName();
    char getColor();
    int getScore();
    void setScore(int score);
 private:
    std::string name_;
    char color_;
    int score_;
};

#endif  // _HOME_VSWNGJS_TERM_PLAYER_H_"
