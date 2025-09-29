#include<iostream>
#include<nlohmann/json.hpp>
#include<vector>
#include<string>
#include<sstream>
#include<cctype>
#include<queue>
#include<stack>
#include<fstream>
#include <typeinfo>

using namespace std;
using namespace nlohmann;


map<string, vector<int>> operations = {{"not", {10, 1}}, {"all", {10, -1}}, {"exist", {10, -1}},{"->", {3, 2}}};


template<typename T>
void modus_ponens(T& form, vector<string> antecedent){
  form["conclusion"].push_back({{{"formul", antecedent}, {"conclusion", vector<string>{}}}});
  cout << form["formul"];
  for(string i : form["formul"]){
      antecedent.push_back(i);
    }
  antecedent.push_back("->");
  form["conclusion"].push_back({{{"formul", antecedent}, {"conclusion", vector<string>{}}}});
  
}

void shuting_yard(string &token, vector<string> & polish, stack<string> &op){
  if(!op.empty()){
    if(operations[token][0] <= operations[op.top()][0]){
      while(!op.empty()){
	polish.push_back(op.top());
	op.pop();
      }
    }
  }
  op.push(token);
  token = "";
}

vector<vector<string>> synonyms = {};


int main(){
  vector<string> polish;
  stack<string> op;
  string input = "";
  string token= "";
  bool alnum = false;
  json sequence;


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
	  polish.push_back(token);
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
	polish.push_back(token);
      }
      else{
	cout << "invalid sintax, operator " + token + " dosn`t exist" + "\n";
      }
    }

   while(not op.empty()){
    polish.push_back(op.top());
    op.pop();
  }

  for(string i : polish){
    cout << i << " ";
  }
  cout << "\n";
  sequence["formul"] = vector<string>{polish};
  sequence["conclusion"] = {};

  
  json * leaf = &(sequence["conclusion"]);
  vector<json *> leafs = {leaf};
  modus_ponens(sequence, vector<string>{"3", "->", "lol"});
  
  cout << sequence.dump(4) << "\n";
  ofstream file("./seq_json/seq_tree2");
  
  file << sequence.dump(4);
  return 0;
}  
