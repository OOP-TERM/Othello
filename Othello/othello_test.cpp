#include "gtest/gtest.h"
#include "Judge.h"
#include "Board.h"
#include "Player.h"

Judge* judge_test = Judge::GetInstance();
Board* board_test = judge_test -> GetBoard();

judge_test -> GetBoard() -> SetSize(8);

//기본 판 미리 깔아놓음
std::vector<std::vector<char> > matrix_now = judge_test -> GetBoard() -> Getmatrix();

//시작 테스트 1(이름 선택) e
TEST(OthelloTest, StartNameTest) {
    judge_test -> GetP1() -> SetName("p1name");
    judge_test -> GetP2() -> SetName("p2name");
    std::string end = "p1namep2name";
    std::string to = judge_test -> GetP1() -> GetName();
    to += judge_test -> GetP2() -> GetName();
    EXPECT_EQ(to, end);
}

//시작 테스트 2(색 선택) e
TEST(OthelloTest, StartColorTest) {
    judge_test -> GetP1() -> SetColor('B');
    judge_test -> GetP2() -> SetColor('B');
    std::string end = "BW";
    std::string to = "";
    to += judge_test -> GetP1() -> GetColor();
    to += judge_test -> GetP2() -> GetColor();
    EXPECT_EQ(to, end);
}

//시작 후 보드 기본 상태 e
TEST(OthelloTest, StartSetBoardTest) {
    bool one = true;
    bool two = true;
    //실제 배열을 받음
    std::vector<std::vector<char> > matrix_now = judge_test -> GetBoard() -> Getmatrix();

    for(int i = 0; i < matrix_now.size(); i++){
        for(int j = 0; j < matrix_now[i].size(); j++){
            if(i == 3 || i == 4 || j == 3 || j == 4){
                if((i == 3 && j == 3) || (i == 4 && j == 4)){
                    if(matrix_now[i][j] != 'B'){
                        two = false;
                        break;
                    }
                }
                if((i == 4 && j == 3) || (i == 3 && j == 4)){
                    if(matrix_now[i][j] != 'W'){
                        two = false;
                        break;
                    }
                }
            }else{
                //다른곳에서 돌이 나왔을경우
                if(matrix_now[i][j] == 'B' || matrix_now[i][j] == 'W'){
                    two = false;
                    break;
                }
            }
        }
    }
    EXPECT_EQ(one, two);
}

//돌을 놓음
board_test -> PutStone();
judge_test -> ModStoneStatus(3, 5, 'B');
judge_test -> ChangeTurn('B');
board_test -> RestoreBoard();
//putStone 동작 여부 (뒤집히지 않은 상태임) ing
TEST(OthelloTest, StartPutStoneTest) {
    bool to = true;
    bool from = true;
    //예상 배열 제작
    std::vector<std::vector<char> > matrix_now_test = matrix_now;
    matrix_now_test[3][4] = 'B';
    matrix_now_test[3][5] = 'B';

    matrix_now_test[2][3] = '*';
    matrix_now_test[2][5] = '*';
    matrix_now_test[4][5] = '*';

    matrix_now_test[2][4] = '.';
    matrix_now_test[4][2] = '.';
    matrix_now_test[5][3] = '.';
    std::vector<std::vector<char> > matrix_prev = board_test -> Getmatrix();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(matrix_now_test[i][j] != matrix_prev[i][j]){
                from = false;
                break;
            }
        }
    }
    EXPECT_EQ(to, from);
}

//스코어 정상 작동 여부 e
judge_test -> SetScore();
int p1_test_score = 1;
int p2_test_score = 4;
int p1_real_score = judge_test -> GetP1() -> GetScore();
int p2_real_score = judge_test -> GetP2() -> GetScore();
TEST(OthelloTest, ScoreTest1) {
    EXPECT_EQ(p1_test_score, p1_real_score);
}

TEST(OthelloTest, ScoreTest2) {
    EXPECT_EQ(p2_test_score, p2_real_score);
}

//CheckValid 정상 실행 여부
TEST(OthelloTest, CheckValidTest) {
    bool to = false;
    bool from = CheckValid(0, 0, 'B');
    EXPECT_EQ(to, from);
}

//candidate 정상 실행 여부 e
std::vector<std::vector<char> > matrix_next = judge_test -> GetBoard() -> Getmatrix();
TEST(OthelloTest, CandidateTest) {
    bool to = true;
    bool from = true;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if((i == 2 && j == 3) || (i == 2 && j == 5) || (i == 4 && j == 5)){
                if(matrix_next[i][j] != '*'){
                    from = false;
                    break;
                }
            }else{
                if(matrix_next[i][j] == '*'){
                    from = false;
                    break;
                }
            }
        }
    }

    EXPECT_EQ(to, from);
}

//IsFullBoard 정상 여부 e
TEST(OthelloTest, IsFullBoardTest) {
    bool to = false;
    bool from = board_test -> IsFullBoard();
    EXPECT_EQ(to, from);
}

//IsGameContinue 정상 여부 e
TEST(OthelloTest, IsGameContinueTest) {
    bool to = true;
    bool from = judge_test -> IsGameContinue('B');
    EXPECT_EQ(to, from);
}

//HasOnlyOneType 정상 여부
TEST(OthelloTest, HasOnlyOneTypeTest) {
    bool to = false;
    bool from = board_test -> HasOnlyOneType();
    EXPECT_EQ(to, from);
}

//정상 게임 종료 여부
TEST(OthelloTest, EndingTest) {
    std::string to = judge_test -> GetP1() -> GetName();
    std::string from = judge_test -> CheckWinner();
    EXPECT_EQ(to, from);
}
// TEST(Testt, TDFS1) {
//     IntNode in1(nullptr, nullptr, 3);
//     IntNode in2(nullptr, nullptr, 7);
//     StringNode sn1(nullptr, nullptr, "hello");
//     StringNode sn2(nullptr, nullptr, "world");
//     StringNode sn3(&in1, &in2, "here");
//     IntNode in3(&sn1, &sn2, 6);
//     IntNode root(&sn3, &in3, 10);
//     std::vector<const Node*> dfs_test = util -> DepthFirstSearch(&root);
//     std::string to = "10here376helloworld";
//     std::string from = "";
//     for (const Node* n : dfs_test) {
//          from += n -> value();
//     }
//     EXPECT_EQ(to, from);
// }