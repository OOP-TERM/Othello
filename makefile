 # TODO: Set your googletest directory path
GTEST_DIR=/home/vswngjs/googletest/googletest

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

# TODO: Change 'Student.h' and 'Student.cpp' to your source files
Board.o : Board.h Board.cpp
	g++ --std=c++17 -c Board.cpp -o $@

Player.o : Player.h Player.cpp 
	g++ --std=c++17 -c Player.cpp -o $@

Judge.o : Judge.h Judge.cpp Board.o Player.o
	g++ --std=c++17 -c Judge.cpp -o $@

# TreeUtil.o : Node.h Node.cpp IntNode.h IntNode.cpp StringNode.h StringNode.cpp TreeUtil.h TreeUtil.cpp 
# 	g++ --std=c++17 -c TreeUtil.cpp -o $@

# TODO: Change 'main.cpp' and 'Student.o' to your main source file and Student target
# respectively
main : main.cpp Board.o Player.o Judge.o  $(GTEST_HEADERS)
	g++ --std=c++17 main.cpp Board.o Player.o Judge.o -o $@

# TODO: Change 'Student_test.cpp' to your StringNode

# TreeUtil_test.o : TreeUtil_test.cpp $(GTEST_HEADERS)
# 	g++ $(CPPFLAGS) $(CXXFLAGS) --std=c++17 -c TreeUtil_test.cpp -o $@

# TODO: Change 'Student_test.o' and 'Student.o' to your object targets
# test : TreeUtil_test.o Node.o IntNode.o StringNode.o TreeUtil.o gtest_main.a
# 	g++ $(CPPFLAGS) $(CXXFLAGS) --std=c++17 $^ -o $@

.PHONY: all clean 
