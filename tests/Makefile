DIR = ../oneThread
OPTS = -std=c++0x -I$(DIR)


all: test_bwt test_mtf

test_bwt: test_bwt.cpp $(DIR)/BurrowsWheeler.cpp $(DIR)/BurrowsWheeler.hpp
	g++ $(OPTS) -o test_bwt test_bwt.cpp $(DIR)/BurrowsWheeler.cpp

test_mtf: test_mtf.cpp $(DIR)/MoveToFront.cpp $(DIR)/MoveToFront.hpp
	g++ $(OPTS) -o test_mtf test_mtf.cpp $(DIR)/MoveToFront.cpp

clean:
	rm -r test_bwt test_mtf
