#include<iostream>
#include<cstdio>
#include "MoveToFront.hpp"

using namespace std;

int bufferSize = 16;

int main() {
	char * buf_in = new char[bufferSize];
	char * buf_out = new char[bufferSize];
	
	
	for(int i = 0; i<bufferSize; i++)
		scanf("%c", &buf_in[i]);
		
	mtf_encode(buf_in, buf_out, bufferSize);
	
	for(int i = 0; i<bufferSize; i++)
		printf("%c", buf_out[i]);
	printf("\n");
		
	mtf_encode(buf_out, buf_in, bufferSize);
	
	for(int i = 0; i<bufferSize; i++)
		printf("%c", buf_in[i]);
	printf("\n");
	

	delete[] buf_in;
	delete[] buf_out;
}
