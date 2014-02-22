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
	scanf("%s", buf_1);
	
	//T B-W buf_1 -> buf_2
	for(int i = 0; i<size; i++)
		buf_2[i] = buf_1[i];
		
		
	//MoveToFront buf_2 -> buf_1
	mtf_encode(buf_2, buf_1, size);
	
	
	//huffman buf_1->result.txt
	vector<char> result = huff_encode(buf_1, size, "result.txt");
	
	//end of coding
	
	
	
	//huffman result.txt -> buf_2
	result = huff_decode("result.txt");
	for(int i = 0; i<size; i++)
		buf_2[i] = result[i];
	
	//MoveToFront buf_2 -> buf_1
	mtf_decode(buf_2, buf_1, size);
	
	//T B-W buf_1 -> buf_2
	for(int i = 0; i<size; i++)
		buf_2[i] = buf_1[i];
		
	//end of decoding
	
	
	for(int i = 0; i<size; i++)
		printf("%c", buf_2[i]);
	printf("\n");	
	 
	return 0;
}

