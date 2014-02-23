#include<iostream>
#include<cstdio>
#include<queue>
#include<cstdlib>
#include"constants.hpp"
#include<boost/archive/text_oarchive.hpp> 
#include<boost/archive/text_iarchive.hpp> 
#include<sstream> 
#include<cstring>
#include<fstream> 
using namespace std;

struct node {
    int weight;
    bool value;
    char letter;
    node * left, *right;
    node() : left(NULL), right(NULL), weight(0), value(0), letter(0) {};
    node (char l, int w) : letter(l), weight(w), value(1), left(NULL), right(NULL) {}
    node (int w, node *a, node* b) : weight(w), left(a), right(b), letter(0), value(1) {}
    
private: 
  	friend class boost::serialization::access; 

	template <typename Archive> 
	void serialize(Archive &ar, const unsigned int version) 
	{ 
    	ar & weight;
    	ar & value;
    	ar & letter;
    	ar & left;
    	ar & right;
	} 
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
        codes[x->letter-'@']=tmp;
        
        /*printf("%c : ", x->letter);
        for(int i = 0; i<tmp.size(); i++)
            printf("%c", tmp[i]);
        printf("\n");*/
        
    }
}

int charsToInt(vector<char>& v, int k) {
    int res = 0, pow = 1;
    for(int i=k+7; i>=k; i--) res += (pow*((v[i]=='1')?1:0)), pow*=2;
    return res; 
}

vector<char> huff_encode(char *input, int size, string fileName) {
    vector<char> codes[ALPHABET_SIZE];
    int P[ALPHABET_SIZE];
    for(int i=0; i<ALPHABET_SIZE; i++) P[i]=0;
    
    for(int i=0; i<size; i++) P[input[i]-'@']++;
    priority_queue<node*, vector<node*>, mycomparison> Q;
    
    for(int i=0; i<ALPHABET_SIZE; i++) 
    	if(P[i] > 0)
    		Q.push(new node('@'+i, P[i]));

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
        int x = input[i]-'@';
        for(int j=0; j<codes[x].size(); j++) {
            tmp.push_back(codes[x][j]);
        }
        //tmp.push_back(' ');
    }
    
    /*while(tmp.size()%8!=0)tmp.push_back('0');
       
    for(int i=0; i<tmp.size(); i+=8)     
        result.push_back(charsToInt(tmp,i));
    
    return result;*/
    
    node n = *Q.top();
    
    std::ofstream file(fileName); 
 	boost::archive::text_oarchive oa(file);  
  	oa << n; 
  	
  	int x = tmp.size();
  	oa << x;
  	
  	//for(int i = 0; i<tmp.size(); i++) oa << tmp[i];
  	
  	ofstream myfile;
  	myfile.open("tree.txt");
  	
 	for(int i = 0; i<tmp.size(); i++)
 		myfile<<tmp[i];
 		
  	myfile.close();
    
    return tmp;
}

std::vector<char> huff_decode(std::string fileName) {

  	std::ifstream file(fileName); 
  	boost::archive::text_iarchive ia(file); 
  	node n; 
  	ia >> n;
  	
  	int size;
  	ia >> size;
  	
  	vector<char> tmp;
  	
  	ifstream myfile;
  	myfile.open("tree.txt");
  	
  	for(int i = 0; i<size; i++) {
  		char x;
  		myfile >> x;
  		tmp.push_back(x);
  	}
  	myfile.close();
  	
  	node * root = &n, * w = &n;
  	vector<char>result;
  	
  	for(int i = 0; i<tmp.size(); i++) {

  		if(tmp[i] == '0') {
  			w = w->left;
  		} else {
  			w = w->right;
  		}
  		
  		if(w->letter != 0) {
  			result.push_back(w->letter);
  			w = root;
  		}
  		
  	}
  	
  	return result;
  	 
}
