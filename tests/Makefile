DIR = ../algorithms
OPTS = -std=c++0x -I$(DIR)


all: test_bwt test_mtf test_huff

test_bwt: test_bwt.cpp $(DIR)/BurrowsWheeler.cpp $(DIR)/BurrowsWheeler.hpp
	g++ $(OPTS) -o test_bwt test_bwt.cpp $(DIR)/BurrowsWheeler.cpp

test_mtf: test_mtf.cpp $(DIR)/MoveToFront.cpp $(DIR)/MoveToFront.hpp
	g++ $(OPTS) -o test_mtf test_mtf.cpp $(DIR)/MoveToFront.cpp

test_huff: test_huff.cpp $(DIR)/huffman.cpp $(DIR)/huffman.hpp
	g++ $(OPTS) -o test_huff test_huff.cpp $(DIR)/huffman.cpp -lboost_serialization
clean:
	rm -r test_bwt test_mtf test_huff
