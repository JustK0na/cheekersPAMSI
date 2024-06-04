#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <windows.h>

using namespace std;

void showBoard(string (*board)[8]){
  system("cls"); //WINDOWS ONLY
  cout<<"  ";
  for(int i=0; i<8; i++)
    cout<<i<<" ";
  cout<<endl;
  for(int i=0; i<8; i++){
    cout<<i<<" ";
    for(int j=0; j<8; j++){
      cout<<board[i][j];
    }
    cout<<endl;
  }
  cout<<"*******************"<<endl;
}

void initBoard(string (*board)[8]){
  
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if((i+j)%2==0)
	board[i][j] = "🔲";
      else
	 board[i][j] = "🔳";
    }
  }


  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if(i<3&&(i+j)%2!=0)
	board[i][j] = "🤡";//Black ;
      else if(i>4&&(i+j)%2!=0)
	board[i][j] = "💀";//White
    }
  }

}

void update(string (*board)[8], string move, bool player){
  //decode move
  vector<string> sequence;
  vector<char> helpChar;
  vector<int> sequenceInt;
  istringstream stringStream(move);
  string tmp="";
  string figure = "";
  char c;
  int a=0,b=0,pom=0;

  //decode move
  while(stringStream.get(c)){
    helpChar.push_back(c);
    tmp="";
    if(c=='x'||c=='-'){
      for(int i=0; i<(int)helpChar.size()-1; i++)
	tmp += helpChar.at(i);
      
      sequence.push_back(tmp);
      helpChar.clear();
    }
  }
  //last move
  for(int i=0; i<(int)helpChar.size(); i++)
    tmp += helpChar.at(i);
  sequence.push_back(tmp);
  helpChar.clear();
  
  
  //sanity check
  for(int i=0; i<(int)sequence.size(); i++){
    sequenceInt.push_back(stoi(sequence.at(i)));
    //    cout<<sequenceInt.at(i)<<"\t";
  }
  //  cout<<endl;
  //update board 
  for(int i=0; i<(int)sequenceInt.size(); i++){
    a=0;
    if(i%2==0){
      pom = sequenceInt.at(i);
      while(pom>0){
	pom -= 4;
	a++;
      }
      a--;
      if(a%2==0){
	b = 2*pom + 7;
      }
      else{
	b = 2*pom + 6;
      }
	
      cout<<"\t\t"<<a<<"\t\t"<<b<<endl;
      figure = board[a][b];
      if((a+b)%2==0)
	board[a][b] = "🔲";
      else
	board[a][b] = "🔳";
      a=0;
    }
    
    else if(i%2!=0){
      cout<<"\t\t\t\t\t"<<sequenceInt.at(i)<<endl;
      pom = sequenceInt.at(i);
      while(pom>0){
	pom -= 4;
	a++;
      }
      a--;
      if(a%2==0){
	b = 2*pom + 7;
      }
      else{
	b = 2*pom + 6;
      }
      
      cout<<"\t\t"<<a<<"\t\t"<<b<<endl;
      board[a][b] = figure;
    }
  }  
}
void gameManager(string (*board)[8], string move, bool player){
  
}

int main(int argc, char** argv){

  std::string  board[8][8];
  string move="0";
  initBoard(board);

  
  while(1){
    showBoard(board);
    cin>>move;
    gameManager(board, move);
    update(board,move,1);
  }
  
}
