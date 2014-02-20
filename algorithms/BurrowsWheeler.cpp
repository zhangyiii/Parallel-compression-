#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
#include<functional>
#include<omp.h>
#include<cmath>
#include<cassert>
#include "constants.hpp"
using namespace std;

int get_hash(char *input, int N, int j) {
    int result = 0;
    for(int i=0; i<PREF_WIDTH; i++) {
        result += (input[(j+i)%N]-(int)'A')*pow(ALPHABET_SIZE,PREF_WIDTH-i-1);
    }
    return result;
}

int _min(int a,int b) { return (a<b)?a:b; }

void par_suffix_array(char *input, int N, int *SUF) {
    
    int BLENGTH = pow(ALPHABET_SIZE,PREF_WIDTH);
    int *B = new int[BLENGTH], *hashes = new int[N];
    for(int i=0; i<BLENGTH; i++)B[i]=0;

    int num_threads = 10;
    int block_width = (N+num_threads)/num_threads;
    omp_set_num_threads(num_threads);

 #pragma omp parallel shared(input,N,num_threads,block_width,B)
 {
    int tid = omp_get_thread_num();
    int first = tid * block_width;
    int last = (tid+1) * block_width - 1;

    for(int i=first; i<=last && i<N; i++) {
        int hash = get_hash(input,N,i);
        hashes[i] = hash;
        #pragma omp critical
        B[hash]++;
    }
 }
    // prefsum
    for(int i=1; i<BLENGTH; i++) B[i]+=B[i-1];   
    vector<int> buckets; // ends+1 of the buckets (consistent fragments in terms of common prefix)
    buckets.push_back(0);   
 
    int tmp=-1;
    for(int i=0; i<BLENGTH; i++) {
        if(B[i]!=tmp){
            buckets.push_back(B[i]);
            tmp=B[i];
        }
    }

/*
    for(int i=0; i<buckets.size(); i++) cout<<buckets[i]<<" ";
    cout<<endl;
*/

 #pragma omp parallel shared(B,SUF,N)
 {
    int tid = omp_get_thread_num();
    int first = tid * block_width;
    int last = (tid+1) * block_width - 1;
    
    for(int i=first; i<=last && i<N; i++){
        #pragma omp critical
        SUF[--B[hashes[i]]]=i;

    }
 }

/*
    cout<<"---"<<endl;
    for(int i=0; i<buckets.size()-1; i++) {
        int a=buckets[i];
        int b=buckets[i+1];
        cout<<"from "<<a<<" to "<<b<<endl;
        for(int j=a; j<b; j++) {
            int x = SUF[j];
            for(int k=0; k<N; k++)cout<<input[(x+k)%N];
            cout<<endl;
        }
    }
    cout<<"---"<<endl;
*/
 
    num_threads = _min(buckets.size(), omp_get_max_threads());
    block_width = (buckets.size()+num_threads)/num_threads;    

    function<bool(int,int)> comp = [input,N] (int i,int j) { 
        int k=0;
        while(k<N && input[(i+k)%N] == input[(j+k)%N] ) k++;
        return input[(i+k)%N] < input[(j+k)%N];
    }; 
 
 #pragma omp parallel shared(buckets,comp)
 {

    int tid = omp_get_thread_num();
    int first = _min(tid*block_width,buckets.size()-1);
    int last = _min((tid+1)*block_width,buckets.size()-1);
 
    if(buckets[first]<=N && buckets[last]<=N) 
        sort(SUF+buckets[first], SUF+buckets[last], comp);    
 }

}    

pair<char*,int> par_bwt_encode(char *input, int N) {
    int *SUF = new int[N];
    par_suffix_array(input,N,SUF);
    char *L = new char[N+1]; L[N]=0;
    int I;   
    for(int i=0; i<N; i++) {
        if(SUF[i]==0)I=i;
        L[i]=input[(SUF[i]-1+N)%N];
    }
    return make_pair(L,I);
}
char* par_bwt_decode(pair<char*,int> enc, int N) {

    return NULL;
}


/*
 * SEQUENTIAL BWT
 */

// returns pair of pointer to the encoded string and special index I
pair<char*,int> seq_bwt_encode(char *input, int N) {
    char *L = new char[N+1]; L[N]=0;
    vector<int> tmp;
    int I;
    for(int i=0; i<N; i++) tmp.push_back(i);

    function<bool(int,int)> comp = [input,N] (int i,int j) { 
        int k=0;
        while(k<N && input[(i+k)%(N+0)] == input[(j+k)%(N+0)] ) k++;
        return input[(i+k)%(N+0)] < input[(j+k)%(N+0)];
    }; 

    sort(tmp.begin(),tmp.end(),comp);
    for(int i=0; i<N; i++) {
        if(tmp[i]==0)I=i;
        L[i]=input[(tmp[i]-1+N)%N];
    }
    return make_pair(L,I);
}

// returns the pointer to the output = decoded input
char* seq_bwt_decode(pair<char*,int> enc, int N) {
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

