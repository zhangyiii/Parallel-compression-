#include<iostream>
#include<cstdio>
#include <queue>          
using namespace std;

const int size = 50;
const int alphabetSize = 4;

char input[size+1];
int P[alphabetSize];


struct node {
	int weight;
	bool value;
	char letter;
	node * left, *right;
	
	node (char l, int w) : letter(l), weight(w) {}
	
	node (int w, node *a, node* b) : weight(w), left(a), right(b), letter(0) {}
	
} *N[size];


class mycomparison
{
public:
  bool operator() (const node* lhs, const node* rhs) const
  {
    return (lhs->weight > rhs->weight);
  }
};

vector<char> result;

void DFS(node* x) {

	if(x->letter == 0) {
		result.push_back('0');
		DFS(x->left);
		result.pop_back();
		
		result.push_back('1');
		DFS(x->right);
		result.pop_back();
	} else {
		printf("%c : ", x->letter);
		
		for(int i = 0; i<result.size(); i++)
			printf("%c", result[i]);
			
		printf("\n");
	}
	
}

int main() {

	scanf("%s", input);
	
	for(int i = 0; i<size; i++)
		P[input[i]-'A']++;
		
	
	priority_queue<node*, vector<node*>, mycomparison> Q;
	
	for(int i = 0; i<alphabetSize; i++) {
		Q.push(new node('A'+i, P[i]));
	}
	
	while(Q.size() > 1) {
		node *x = Q.top();
		Q.pop();
		node *y = Q.top();
		Q.pop();
		
		node *newTree = new node(x->weight+y->weight, x, y);
		
		Q.push(newTree); 
	}
	
	DFS(Q.top());
		
}
