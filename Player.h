#ifndef _MNT_C_USERS_USER_OODLAB_TERM_PROJECT_OTHELLO_PLAYER_H_
#define _MNT_C_USERS_USER_OODLAB_TERM_PROJECT_OTHELLO_PLAYER_H_
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

#endif // _MNT_C_USERS_USER_OODLAB_TERM_PROJECT_OTHELLO_PLAYER_H_
