#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <ctime>
#include <windows.h>

using namespace std;

void showBoard(string (*board)[8]){
  //system("cls"); //WINDOWS ONLY
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

void update(string (*board)[8], string move){
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
    // cout<<sequenceInt.at(i)<<"\t";
  }
  cout<<endl;
  
  //Dealing with multipe moves at once
  if(sequenceInt.size()>2){
    for(int i=1; i<((int)sequenceInt.size()-1); i++){
      sequenceInt.insert(sequenceInt.begin()+i, sequenceInt[i]);
      i++;
    }
  }
  

    
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
	
      // cout<<"\t\t"<<a<<"\t\t"<<b<<endl;
      figure = board[a][b];
      if((a+b)%2==0)
	board[a][b] = "🔲";
      else
	board[a][b] = "🔳";
      a=0;
    }
    
    else if(i%2!=0){
      // cout<<"\t\t\t\t\t"<<sequenceInt.at(i)<<endl;
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
      
      // cout<<"\t\t"<<a<<"\t\t"<<b<<endl;
      board[a][b] = figure;
    }
  }  

}
vector<string> gameManager(string (*board)[8], bool player, bool &gameEnded, bool &whiteWon){
  int nOfWhite = 0, nOfBlack = 0;
  vector<string> allPossibleMoves;
  //check if game aleady ended
  for(int i=0; i<8;i++)
    for(int j=0; j<8; j++){
      if(board[i][j]=="💀")//white
	nOfWhite++;
      if(board[i][j]=="🤡")//black
	nOfBlack++;
    }
  if(nOfWhite==0||nOfBlack==0){
    
    gameEnded = !gameEnded;
    return allPossibleMoves;
  }

  if()
  
  return allPossibleMoves;
}
string elmo(string (*board)[8], bool elmoColor){
  string example="12x13";
  cout<<example<<endl;
  //searching for all possible moves
  if(elmoColor)
    cout<<"im skull\n";
  
  else
    cout<<"im clown\n";
      
  //picking the righr one

  return example;

}
//White 1
//Black 0
int main(int argc, char** argv){

  std::string  board[8][8];
  vector<string> allPossibleMoves;
  string move="0";
  bool elmoColor = true; //bot checker color - white
  bool player = false; // Black on move
  bool gameEnded = false;
  bool GUIMode = true;
  bool whiteWon = true;

  initBoard(board);
  
  if((string)argv[1] == "NET")
    GUIMode = false;
  if((string)argv[2] == "BLACK")
    elmoColor = false;
  
  while(!gameEnded){
    if(GUIMode)
      showBoard(board);

    
    if(elmoColor == player)
      move=elmo(board,elmoColor);
    else
      cin>>move;

    
    allPossibleMoves = gameManager(board, player, gameEnded, whiteWon);
    
    update(board,move);
   
      
    player = !player;
    if(gameEnded){
      if(whiteWon)
	cout<<"White won";
      else
	cout<<"BLack won";
    }
  }
  
}
