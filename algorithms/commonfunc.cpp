#include<iostream>
#include"constants.hpp"
using namespace std;

void printSuf(char *input, int N, int j) {
    for(int i=j; i<N; i++) cout<<input[i];
    cout<<endl;
}

void printAllSuf(char *input, int N) {
    for(int i=0; i<N-1; i++) printSuf(input,N,i);
}

void printCyclicShift(char *input, int N, int j) {
    for(int i=0; i<N; i++) cout<<input[(j+i)%N];
    cout<<endl;
}

void printAllCyclicShifts(char *input, int N) {
    for(int i=0; i<N; i++) printCyclicShift(input,N,i);
}

void print(char *input, int N) {
    printSuf(input,N,0);
}

char* getRandomInput(int N) {
    srand(time(NULL));
    char *tmp = new char[N+1];
    tmp[N]=0;
    for(int i=0; i<N; i++) tmp[i]='A'+rand()%(ALPHABET_SIZE); 
    return tmp; 
}

