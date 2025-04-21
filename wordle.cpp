#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void stringSetter(std::string &word, int loc, std::set<std::string>& retVal,std::string floating, int n, const std::set<std::string>& dict, int spaces);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    int n = in.size();
    std::string word = in;
    std::set<std::string> results;
    int spaces_ = 0;
    for(unsigned int i=0; i<in.size(); i++){
      if(in[i] == '-'){
        ++spaces_;
      }
    }
    // std::map<char, int> constraints;
    // for(unsigned int i=0; i<floating.size(); i++){
    //   constraints[floating[i]]+=1;
    // }
    stringSetter(word, 0, results, floating, n, dict, spaces_);

    return results;
}

// Define any helper functions here

void stringSetter(std::string &word, int loc, std::set<std::string>& retVal,std::string floating, int n, const std::set<std::string>& dict, int spaces){
  if(loc==n){
    if(floating.empty() && dict.find(word)!=dict.end()){
        retVal.insert(word);
        return;
    }
  }
  if(word[loc]!='-'){
    if(loc==(n)){
      // cout<<"2"<<endl;
      if(floating.empty() && dict.find(word)!=dict.end()){
        retVal.insert(word);
        return;
      }
    }else{
      // cout<<loc<<endl;
      stringSetter(word, loc+1, retVal, floating, n ,dict, spaces);
      
    }
   // return;
  }else{
    if(spaces == floating.size()){
      for(unsigned int i = 0; i<floating.size(); i++){
        int filled=1;
        char insert_ = floating[i];
        word[loc] = floating[i];
        --spaces;
        floating.erase(i, 1);
        
        stringSetter(word, loc+1, retVal, floating, n ,dict, spaces);
          
        word[loc] = '-'; 
        ++spaces;
        if(filled==1){
            floating.insert(floating.begin()+i, insert_);
        }  
      }
    }else{
      for(char i = 'a'; i<='z'; i++){
        int filled=0;
        word[loc] = i;
        --spaces;
        size_t pos = floating.find(i);
        if(pos!=std::string::npos){
          filled=1;
          floating.erase(pos, 1);
        }
        stringSetter(word, loc+1, retVal, floating, n ,dict, spaces);
          
        word[loc] = '-'; 
        ++spaces;
        if(filled==1){
            floating.insert(floating.begin()+pos, i);
        }
      }
    }
    
  }
  
  
}