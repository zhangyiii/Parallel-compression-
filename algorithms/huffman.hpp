#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP
#include<vector>
#include<cstring>
std::vector<char> huff_encode(char *input, int size, std::string fileName);
std::vector<char> huff_decode(std::string fileName);
#endif
