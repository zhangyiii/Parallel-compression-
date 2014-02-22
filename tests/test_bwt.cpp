#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include "BurrowsWheeler.hpp"
#include "constants.hpp"
#include "commonfunc.hpp"
#include<cstdlib>
using namespace std;


void test_seq_correctness(int trials) { 
    srand(time(NULL));
    for(int i=0; i<trials; i++) {
        int N = 1000+rand()%9000;
        char *input = getRandomInput(N);
        pair<char*,int> p = seq_bwt_encode(input,N);
        char *output =  seq_bwt_decode(p,N);
        assert(strcmp(input,output)==0);
        delete[] input;
        delete[] p.first;
        delete[] output;
    }
    cout<<"test_seq_correctness PASSED"<<endl;
}

void test_par_correctness(int trials) {
    srand(time(NULL));
    for(int i=0; i<trials; i++) {
        int N = 1000+rand()%9000;
        char *input = getRandomInput(N);
        pair<char*,int> p = par_bwt_encode(input,N);
        char *output =  par_bwt_decode(p,N);
        //cout<<"test "<<i<<endl;
        //print(input,N);
        //print(p.first,N);
        //print(output,N);
        assert(strcmp(input,output)==0);
        delete[] input;
        delete[] p.first;
        delete[] output;
    }
    cout<<"test_par_correctness PASSED"<<endl;
}

void test_suffix_sort(char *input, int N) {
    
    function<bool(int,int)> comp = [input,N] (int i,int j) { 
        int k=0;
        while(k<N && input[(i+k)%(N)] == input[(j+k)%(N)] ) k++;
        return input[(i+k)%(N)] < input[(j+k)%(N)];
    }; 

    vector<int> v;
    for(int i=0; i<N; i++) v.push_back(i);
    sort(v.begin(),v.end(),comp);

    int *SUF = par_suffix_array(input,N);
    for(int i=0; i<N; i++){
        if(SUF[i]!=v[i]){
            cout<<"i="<<i<<" SUF[i]="<<SUF[i]<<" v[i]="<<v[i]<<endl;
        }
        assert(SUF[i]==v[i]);
    }

    cout<<"test_suffix_sort PASSED"<<endl;
}

void test_particular(int argc, const char *argv[] ) {
    if(argc<2) {
        cout<<"Give me the argument (1 = parallel, 2 = sequential)"<<endl;
        exit(0);
    }
    int n;
    cin>>n;
    char *input = new char[n];
    for(int i=0; i<n; i++)cin>>input[i];

    cout<<"TESTS OPTIONS:"<<endl;
    cout<<"PREF_WIDTH FOR PARALLEL SORTING = "<<PREF_WIDTH<<endl;
    cout<<"ALPHABET_SIZE = "<<ALPHABET_SIZE<<endl;
    cout<<"INPUT SIZE = "<<n<<endl;

    int x = atoi(argv[1]);

    if(x==1) {
        cout<<"PARALLEL ENCODING"<<endl;
        par_bwt_encode(input,n);
    }
    else if(x==2) {
        cout<<"SEQUENTIAL ENCODING"<<endl;   
        seq_bwt_encode(input,n);
    }
}

int main(int argc, const char *argv[]) {

    test_par_correctness(200);
    test_seq_correctness(200);
   /* 
    int n = 20;
    char *input = getRandomInput(n);
    test_bwt_result(input,n+1);
    */
    return 0;
}

