#include<iostream>
#include<cstdio>
#include<stdlib.h>     /* srand, rand */
#include<time.h>       /* time */

using namespace std;

int main() {
	srand(time(0));
	int N;
	scanf("%d", &N);
	
	for(int i = 0; i<N; i++) {
		int tmp = (rand() % ((26*27)/2 - 1)) +1;
		int x = 1, sum = 0;
		
		while(sum+x <= tmp)
			sum += x++;
			
		x--;
		printf("%c", x + 'A');
	}
	
	return 0;
}
