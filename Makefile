# TODO: Set your googletest directory path
GTEST_DIR=/mnt/c/Users/user/OODLab/term_project_othello/googletest/googletest

CPPFLAGS += -isystem $(GTEST_DIR)/include

CXXFLAGS += -pthread

GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# TODO: Set your executable target
all : main

# TODO: Change 'main' and 'main_test' to your executable and test respectively
clean :
	rm -f gtest.a gtest_main.a *.o main test

gtest-all.o : $(GTEST_SRCS_)
	g++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	g++ $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# TODO: Change 'calc.h' and 'calc.cc' to your source files
Board.o : Board.h Board.cpp
	g++ --std=c++17 -c Board.cpp -o $@

Judge.o : Judge.h Judge.cpp
	g++ --std=c++17 -c Judge.cpp -o $@

Player.o : Player.h Player.cpp
	g++ --std=c++17 -c Player.cpp -o $@

# TODO: Change 'main.cc' and 'calc.o' to your main source file and calc target
# respectively
main : main.cpp Board.o Judge.o Player.o $(GTEST_HEADERS)
	g++ --std=c++17 main.cpp Board.o Judge.o Player.o -o $@

# TODO: Change 'calc_test.cc' to your test file
othello_test.o : othello_test.cpp $(GTEST_HEADERS)
	g++ $(CPPFLAGS) $(CXXFLAGS) --std=c++17 -c othello_test.cpp -o $@

# TODO: Change 'calc_test.o' and 'calc.o' to your object targets
test : othello_test.o main.cpp Board.o Judge.o Player.o gtest_main.a
	g++ $(CPPFLAGS) $(CXXFLAGS) --std=c++17 $^ -o $@

.PHONY: all clean
