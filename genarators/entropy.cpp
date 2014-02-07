#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const int size = 26;

double P[size];

int main() {
	int N;
	scanf("%d\n", &N);
	
	for(int i = 0; i<N; i++) {
		char c;
		scanf("%c", &c);
		P[c-'A']++;
	}
	
	double result = 0;
	
	for(int i = 0; i<size; i++) {
		if(P[i] > 0)
			result -= (P[i]/N) * log(P[i]/N); 
	}
	
	printf("%lf\n", result);
	
	return 0;
}
