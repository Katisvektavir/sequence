#include<iostream>
#include<nlohmann/json.hpp>
#include<vector>
#include<string>
#include<sstream>
#include<cctype>
#include<queue>
#include<stack>

using namespace std;
using namespace nlohmann;


map<string, vector<int>> operations = {{"not", {10, 1}}, {"all", {10, -1}}, {"exist", {10, -1}},{"->", {3, 2}}};


void shuting_yard(string &token, queue<string> & polish, stack<string> &op){
  if(!op.empty()){
    if(operations[token][0] <= operations[op.top()][0]){
      while(!op.empty()){
	polish.push(op.top());
	op.pop();
      }
    }
  }
  op.push(token);
  token = "";
}

vector<vector<string>> synonyms = {};


int main(){
  queue<string> polish;
  stack<string> op;
  json data;
  string input = "";
  string token= "";
  bool alnum = false;
  getline(cin, input);
  for(char i : input){
    
    if(isalnum(i)){
      if(!token.empty() and !alnum){
	if(operations.count(token)){
	  shuting_yard(token, polish, op);
	}
	else{
	  cout << "invalid sintax, operator " + token + " dosn`t exist" + "\n";
	}
      }	
	token += i;
	alnum = true;
    }
    else{
      if(!token.empty() and alnum){
	if(operations.count(token)){
	  shuting_yard(token, polish, op);
	}
	else{
	  polish.push(token);
	  token = "";
	}
      }
      if(i != ' '){
	token += i;
      }
      alnum = false;
    }
  }
  
   if(!token.empty()){
      if(operations.count(token)){
	shuting_yard(token, polish, op);
      }
      else if(alnum){
	polish.push(token);
      }
      else{
	cout << "invalid sintax, operator " + token + " dosn`t exist" + "\n";
      }
    }
  while(not op.empty()){
    polish.push(op.top());
    op.pop();
  }
  while(not polish.empty()){
    cout << polish.front() << "\n";
    polish.pop();
  }
  
  return 0;}
  
