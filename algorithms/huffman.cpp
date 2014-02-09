#include<iostream>
#include<cstdio>
#include<queue>
#include<cstdlib>
#include "constants.hpp"
using namespace std;

struct node {
    int weight;
    bool value;
    char letter;
    node * left, *right;
    node (char l, int w) : letter(l), weight(w) {}
    node (int w, node *a, node* b) : weight(w), left(a), right(b), letter(0) {}
} *N[50];

class mycomparison
{
    public:
        bool operator() (const node* lhs, const node* rhs) const
        {
            return (lhs->weight > rhs->weight);
        }
};

void DFS(node* x, vector<char>& tmp, vector<char>* codes) {
    if(x->letter == 0) {
        tmp.push_back('0');
        DFS(x->left,tmp,codes);
        tmp.pop_back();

        tmp.push_back('1');
        DFS(x->right,tmp,codes);
        tmp.pop_back();
    } else {
        codes[x->letter-'A']=tmp;
        /*
        printf("%c : ", x->letter);
        for(int i = 0; i<tmp.size(); i++)
            printf("%c", tmp[i]);
        printf("\n");
        */
    }
}

int charsToInt(vector<char>& v, int k) {
    int res = 0, pow = 1;
    for(int i=k+7; i>=k; i--) res += (pow*((v[i]=='1')?1:0)), pow*=2;
    return res; 
}

vector<int> huff_encode(char *input, int size) {
    vector<char> codes[ALPHABET_SIZE];
    int P[ALPHABET_SIZE];
    for(int i=0; i<ALPHABET_SIZE; i++) P[i]=0;
    
    for(int i=0; i<size; i++) P[input[i]-'A']++;
    priority_queue<node*, vector<node*>, mycomparison> Q;
    for(int i=0; i<ALPHABET_SIZE; i++) Q.push(new node('A'+i, P[i]));

    while(Q.size() > 1) {
        node *x = Q.top();
        Q.pop();
        node *y = Q.top();
        Q.pop();
        node *newTree = new node(x->weight+y->weight, x, y);
        Q.push(newTree); 
    }
    
    vector<char> tmp;
    DFS(Q.top(),tmp,codes);
    tmp.clear();

    vector<int> result;

    for(int i=0; i<size; i++) {
        int x = input[i]-'A';
        for(int j=0; j<codes[x].size(); j++) {
            tmp.push_back(codes[x][j]);
        }
    }
    while(tmp.size()%8!=0)tmp.push_back('0');
       
    for(int i=0; i<tmp.size(); i+=8)     
        result.push_back(charsToInt(tmp,i));
    
    return result;
}
