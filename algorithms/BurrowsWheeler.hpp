#ifndef BURROWSWHEELER_HPP
#define BURROWSWHEELER_HPP

std::pair<char*,int> bwt_encode(char *input, int length);
char* bwt_decode(std::pair<char*,int>, int length);

#endif
