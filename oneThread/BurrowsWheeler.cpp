#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>

namespace BurrowsWheeler {

char *buffer;
int N;

const char ALPHABET_FIRST = 'A';
const char ALPHABET_LAST = 'Z';
const int ALPHABET_SIZE = ALPHABET_LAST - ALPHABET_FIRST + 1;

bool comp(int i,int j) {
    int k=0;
    while(k<N && buffer[(i+k)%N] == buffer[(j+k)%N] ) k++;
    return buffer[(i+k)%N] < buffer[(j+k)%N];
}

// returns pair of pointer to the encoded string and special index I
std::pair<char*,int> encode(char *input, int length) {
    buffer = input;
    N = length;
    char *L = new char[N+1];
    L[N]=0;
    std::vector<int> tmp;
    int I;
    for(int i=0; i<N; i++) tmp.push_back(i);
    std::sort(tmp.begin(),tmp.end(),comp);
    for(int i=0; i<N; i++) {
        if(tmp[i]==0)I=i;
        L[i]=buffer[(tmp[i]-1+N)%N];
    }
    return std::make_pair(L,I);
}

// returns the pointer to the output = decoded input
char* decode(std::pair<char*,int> enc, int length) {
    char *input = enc.first;
    int I = enc.second;
    int *C = new int[ALPHABET_SIZE+1];
    int *P = new int[length+1];
    for(int i=0; i<ALPHABET_SIZE; i++) C[i]=0;
    for(int i=0; i<length; i++) {
        P[i] = C[input[i]-ALPHABET_FIRST];
        C[input[i]-ALPHABET_FIRST]++;
    }
    int sum = 0;
    for(int i=0; i<ALPHABET_SIZE; i++) {
        sum += C[i];
        C[i] = sum - C[i];
    }
    char *S = new char[length+1];
    S[length]=0;
    int j = I;
    for(int i=length-1; i>=0; i--) {
        S[i] = input[j];
        j = P[j] + C[input[j]-ALPHABET_FIRST];
    }
    return S;
}

}
