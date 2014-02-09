#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
#include "BurrowsWheeler.hpp"
#include<cstdlib>
using namespace std;

void test(int trials) { 
    srand(time(NULL));
    for(int i=0; i<trials; i++) {
        int N = 100+rand()%200;
        char *input = new char[N+1];
        input[N]=0;
        for(int i=0; i<N; i++)input[i] = 'A'+rand()%26;
        pair<char*,int> p = BurrowsWheeler::encode(input,N);
        char *output =  BurrowsWheeler::decode(p,N);
        assert(strcmp(input,output)==0);
        delete[] input;
        delete[] p.first;
        delete[] output;
    }
}

int main() {
    test(2000);
    return 0;
}

