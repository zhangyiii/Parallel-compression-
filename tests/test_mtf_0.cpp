#include<iostream>
#include<cstdio>
#include "MoveToFront.hpp"
#include<cassert>
#include<cstring>

using namespace std;

int bufferSize = 1000000;

int main() {
	srand(time(NULL));
	#pragma omp parallel
	{
	#pragma omp for schedule(static) nowait
	for(int k = 0; k<100; k++) {
	
		char * buf_in = new char[bufferSize];
		char * buf_out = new char[bufferSize];
		char * result = new char[bufferSize];
	
		//for(int i = 0; i<bufferSize; i++)
		//	scanf("%c", &buf_in[i]); 
	
		for(int i=0; i<bufferSize; i++) buf_in[i] = 'A'+rand()%26;
		
		mtf_encode(buf_in, buf_out, bufferSize);
	
		/*for(int i = 0; i<bufferSize; i++)
			printf("%c", buf_out[i]);
		printf("\n");*/
		
		mtf_decode(buf_out, result, bufferSize);
	
		/*for(int i = 0; i<bufferSize; i++)
			printf("%c", buf_in[i]);
		printf("\n");*/
	
		//assert(strcmp(buf_in,result)==0);
		for(int i = 0; i<bufferSize; i++)
			if(buf_in[i] != result[i])
				cout<<"BLAD " << buf_in[i] << " " << result[i]<<endl;
	
		delete[] buf_in;
		delete[] buf_out;
		delete[] result;
	}
	}
}
