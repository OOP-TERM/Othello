#include "gtest/gtest.h"
#include "Judge.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

Judge* judge = Judge::GetInstance();
Board* board = Board::GetInstance();

//시작 테스트 1(이름 선택) e
TEST(OthelloTest, StartNameTest) {
    judge -> p1_ -> SetName("p1name");
    judge -> p2_ -> SetName("p2name");
    std::string end = "p1namep2name";
    std::string to = judge -> p1_ -> GetName();
    to += judge -> p2_ -> GetName();
    EXPECT_EQ(to, end);
}

//시작 테스트 2(색 선택) e
TEST(OthelloTest, StartColorTest) {
    judge -> p1_ -> SetColor("B");
    judge -> p2_ -> SetColor("B");
    std::string end = "BW";
    std::string to = judge -> p1_ -> GetColor();
    to += judge -> p2_ -> GetColor();
    EXPECT_EQ(to, end);
}

//시작 후 보드 기본 상태 e
TEST(OthelloTest, StartSetBoardTest) {
    bool one = true;
    bool two = true;
    board -> SetSize(8);
    //예상 배열에는과 실제 배열을 받음
    std::vector<std::vector<char>> matrix_now = board -> Getmatrix();

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
                if(matrix_now[i][j] != '.'){
                    two = false;
                    break;
                }
            }
        }
    }
    EXPECT_EQ(one, two);
}

//첫 돌 올렸을때 정상 동작 여부
TEST(OthelloTest, StartSetStoneTest) {
    
    EXPECT_EQ(to, from);
}

//스코어 정상 작동 여부
TEST(OthelloTest, ScoreTest) {
    
    EXPECT_EQ(to, from);
}

//게임 정상 진행 테스트1
TEST(OthelloTest, FlowingTest1) {
    
    EXPECT_EQ(to, from);
}

//게임 정상 진행 테스트2
TEST(OthelloTest, FlowingTest2) {
    
    EXPECT_EQ(to, from);
}

//게임 정상 진행 테스트3
TEST(OthelloTest, FlowingTest3) {
    
    EXPECT_EQ(to, from);
}

//돌 올려야 할곳 정상 출력 여부
TEST(OthelloTest, PrintRecommandTest) {
    
    EXPECT_EQ(to, from);
}

//돌 올려야 할곳에 안올릴경우1(내부)
TEST(OthelloTest, InsideTest1) {
    
    EXPECT_EQ(to, from);
}

//돌 올려야 할곳에 안올릴경우2(내부)
TEST(OthelloTest, InsideTest2) {
    
    EXPECT_EQ(to, from);
}


//돌 올려야 할곳에 안올릴경우(외부)
TEST(OthelloTest, OutSideTest) {
    
    EXPECT_EQ(to, from);
}

//정상 게임 종료 여부
TEST(OthelloTest, EndingTest) {
    
    EXPECT_EQ(to, from);
}


TEST(OthelloTest, Test) {
    
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