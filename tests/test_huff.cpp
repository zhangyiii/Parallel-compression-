#include<iostream>
#include<cstdio>
#include "huffman.hpp"
using namespace std;
int main() {

    int size;
    scanf("%d", &size);
    char *input = new char[size];
    vector<int> result = huff_encode(input,size);
    for(int i=0; i<result.size(); i++)printf("%d", result[i]);
    printf("\n");
    return 0;
}
