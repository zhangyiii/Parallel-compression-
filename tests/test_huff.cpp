#include<iostream>
#include<cstdio>
#include<cstring>
#include "huffman.hpp"
using namespace std;
int main() {

    int size;
    scanf("%d\n", &size);
    char *input = new char[size];
    scanf("%s", input);
    vector<char> result = huff_encode(input, size, "result.txt");
    for(int i=0; i<result.size(); i++)printf("%c", result[i]);
    printf("\n");
    
    result = huff_decode("result.txt");
    for(int i=0; i<result.size(); i++)printf("%c", result[i]);
    printf("\n");
    return 0;
}
