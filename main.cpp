#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdlib.h>
#include <algorithm>


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSPACE 1024

int errno;




//White 💀
//Black 🤡
//White_King 👑	
//Black_King 🎩
using namespace std;
int elmosHeuristics(string (*board)[8], bool player, bool gameEnded, bool whiteWon);
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
  //cout<<endl;
  
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

      //cout<<endl<<"olda: "<<olda<<"   a: "<<a<<" player: "<<player<<endl;
      if(!player&&a-olda>1){
	a--;b=b+(oldb-b)/2;;
	if((olda+oldb)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
      if(!player&&olda-a>1){
	a++;b=b+(oldb-b)/2; 
	if((olda+oldb)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
      if(player&&olda-a>1){
	a++;b=b+(oldb-b)/2; 
	if((a+b)%2==0)
	  board[a][b] = "🔲";
	else
	  board[a][b] = "🔳";
      }
      if(player&&a-olda>1){
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
  string copiedBoard[8][8];
  if(player)
    dir = -1; //if white is on move


  for(int i=0; i<8; i++){
    for(int j=0; j<8; j++){
      copiedBoard[i][j]=board[i][j];
    }
  }

  
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
  
  if(!captures.empty()){
    for(int i=0; i<(int)captures.size(); i++){
      update(copiedBoard, captures.at(i), player);
      vector<string> newCaptures = findAllPossibleMoves(copiedBoard, player);
      for(int j=0; j<(int)newCaptures.size(); j++){
	if(newCaptures.at(j).find('x')!=std::string::npos){
	size_t posA = captures.at(i).find('x');
	size_t posB = newCaptures.at(j).find('x');

	string numA = captures.at(i).substr(posA+1);
	string numB = newCaptures.at(j).substr(0,posB);

	int moveA, moveB;
	istringstream(numA) >> moveA;
	istringstream(numB) >> moveB;

	if(moveA == moveB){
	  newCaptures.at(j) = captures.at(i) + "x" + newCaptures.at(j).substr(posB+1);
	  // cout<<"Kolejny ruch dla: "<<captures.at(i)<<" to: "<<newCaptures.at(j)<<endl;
	  captures.at(i)=newCaptures.at(j);
	}
	}
	
      }

    }
    return captures;
  }
  return moves;
  
}

int minimax(string (*board)[8] ,int depth, int alpha, int beta, bool maximizingPlayer, bool player){
  string copiedBoard[8][8];
  vector<string> allPossibleMoves=findAllPossibleMoves(board,player);
  
  if(depth == 0)
    return elmosHeuristics(board, player, 0,0);


  for(int i=0; i<8; i++)
    for(int j=0; j<8; j++)
      copiedBoard[i][j]=board[i][j];
      
  
  if(maximizingPlayer){
    int maxEval = -10000000;
    for(int i=0; i<(int)allPossibleMoves.size(); i++){
      int eval = minimax(board, depth-1, alpha, beta, false, !player);
      maxEval = std::max(maxEval, eval);
      alpha = std::max(alpha, eval);
      if (beta<=alpha)
	break;
    }
      
    return maxEval;
  }
  else{
    int minEval = 10000000;
    for(int i=0; i<(int)allPossibleMoves.size(); i++){
      int eval = minimax(board, depth-1, alpha, beta, true, !player);
      minEval = std::min(minEval, eval);
      beta = std::min(beta, eval);
      if(beta<=alpha)
	break;
    }
    
    return minEval;
  }
  
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
	/*każdy pionek gracza białego otrzymuje tym więcej punktów im bliżej jest przeciwnego
	 końca planszy*/
	if(j>1&&j<6)
	  score+=2;
	/*Bonusowe punkty za trzymanie się poza brzegami planszy, ponieważ pion na brzegu
	 ma tylko jeden możliwy ruch*/
      }
      else if(board[i][j]=="👑")
	score+=kingValue;
      /*Bonusowe punkty za każdego króla*/


      
      else if(board[i][j]=="🤡"){
	score-=(manValue+i);
	if(j>1&&j<6)
	  score-=2;	
      }
      else if(board[i][j]=="🎩")
	score-=kingValue;
      /*To samo dla gracza czarnego, ale ten minimalizuje punkty*/
    }
  }

  //mobility
  vector<string> whiteMoves = gameManager(board, true, gameEnded, whiteWon);
  vector<string> blackMoves = gameManager(board, false, gameEnded, whiteWon);
  score += 2*whiteMoves.size();
  score -= 2*blackMoves.size();
  /*Mobilność - każdy gracz dostaje punkty jeżeli w danej turze ma dużo możliwości ruchu - 
   im więcej możliwych ruchów tym większa szansa, że któryś będzie dobry*/
  return score;
}

string elmo(string (*board)[8], bool elmoColor, vector<string> possibleMoves, int DEPTH){
  string bestMove;
  int bestMoveValue;
  if(elmoColor)
    bestMoveValue=-100000;
  else if(!elmoColor)
    bestMoveValue= 100000;
  int moveValue;

  for(int i=0; i<(int)possibleMoves.size(); i++){
    moveValue = minimax(board, DEPTH, -1000000, 1000000,true,elmoColor);

    if(elmoColor){
      if(moveValue>bestMoveValue){
	bestMoveValue=moveValue;
	bestMove = possibleMoves.at(i);
      }
    }
    else{
      if(moveValue<bestMoveValue){
	bestMoveValue = moveValue;
	bestMove = possibleMoves.at(i);
      }
    }
		  
    }

  return bestMove;//=possibleMoves.at(rand()%possibleMoves.size());

}
//White 1
//Black 0
int main(int argc, char** argv){

  //system("[Console]::OutputEncoding = [System.Text.Encoding]::UTF8"); //Windows UTF8 encoding


  char buf[BUFSPACE];
  int serv_sock, n, nr_ruchu;
  struct sockaddr_in serv_addr;
  struct hostent *serv_hostent;







  
  std::string  board[8][8];
  vector<string> allPossibleMoves;
  string move="0";
  int MAXDEPTH = stoi(argv[3]);
  bool elmoColor = true; //bot checker color - white
  bool player = false; // Black on move
  bool gameEnded = false;
  bool GUIMode = true;
  bool whiteWon = true;

  if(argc==5||argc==7){
    int seed = stoi(argv[4]);
    srand(static_cast<unsigned int>(seed));
  }
  else
    srand(static_cast<unsigned int>(time(0)));

  
  
  initBoard(board);
  
  if((string)argv[1] == "NET")
    GUIMode = false;
  if((string)argv[2] == "BLACK")
    elmoColor = false;

  serv_sock = socket(AF_INET, SOCK_STREAM, 0);
  if(!GUIMode){
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock < 0) {
      perror("socket");
      exit(errno);
    }
    serv_hostent = gethostbyname("localhost");
    if(argc==7)    
      serv_hostent = gethostbyname(argv[5]);
    else if(argc==6)
      serv_hostent = gethostbyname(argv[4]);
    if (serv_hostent == 0) {
      //  fprintf(stderr, "%s: nieznany adres IP %s\n", argv[0], argv[5]);
      exit(-1);
    }
    serv_addr.sin_family = AF_INET;
    memcpy(&serv_addr.sin_addr, serv_hostent->h_addr, serv_hostent->h_length);
    if(argc==7)
      serv_addr.sin_port = htons(atoi(argv[6]));
    else if(argc==6)
      serv_addr.sin_port = htons(atoi(argv[5]));
    
    // printf("Laczymy sie z serwerem ...\n");
    if (connect(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("connect");
      exit(-1);
    }
    
    //printf("Polaczenie nawiazane, zaczynamy gre ...\n");
    
    
  }
  nr_ruchu = 0;				/* czarny robi ruchy parzyste */
  if (elmoColor) nr_ruchu = 0;	/* bialy nieparzyste */
  while(!gameEnded){

    if(GUIMode){
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
	move=elmo(board,player,allPossibleMoves,MAXDEPTH);
      else
	cin>>move;



      update(board,move,player);
      player = !player;

    }
    else{//NET
      
      allPossibleMoves = gameManager(board, player, gameEnded, whiteWon);
      if(elmoColor == player){
	move=elmo(board,elmoColor,allPossibleMoves,MAXDEPTH);
	//	printf("Wysylam do serwera moj ruch: %s\n", move.c_str());
	if (write(serv_sock, move.c_str(), strlen(move.c_str())) < 0){
	  perror("write");
	  exit(errno);
	}
	update(board,move,player);
	player =! player;
      }
      //  printf("Czekam na ruch przeciwnika ...\n");
      n=read(serv_sock, buf, sizeof buf);
      if (n<0) {
	perror("read");
	exit(errno);
      }
      if (n==0) { /* pusty komunikat = zamkniete polaczenie */
	//	printf("Broker zamknal polaczenie, hmmmm...\n");
	exit(0);
      }
      buf[n] = 0;
      // printf("Otrzymalem ruch przeciwnika: %s", buf);
      if (buf[n-1]!='\n'); //printf("\n");
      
      ++nr_ruchu;
      string moveServer(buf);
      update(board,moveServer,player);
      player = !player;	
    }
  }
}
      
