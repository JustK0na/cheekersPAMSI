#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <ctime>
#include <windows.h>
#include <stdlib.h>


//White 💀
//Black 🤡
//White_King 👑	
//Black_King 🎩
using namespace std;

void showBoard(string (*board)[8]){
  //system("cls"); //WINDOWS ONLY
  
  //system("clear"); //LINUX ONLY
  //cout << "\033[2J\033[1;1H"; //BOTH
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
	board[i][j] = "🔲";//black squere
      else
	board[i][j] = "🔳"; //whtie squere
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
  int a=0,b=0,olda=0, oldb=0,pom=0;

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
      olda = a;
      oldb = b;
      //cout<<"\t\t"<<a<<"\t\t"<<b<<endl;
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


      
      //cout<<"\t\t"<<a<<"\t\t"<<b<<endl;
      board[a][b] = figure;

      //Obsługa bicia !!DO WYMIANY!!
      //cout<<endl<<"olda: "<<olda<<"   a: "<<a<<" player: "<<player<<endl;
      if(!player&&a-olda>1){
	cout<<"doszlo tu do sigmy, clown"<<endl;
	a--;b=b+(oldb-b)/2;;
	if((olda+oldb)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
      if(!player&&olda-a>1){
	cout<<"doszlo tu do sigmy, clown"<<endl;
	a++;b=b+(oldb-b)/2; 
	if((olda+oldb)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
      if(player&&olda-a>1){
	cout<<"doszlo tu do sigmy, skull"<<endl;
	a++;b=b+(oldb-b)/2; 
	if((a+b)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
      if(player&&a-olda>1){
	cout<<"doszlo tu do sigmy, clown"<<endl;
	a--;b=b+(oldb-b)/2;;
	if((olda+oldb)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
    }
  }

  //Exhange for Kings
  if(player){
    for(int j=0; j<8; j++)
      if(board[0][j]=="💀")
	board[0][j]="👑";
  }
    
  else{
    for(int j=0; j<8; j++)
      if(board[7][j]=="🤡")
	board[7][j]="🎩";
  }

}
bool isOnBoard(int i, int j){
  return ((i>=0 && i<8)&&(j>=0&&j<8));
}
  
void addMove(vector<string> &moves, int oldi, int oldj, int i, int j){
  moves.push_back(to_string(oldi*4+oldj/2+1) + "-" + to_string(i*4+j/2+1));
}

void addCapture(vector<string> &captures, int oldi, int oldj, int i, int j){
  captures.push_back(to_string(oldi*4+oldj/2+1) + "x" + to_string(i*4+j/2+1));
}

vector<string> findAllPossibleMoves(string (*board)[8], bool player){
  
  vector<string> moves;
  vector<string> captures;
  int dir = 1; //if black is on move
  if(player)
    dir = -1; //if white is on move

  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      //Just for  Men
      //      cout<<"\n na polu: "<<i<<", "<<j;
      if((player && board[i][j]=="💀")||(!player && board[i][j]=="🤡")){
	//cout<<" znaleziono pionek należący do gracza ";
	
	if(isOnBoard(i+2*dir, j-2) && board[i+2*dir][j-2]=="🔳"){
	  if(!player&&(board[i+dir][j-1]=="💀"||board[i+dir][j-1]=="👑"))
	    addCapture(captures, i,j,i+2*dir, j-2);
	  if(player&&(board[i+dir][j-1]=="🤡"||board[i+dir][j-1]=="🎩"))
	    addCapture(captures, i,j,i+2*dir, j-2);
	}
      
	
	if(isOnBoard(i+2*dir, j+2)&& board[i+2*dir][j+2]=="🔳"){
	  if(!player&&(board[i+dir][j+1]=="💀"||board[i+dir][j+1]=="👑"))
	    addCapture(captures, i,j,i+2*dir, j+2);
	  if(player&&(board[i+dir][j+1]=="🤡"||board[i+dir][j+1]=="🎩"))
	    addCapture(captures, i,j,i+2*dir, j+2);
	}



	
	if(isOnBoard(i+dir, j-1) && board[i+dir][j-1]=="🔳")
	  addMove(moves, i,j,i+dir,j-1);
	if(isOnBoard(i+dir, j+1) && board[i+dir][j+1]=="🔳")
	  addMove(moves, i,j,i+dir,j+1);
	    
      }
      //For Kings
      if((player&&board[i][j]=="👑")||(!player&&board[i][j]=="🎩")){
	for(int di=-1; di<=1; di+=2){
	  for(int dj=-1; dj<=1; dj+=2){
	    if(isOnBoard(i+di,j+dj)&& board[i+di][j+dj]=="🔳")
	      addMove(moves, i,j,i+di,j+dj);

	    if(isOnBoard(i+2*di, j+2*dj)&&board[i+2*di][j+2*dj]=="🔳"){
	      if(!player&&(board[i+di][j+dj]=="💀"||board[i+di][j+dj]=="👑"))
		addCapture(captures, i,j,i+2*di,j+2*dj);
	      if(player&&(board[i+di][j+dj]=="🎩"||board[i+di][j+dj]=="🤡"))
		addCapture(captures, i,j,i+2*di,j+2*dj);
	    }
		 
	  }
	}
      }
	
    }

  }
    

  if(!captures.empty())
    return captures;

  return moves;
  
}


vector<string> gameManager(string (*board)[8], bool player, bool &gameEnded, bool &whiteWon){
  int nOfWhite = 0, nOfBlack = 0;
  vector<string> allPossibleMoves;
  allPossibleMoves = findAllPossibleMoves(board,player);
  



//check if game aleady ended
  for(int i=0; i<8;i++)
    for(int j=0; j<8; j++){
      if(board[i][j]=="💀"||board[i][j]=="👑")//white
	nOfWhite++;
      if(board[i][j]=="🤡"||board[i][j]=="🎩")//black
	nOfBlack++;
    }
  if(nOfWhite==0||nOfBlack==0||allPossibleMoves.empty()){
    if(nOfWhite==0 || (player && allPossibleMoves.empty()))
      whiteWon=false;
    else if(nOfBlack==0||(!player && allPossibleMoves.empty()))
      whiteWon=true;
    gameEnded = true;
    return allPossibleMoves;
  }

  return allPossibleMoves;
}

int elmosHeuristics(string (*board)[8], bool player, bool gameEnded, bool whiteWon){
  int score=0;
  int manValue=10;
  int kingValue=50;

  //raw pawn value + advancedments
  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      if(board[i][j]=="💀"){
	score+=(manValue+(7-i));
	if(j>1&&j<6)
	  score+=2;
      }
      else if(board[i][j]=="👑")
	score+=kingValue;
      
      else if(board[i][j]=="🤡"){
	score-=(manValue+i);
	if(j>1&&j<6)
	  score-=2;	
      }
      else if(board[i][j]=="🎩")
	score-=kingValue;

    }
  }

  //mobility
  vector<string> whiteMoves = gameManager(board, true, gameEnded, whiteWon);
  vector<string> blackMoves = gameManager(board, false, gameEnded, whiteWon);
  score += 3*whiteMoves.size();
  score -= 3*blackMoves.size();
    
  return score;
}

string elmo(string (*board)[8], bool elmoColor, vector<string> possibleMoves, bool gameEnded, bool whiteWon){
  string bestMove;
  //picking the righr one
  cout<<"\n Board value: "<<elmosHeuristics(board, elmoColor,gameEnded, whiteWon)<<endl;
  bestMove = possibleMoves.at(rand()%possibleMoves.size());
  return bestMove;

}
//White 1
//Black 0
int main(int argc, char** argv){

  //system("[Console]::OutputEncoding = [System.Text.Encoding]::UTF8"); //Windows UTF8 encoding
  
  std::string  board[8][8];
  vector<string> allPossibleMoves;
  string move="0";
  bool elmoColor = true; //bot checker color - white
  bool player = false; // Black on move
  bool gameEnded = false;
  bool GUIMode = true;
  bool whiteWon = true;

  srand(static_cast<unsigned int>(time(0)));

  
  initBoard(board);
  
  if((string)argv[1] == "NET")
    GUIMode = false;
  if((string)argv[2] == "BLACK")
    elmoColor = false;
  
  while(!gameEnded){

 
    
    if(GUIMode)
      showBoard(board);

    allPossibleMoves = gameManager(board, player, gameEnded, whiteWon);
    if(gameEnded){
      if(whiteWon)
	cout<<"White won"<<endl;
      else if(!whiteWon)
	cout<<"BLack won"<<endl;
      return 0;
    }
    if(allPossibleMoves.size()!=0){
      for(int i=0; i<(int)allPossibleMoves.size(); i++)
	cout<<allPossibleMoves.at(i)<<"\t";
      
      cout<<endl;
    }
    else
      cout<<"\n no mnoves :(";


    if(elmoColor == player)
      move=elmo(board,elmoColor,allPossibleMoves, gameEnded, whiteWon);
    else
      //cin>>move;
      move=elmo(board,elmoColor,allPossibleMoves, gameEnded, whiteWon);




    
    update(board,move,player);
    cin>>move;
    player = !player;

  }
  
}
