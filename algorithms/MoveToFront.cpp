#include<iostream>
#include<cstdio>
#include "constants.hpp"
using namespace std;


void mtf_encode (char *buf_in, char *buf_out, int size) {
    char state[ALPHABET_SIZE];
 	#pragma omp parallel num_threads(8)
    {
    	#pragma omp for schedule(dynamic, 1) nowait firstprivate(ALPHABET_SIZE)
    	for(int i = 0; i <ALPHABET_SIZE; ++i)
        	state[i] = i;
    }
        
    for (int i = 0; i<size; i++) {
        buf_out[i] = state[buf_in[i]-'A']+'A';
        #pragma omp parallel num_threads(8)
    	{
    		#pragma omp for schedule(dynamic, 1) nowait firstprivate(ALPHABET_SIZE)
       		for (int j = 0; j<ALPHABET_SIZE; ++j) {
           		if (state[j] < state[buf_in[i]-'A'])
                	++state[j];
        	}
        }
        state[buf_in[i]-'A'] = 0;
    }
}

void mtf_decode (char *buf_in, char *buf_out, int size) {
    char state[ALPHABET_SIZE];
    char tmp;
 
    #pragma omp parallel num_threads(8)
    {
    	#pragma omp for schedule(dynamic, 1) nowait firstprivate(ALPHABET_SIZE)
    	for(int i = 0; i <ALPHABET_SIZE; ++i)
        	state[i] = i;
    }
        
    for (int i = 0; i<size; ++i) {
        buf_out[i] = state[buf_in[i]-'A'];
        tmp = state[buf_in[i]-'A'];
        for (int j = buf_in[i]; j ; --j)
            state[j] = state[j-1];
        state[0] = tmp;
    }
}

