#ifndef BURROWSWHEELER_HPP
#define BURROWSWHEELER_HPP
namespace BurrowsWheeler {

std::pair<char*,int> encode(char *input, int length);

char* decode(std::pair<char*,int>, int length);

}
#endif
