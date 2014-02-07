#include<iostream>
#include<cstdio>
#include<stdlib.h>     /* srand, rand */
#include<time.h>       /* time */

using namespace std;

int main() {
	srand(time(0));
	int N;
	scanf("%d", &N);
	for(int i = 0; i<N; i++)
		printf("%c", ( (rand()%26) + 'A'));
	return 0;
}
