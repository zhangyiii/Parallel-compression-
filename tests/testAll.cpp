#include<iostream>
#include<cstdio>
#include "huffman.hpp"
#include "BurrowsWheeler.hpp"
#include "constants.hpp"
#include "commonfunc.hpp"
#include "MoveToFront.hpp"
#include<cassert>
#include<cstring>
using namespace std;

int main() {
    int size;
    scanf("%d", &size);
    char * buf_1 = new char[size];
    char * buf_2 = new char[size];
    char *in = new char[size], *out = new char[size];
    scanf("%s", in);

// encoding
    //BWT
    pair<char*,int> enc = par_bwt_encode(in,size);
    //printf("\n%s\n", enc.first);
    size++;
    //MoveToFront 
    mtf_encode(enc.first, buf_1, size);
    //huffman buf_1->result.txt
    vector<char> result = huff_encode(buf_1, size, "result.txt");

// decoding	
    //huffman result.txt -> buf_1
    result = huff_decode("result.txt");
    for(int i = 0; i<size; i++) buf_1[i] = result[i];
    //MoveToFront buf_1 -> buf_2
    mtf_decode(buf_1, buf_2, size);
    //BWT -> out
    out = par_bwt_decode(make_pair(buf_2,enc.second),size-1);
    // check correctness
    assert(strcmp(in,out)==0);
    cout<<"OK"<<endl;

    //printf("out:\n");
    //printf("%s\n", out);

	return 0;
}

