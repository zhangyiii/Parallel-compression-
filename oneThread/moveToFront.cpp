#include<iostream>
#include<cstdio>

using namespace std;

const int alphabetSize = 26;
const int bufferSize = 18;

void mtf_encode (char *buf_in, char *buf_out, int size) {
    char state[alphabetSize];
 
    for(int i = 0; i <alphabetSize; ++i)
        state[i] = i;
        
    for (int i = 0; i<size; i++) {
        buf_out[i] = state[buf_in[i]-'A']+'A';
        for (int j = 0; j<alphabetSize; ++j)
            if (state[j] < state[buf_in[i]-'A'])
                ++state[j];
        state[buf_in[i]-'A'] = 0;
    }
}

void mtf_decode (char *buf_in, char *buf_out, int size) {
   	char state[alphabetSize];
    char tmp;
 
    for (int i = 0; i<alphabetSize; ++i)
        state[i] = i;
        
    for (int i = 0; i<size; ++i) {
        buf_out[i] = state[buf_in[i]-'A'];
        tmp = state[buf_in[i]-'A'];
        for (int j = buf_in[i]; j ; --j)
            state[j] = state[j-1];
        state[0] = tmp;
    }
}


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
