#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<functional>
#include "constants.hpp"
using namespace std;

// returns pair of pointer to the encoded string and special index I
pair<char*,int> bwt_encode(char *input, int N) {
    char *L = new char[N+1]; L[N]=0;
    vector<int> tmp;
    int I;
    for(int i=0; i<N; i++) tmp.push_back(i);

    function<bool(int,int)> comp = [input,N] (int i,int j) { 
        int k=0;
        while(k<N && input[(i+k)%N] == input[(j+k)%N] ) k++;
        return input[(i+k)%N] < input[(j+k)%N];
    }; 

    sort(tmp.begin(),tmp.end(),comp);
    for(int i=0; i<N; i++) {
        if(tmp[i]==0)I=i;
        L[i]=input[(tmp[i]-1+N)%N];
    }
    return make_pair(L,I);
}

// returns the pointer to the output = decoded input
char* bwt_decode(pair<char*,int> enc, int N) {
    char *input = enc.first;
    int I = enc.second;
    int C[ALPHABET_SIZE+1], P[N+1];
    
    for(int i=0; i<ALPHABET_SIZE; i++) C[i]=0;
    for(int i=0; i<N; i++) {
        P[i] = C[input[i]-ALPHABET_FIRST];
        C[input[i]-ALPHABET_FIRST]++;
    }
    for(int i=0,sum=0; i<ALPHABET_SIZE; i++) {
        sum += C[i];
        C[i] = sum - C[i];
    }

    char *S = new char[N+1]; S[N]=0;
    for(int i=N-1, j=I; i>=0; i--) {
        S[i] = input[j];
        j = P[j] + C[input[j]-ALPHABET_FIRST];
    }

    return S;
}

