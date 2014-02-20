#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include "BurrowsWheeler.hpp"
#include "constants.hpp"
#include<cstdlib>
using namespace std;

char* rand_array(int N) {
    srand(time(NULL));
    char *tmp = new char[N+1];
    tmp[N]=0;
    for(int i=0; i<N; i++)tmp[i]='A'+rand()%ALPHABET_SIZE;
    return tmp;
}

int main(int argc, const char* argv[]) {

    if(argc<2) return 0;
    int n = atoi(argv[1]);
    printf("%d\n", n);

    char *out = rand_array(n);
    printf("%s\n", out);
    return 0;
}
