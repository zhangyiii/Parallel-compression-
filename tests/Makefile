DIR = ../algorithms
OPTS = -fopenmp -std=c++0x -I$(DIR)
COMMON_DEPENDECIES = $(DIR)/constants.hpp $(DIR)/commonfunc.hpp $(DIR)/commonfunc.cpp

all: test_bwt test_mtf test_mtf_0 test_mtf_2 test_huff gen

gen: gen.cpp $(DIR)/BurrowsWheeler.cpp $(DIR)/BurrowsWheeler.hpp $(COMMON_DEPENDENCIES) 
	g++ $(OPTS) -o gen gen.cpp $(DIR)/BurrowsWheeler.cpp $(DIR)/commonfunc.cpp -fopenmp

test_bwt: test_bwt.cpp $(DIR)/BurrowsWheeler.cpp $(DIR)/BurrowsWheeler.hpp $(COMMON_DEPENDECIES)
	g++ $(OPTS) -o test_bwt test_bwt.cpp $(DIR)/BurrowsWheeler.cpp $(DIR)/commonfunc.cpp -fopenmp

test_mtf_0: test_mtf_0.cpp $(DIR)/MoveToFront_0.cpp $(DIR)/MoveToFront.hpp $(DIR)/constants.hpp
	g++ $(OPTS) -o test_mtf_0 test_mtf_0.cpp $(DIR)/MoveToFront_0.cpp

test_mtf: test_mtf.cpp $(DIR)/MoveToFront.cpp $(DIR)/MoveToFront.hpp $(DIR)/constants.hpp
	g++ $(OPTS) -o test_mtf test_mtf.cpp $(DIR)/MoveToFront.cpp
	
test_mtf_2: test_mtf_2.cpp $(DIR)/MoveToFront_0.cpp $(DIR)/MoveToFront.hpp $(DIR)/constants.hpp
	g++ $(OPTS) -o test_mtf_2 test_mtf_2.cpp $(DIR)/MoveToFront_0.cpp

test_huff: test_huff.cpp $(DIR)/huffman.cpp $(DIR)/huffman.hpp
	g++ $(OPTS) -o test_huff test_huff.cpp $(DIR)/huffman.cpp -lboost_serialization
clean:
	rm -r test_bwt test_mtf test_mtf_0 test_mtf_2 test_huff gen
