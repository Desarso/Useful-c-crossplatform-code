// Specification C2 – Source File Header
//TicTacToe
// Gabriel Malek
// 4/27/2022

#include <iostream> 
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <thread>
#include<chrono>
#ifdef __MINGW32__ 
       #include <conio.h>
#endif
using namespace std;
//create construct called scores so that I can turn the string of winner into a score for minimax to use
struct scores{
  int Xscore;
  int Oscore;
  int tie;
//object constructor
scores(int O, int X, int tied){
  Xscore = X;
  Oscore = O;
  tie = tied;
}
//object method that turns the actual string into the values that go into the construct that I create later.
int resultValue(string x){
  if(x=="tie"){return tie;}
  if(x=="X"){return Xscore;}
  if(x=="0"){return Oscore;}
  return 0;
};
};



//function declarations
void greetingModule(bool& debugMode);
void initGame(vector<string> board, vector<string> options, bool gameComplete, string winner, int depth, bool debugMode, int searchTree);
string inputValidation(vector<string> validArray, string inputToOptions[9], bool& debugMode, vector<string>& options);
void computerInput(vector<string>& options, int depth, int& searchTree, bool& gameComplete, string& winner, bool& debugMode, vector<string> board);
int randomNumber();
void largeType(string);
int minmax(vector<string>& options,int depth,bool isMaximizing,int alpha,int beta,bool& gameComplete, string& winner, int& searchTree,bool& debugMod, int& dotAnimation);
string isGameOver(vector<string> options, bool& gameComplete, string& winner);
void finalMenu(string& winner);
void initializegame();
void startMenu(string extra);
char basicABC_SIV(char input, int size);
int isInputValid(string input);
void dotAnimationFunction(int& index);
string getStringInRawMode(int minSize, int maxSize);
void clear();
char getRawInput();





int main(){
  startMenu("");
  //here I reset all console settings to default

}

//basic start menu
// Specification B1 - Start Menu
void startMenu(string extra){
  clear();;
  char input;
  cout<<"\n";
  largeType("Main Menu");
  cout<<"\n";
  cout << "\nTic Tac Toe\nby Gabriel Malek\nMay 2, 2022\n\n";
 
  cout << "To get started please choose one of the following options, use esc to come back to main." << endl
       << endl
       << " A - Explain Game.\n"
       << " B - Start New Game.\n"
       << " C - Quit.\n";
  if(extra.size()>0){
    cout<<"\n\n";
    largeType("TIC TAC TOE");
  }
  cout<<"\n"<<extra;
   input=basicABC_SIV(input, 3);

  if (input == 65) {
   extra= "--A game in which two players seek in alternate turns to complete a row, a column, or a diagonal with either three O's or three X's drawn in the spaces of a grid of nine squares.\n";
     clear();;
    startMenu(extra);
  }
   if(input==66){
      initializegame();
 }
  if(input==67){
    clear();;
    cout<<"Program Ended.";
    exit(0);
  }
  if(input==27 && extra.size()==0){
    clear();;
    cout<<"Program Ended.";
    exit(0);
  }
  if(input==27 && extra.size()>0){
     clear();;
     extra="";
     startMenu(extra);
     exit(0);    }
};

void initializegame(){
  
  vector<string> board;
  vector<string> options;
  bool gameComplete;
  string winner;
  int depth=0;
  bool debugMode=false;
  int searchTree;
  clear();;
  greetingModule(debugMode);
  initGame(board, options, gameComplete, winner, depth, debugMode, searchTree);
}

void greetingModule(bool& debugMode){
  cout<<"\n";
  largeType("Welcome to");
  largeType("Tic Tac Toe.");
  cout << "\nBy Gabriel Malek\nMay 2, 2022\n\nTry to get three X's in a row.\n\nTo access debug mode type 'debugMode'\n\n";
}




void initGame(vector<string> board, vector<string> options, bool gameComplete, string winner, int depth, bool 
  debugMode, int searchTree){
  winner="tie";
  depth = 0;
  gameComplete = false;
  string input;
  searchTree=0;
  vector<string> validArray={};
  string inputToOptions[9]={"A1","B1","C1","A2","B2","C2","A3","B3","C3"};
  options={"-","-","-","-","-","-","-","-","-"};
  board={};
  // Specification C1 - Random Start
  // calls function to receive random number between 0-10
  int randomStart = randomNumber();
  
//Display the board
// Specification A3 - Array Data Type
 board={"\n\n        1","        2","        3\n"
    "            |","        |\n",
    "a       ",options[0],"   |","    ",options[3],"   |","    ",options[6],"   \n",
    "    ________|","________|","________\n"
   "            |","        |\n",
    "b       ",options[1],"   |","    ",options[4],"   |","    ",options[7],"   \n",
    "    ________|","________|","________\n",
       "            |","        |\n",
    "c       ",options[2],"   |","    ",options[5],"   |","    ",options[8],"   \n"};
  // Specification C2 - Simple Display
  for(int i=0;i<board.size();i++){
      cout<<board[i];
    };
  cout<<"\n";
  // if(randomStart>=5){ cout<<"\nThe Ai is starting as 0. Please wait. Thinking...";}
  //  cout.flush();

 //this if decides if the user or AI begin the game
  if(randomStart<5){
    cout << "\nYou are starting as X.\n";
    //This loop is the main game loop
    // Specification A1 - Main Game Loop
    //there are actually two loops depending on who starts first user or AI. There's prob a way to avoid that but this was good enough
    while(gameComplete==false){
      
  //Create valid input array for user
      validArray={};
      for(int i=0;i<options.size();i++){
        if(options[i]=="-"){validArray.push_back(options[i]);}
      }
  
    //User Input--------------------
      cout<<"\nYou are X and your opponent is 0 please enter a letter(column) and a number(row): ";
      inputValidation(validArray, inputToOptions, debugMode, options);
      if(isGameOver(options, gameComplete, winner)!="null"){
        gameComplete= true;
      }
    //User Input--------------------
     //AI Input--------------------
      if(gameComplete!=true){computerInput(options, depth, searchTree, gameComplete, winner, debugMode, board);}
      if(isGameOver(options, gameComplete, winner)!="null"){
        gameComplete= true;
      }
    //AI Input--------------------
   board={"\n\n        1","        2","        3\n"
    "            |","        |\n",
    "a       ",options[0],"   |","    ",options[3],"   |","    ",options[6],"   \n",
    "    ________|","________|","________\n"
   "            |","        |\n",
    "b       ",options[1],"   |","    ",options[4],"   |","    ",options[7],"   \n",
    "    ________|","________|","________\n",
       "            |","        |\n",
    "c       ",options[2],"   |","    ",options[5],"   |","    ",options[8],"   \n"};
      if(debugMode==false){clear();}
      greetingModule(debugMode);
       for(int i=0;i<board.size();i++){
        cout<<board[i];
      }
    }
  }else{
    //second main loop
     while(gameComplete==false){
  //Create valid input array for user
      validArray={};
  //AI Input--------------------
       
      if(gameComplete!=true){computerInput(options, depth, searchTree, gameComplete, winner, debugMode, board);}
      if(isGameOver(options, gameComplete, winner)!="null"){
        gameComplete= true;
      }
     board={"\n\n        1","        2","        3\n"
    "            |","        |\n",
    "a       ",options[0],"   |","    ",options[3],"   |","    ",options[6],"   \n",
    "    ________|","________|","________\n"
   "            |","        |\n",
    "b       ",options[1],"   |","    ",options[4],"   |","    ",options[7],"   \n",
    "    ________|","________|","________\n",
       "            |","        |\n",
    "c       ",options[2],"   |","    ",options[5],"   |","    ",options[8],"   \n"};
      if(debugMode==false){clear();;}
      greetingModule(debugMode);
     
       for(int i=0;i<board.size();i++){
        cout<<board[i];
      }
       if(randomStart<5){
           cout << "\nYou started as X.\n";
       }else{  cout << "\nThe Ai started as 0.\n";}
  //AI Input---------------
       
  //User Input-----------------
         cout<<"\nYou are X and your opponent is 0 please enter a letter(column) followed by a number(row): ";
       cout.flush();
      for(int i=0;i<options.size();i++){
        if(options[i]=="-"){validArray.push_back(options[i]);}
      }
      if(gameComplete!=true){inputValidation(validArray, inputToOptions, debugMode, options);}
      if(isGameOver(options, gameComplete, winner)!="null"){
        gameComplete= true;
      }
  //User Input----------------
 

    }
  }
    
  //calls final menu once game finishes
         board={"\n\n        1","        2","        3\n"
    "            |","        |\n",
    "a       ",options[0],"   |","    ",options[3],"   |","    ",options[6],"   \n",
    "    ________|","________|","________\n"
   "            |","        |\n",
    "b       ",options[1],"   |","    ",options[4],"   |","    ",options[7],"   \n",
    "    ________|","________|","________\n",
       "            |","        |\n",
    "c       ",options[2],"   |","    ",options[5],"   |","    ",options[8],"   \n"};
      if(debugMode==false){clear();;}
      greetingModule(debugMode);
     
       for(int i=0;i<board.size();i++){
        cout<<board[i];
      }
       if(randomStart<5){
           cout << "\nYou started as X.\n";
       }else{  cout << "\nThe Ai started as 0.\n";}
  finalMenu(winner);
   
}

// Specification B3 – Valid Move
// input validation makes sure that the input is valid, and avoids inputting into taken spaces.
string inputValidation(vector<string> validArray, string inputToOptions[9], bool& debugMode, vector<string>& options ){
  string input;
  int letterPosition;
  bool inputReceived=false;
  while(inputReceived==false){
    input= getStringInRawMode(2,2);
    //Added debug mode because it was useful and because it was cool seeing the program running thru the entire possibility tree. 
    if(input=="exit()"){exit(0);}
    if(input=="debugMode"&&debugMode==false){debugMode=true;cout<<"\n\nDEBUG MODE ON.\n\n(WARNING! debug mode will display the search tree and make the program much slower\nThe first AI move will have thousands of recursion calls and the console is never cleared.\n\nEnter input: ";
      }else if(input=="debugMode"&&debugMode==true){debugMode=false;cout<<"\n\nDEBUG MODE OFF.\n\nEnter input: ";}
    string holder;
    if(input!="debugMode"&&input!="exit()"){
        letterPosition=isInputValid(input);
        // cout<<"Letter Position: "<<letterPosition<<"\n";
        // cout<<"Input size: "<<input.size()<<"\n";
        holder=toupper(input[letterPosition-1]);
        if(letterPosition==1){
           input = holder+input.substr(1,1);
        }else if(letterPosition==2){
           input = holder+input.substr(0,1);
        }
       // cout<<"Input is: "<<input<<"\n";
       // cout<<"Size: "<<input.size();
        if(input.size()==2&&(input[0]=='A'||input[0]=='B'||input[0]=='C')&&(input[1]=='1'||input[1]=='2'||input[1]=='3')){
            for(int i=0;i<9;i++){
          if(options[i]=="-"&&input==inputToOptions[i]){
            options[i]="X";
            inputReceived=true;
            }}if(inputReceived==false){cout<<"\nInvalid input please try again: ";}
          
        }else{cout<<"\nInvalid input please try again: ";}
      
    }
        
      
  }
   return "-";
};


int isInputValid(string input){
  bool inputValid;
  bool isFirstLetter=false;
  // cout<< "input[0] number is: "<<input[0]-0<<"\n";
  // cout<<"Input[1] number is: "<<input[1]-0;
  if(input.size()==2){
    if(((input[0]-0>=65&&input[0]-0<=67)|| 
        (input[0]-0>=97&&input[0]-0<=99))&&input[1]-0>=49&&input[1]-0<=51){
      isFirstLetter=true;
      inputValid=true;
      return 1;
    }else if(((input[1]-0>=65&&input[1]-0<=67)||
              (input[1]-0>=97&&input[1]-0<=99))&&input[0]-0>=49&&input[0]-0<=51){
      isFirstLetter=false;
      inputValid=true;
      return 2;
    }else{return 0;}
  }else{return 0;}
};

string getStringInRawMode(int minSize, int maxSize){
      string input="";
      // cout<<input.size();
      int rawInput;
      bool inputReceived=false;
    while(inputReceived==false) {

        rawInput = getRawInput();
      //I output rawInput becuase I need to echo manually
        cout<< char(rawInput);
        // cout<<"\nRaw Input: "<<rawInput;
    
      //console checks to see if I pressed anything but the esc or enter key.
        if(rawInput != 10 && rawInput!= 27 && rawInput != 127 && rawInput!=13){
          
          input=input+char(rawInput);
          // cout<<input.size();
          }
     //if esc is pressed the program ends.
        if(rawInput == 27) {
    //cleared the console and end the program.
           // cout<< "I pressed esc;";
          startMenu("");
          exit(0);
        } 
      if(rawInput == 13) {
    //if space bar is pressed start a new game
         cout<<"\b \b";
         inputReceived=true;
         // cout<<"\nMy input was: "<<input;
        cout<<"\n";
        //here I reset all console settings to default
         return input;
        } 
      if(rawInput == 127){
       
        // cout<< "input is: |"<< input;
        // cout<<"size: "<<input.size();

      
        if(input.size()>0){
           cout<<"\b \b";
        }
        // if(input.size()==0){
        //   cout<<"\b \b";
        // }
        if(input.size()&&input.size()!=0){input = input.substr(0,input.size()-1);}
      }
    }
  //here I reset all console settings to default
  
  return "";
};
 
// Specification C3 - AI
// this is the module that calls the minimax module, it handles the root of the tree, and returns the best move to the module with the main game loop.
void computerInput(vector<string>& options, int depth, int& searchTree, bool& gameComplete, string& winner, bool& debugMode, vector<string> board){
  bool choiceMade = false;
  int score;
  int bestScore = -1;
  int bestMoveIndex;
  int dotAnimation =0;
  //Is the spot available?
  //checks to see possible moves
  for(int i=0;i<options.size();i++){
    if(options[i]=="-"){
      //in here we change the reference variable that represents the board state, we must immediatly change it back after checking the move with minimax
      options[i]="0";
      depth = 0;
      searchTree=0;
      int alpha=-1;
      int beta=1;
      //finds one possible move and send it to minimax which ten recursively checks every possible move and gives the original move a score.
     score = minmax(options,depth,false, alpha, beta, gameComplete, winner, searchTree, debugMode, dotAnimation);
      // here we change the options variable back to it's original state
      options[i]="-";
      //this if statement keeps track of the best move, and it's corresponding index in the options variable.
     if(score > bestScore){
       bestScore =score;
       bestMoveIndex = i;
     }
    }
  }
  //once we find the best move we execute it by saving it to the reference variable options which get displayed later in the main game loop.
  options[bestMoveIndex]="0";
}

//function generate random number in between the max and min value.
int randomNumber(){
  const int MIN_VALUE=1;
  const int MAX_VALUE=10;
  unsigned seed;
  //we use a seed to get different values
  //the seed is taken from time function so that each time the program runs the seed is different.
    seed=time(0);
    srand(seed);
  return (rand()%(MAX_VALUE-MIN_VALUE+1))+MIN_VALUE;
}


//large type is a simple function but very tedious to write, I wanted to be able to use an Ascii font, looking back I might have choosen a different font, but it's too late to change it. Would be cool to write a program in javascript that takes Ascci fonts and then outputs a c++ module, I'm sure there are a many external libraries too.
void largeType(string input){
  //first layer
  for(int i=0;i<input.size();i++){
    if(input[i]=='A'){cout <<" /\\ ";}
    if(input[i]=='B'){cout<<"|~)";}
    if(input[i]=='C'){cout<<"/~`";}
    if(input[i]=='D'){cout<<"|~\\";}
    if(input[i]=='E'){cout<<"(~";}
    if(input[i]=='F'){cout<<"|~";}
    if(input[i]=='G'){cout<<"/~_";}
    if(input[i]=='H'){cout<<"|_|";}
    if(input[i]=='I'){cout<<"~|~";}
    if(input[i]=='J'){cout<<"~|~";}
    if(input[i]=='K'){cout<<"|/";}
    if(input[i]=='L'){cout<<"| ";}
    if(input[i]=='M'){cout<<"|\\/|";}
    if(input[i]=='N'){cout<<"|\\ |";}
    if(input[i]=='O'){cout<<"/~\\";}
    if(input[i]=='P'){cout<<"|~)";}
    if(input[i]=='Q'){cout<<"/~\\";}
    if(input[i]=='R'){cout<<"|~)";}
    if(input[i]=='S'){cout<<"(~";}
    if(input[i]=='T'){cout<<"~|~";}
    if(input[i]=='U'){cout<<"| |";}
    if(input[i]=='V'){cout<<"\\  /";}
    if(input[i]=='W'){cout<<"\\    /";}
    if(input[i]=='X'){cout<<"\\/";}
    if(input[i]=='Y'){cout<<"\\ /";}
    if(input[i]=='Z'){cout<<"~/";}
    if(input[i]=='a'){cout<<" _ ";}
    if(input[i]=='b'){cout<<"|_ ";}
    if(input[i]=='c'){cout<<" _";}
    if(input[i]=='d'){cout<<" _|";}
    if(input[i]=='e'){cout<<" _ ";}
    if(input[i]=='f'){cout<<" |`";}
    if(input[i]=='g'){cout<<" _ ";}
    if(input[i]=='h'){cout<<"|_ ";}
    if(input[i]=='i'){cout<<".";}
    if(input[i]=='j'){cout<<" .";}
    if(input[i]=='k'){cout<<"| ";}
    if(input[i]=='l'){cout<<"|";}
    if(input[i]=='m'){cout<<" _ _ ";}
    if(input[i]=='n'){cout<<" _ ";}
    if(input[i]=='o'){cout<<" _ ";}
    if(input[i]=='p'){cout<<" _ ";}
    if(input[i]=='q'){cout<<" _  ";}
    if(input[i]=='r'){cout<<" _";}
    if(input[i]=='s'){cout<<" _";}
    if(input[i]=='t'){cout<<"_|_";}
    if(input[i]=='u'){cout<<"   ";}
    if(input[i]=='v'){cout<<"  ";}
    if(input[i]=='w'){cout<<"\\    /";}
    if(input[i]=='x'){cout<<"  ";}
    if(input[i]=='y'){cout<<"  ";}
    if(input[i]=='z'){cout<<"_ ";}
    if(input[i]==32){cout<<"  ";}
      }
  //second layer
  cout<< "\n";
for(int i=0;i<input.size();i++){
    if(input[i]=='A'){cout <<"/~~\\";}
    if(input[i]=='B'){cout<<"|_)";}
    if(input[i]=='C'){cout<<"\\_,";}
    if(input[i]=='D'){cout<<"|_/";}
    if(input[i]=='E'){cout<<"(_";}
    if(input[i]=='F'){cout<<"|~";}
    if(input[i]=='G'){cout<<"\\_/";}
    if(input[i]=='H'){cout<<"| |";}
    if(input[i]=='I'){cout<<"_|_";}
    if(input[i]=='J'){cout<<"L| ";}
    if(input[i]=='K'){cout<<"|\\";}
    if(input[i]=='L'){cout<<"|_";}
    if(input[i]=='M'){cout<<"|  |";}
    if(input[i]=='N'){cout<<"| \\|";}
    if(input[i]=='O'){cout<<"\\_/";}
    if(input[i]=='P'){cout<<"|~ ";}
    if(input[i]=='Q'){cout<<"\\_X";}
    if(input[i]=='R'){cout<<"|~\\";}
    if(input[i]=='S'){cout<<"_)";}
    if(input[i]=='T'){cout<<" | ";}
    if(input[i]=='U'){cout<<"|_|";}
    if(input[i]=='V'){cout<<" \\/ ";}
    if(input[i]=='W'){cout<<" \\/\\/ ";}
    if(input[i]=='X'){cout<<"/\\";}
    if(input[i]=='Y'){cout<<" | ";}
    if(input[i]=='Z'){cout<<"/_";}
    if(input[i]=='a'){cout<<"(_|";}
    if(input[i]=='b'){cout<<"|_)";}
    if(input[i]=='c'){cout<<"(_";}
    if(input[i]=='d'){cout<<"(_|";}
    if(input[i]=='e'){cout<<"(/_";}
    if(input[i]=='f'){cout<<"~|~";}
    if(input[i]=='g'){cout<<"(_|";}
    if(input[i]=='h'){cout<<"| |";}
    if(input[i]=='i'){cout<<"|";}
    if(input[i]=='j'){cout<<" |";}
    if(input[i]=='k'){cout<<"|<";}
    if(input[i]=='l'){cout<<"|";}
    if(input[i]=='m'){cout<<"| | |";}
    if(input[i]=='n'){cout<<"| |";}
    if(input[i]=='o'){cout<<"(_)";}
    if(input[i]=='p'){cout<<"|_)";}
    if(input[i]=='q'){cout<<"(_| ";}
    if(input[i]=='r'){cout<<"| ";}
    if(input[i]=='s'){cout<<"_\\";}
    if(input[i]=='t'){cout<<" | ";}
    if(input[i]=='u'){cout<<"|_|";}
    if(input[i]=='v'){cout<<"\\/";}
    if(input[i]=='w'){cout<<" \\/\\/ ";}
    if(input[i]=='x'){cout<<"><";}
    if(input[i]=='y'){cout<<"\\/";}
    if(input[i]=='z'){cout<<"/_";}
    if(input[i]==32){cout<<"  ";}
      }
  //third layer
   cout<< "\n";
for(int i=0;i<input.size();i++){
    if(input[i]=='A'){cout <<"    ";}
    if(input[i]=='B'){cout<<"   ";}
    if(input[i]=='C'){cout<<"   ";}
    if(input[i]=='D'){cout<<"   ";}
    if(input[i]=='E'){cout<<"   ";}
    if(input[i]=='F'){cout<<"  ";}
    if(input[i]=='G'){cout<<"   ";}
    if(input[i]=='H'){cout<<"   ";}
    if(input[i]=='I'){cout<<"   ";}
    if(input[i]=='J'){cout<<"   ";}
    if(input[i]=='K'){cout<<"  ";}
    if(input[i]=='L'){cout<<"  ";}
    if(input[i]=='M'){cout<<"    ";}
    if(input[i]=='N'){cout<<"    ";}
    if(input[i]=='O'){cout<<"   ";}
    if(input[i]=='P'){cout<<"   ";}
    if(input[i]=='Q'){cout<<"   ";}
    if(input[i]=='R'){cout<<"   ";}
    if(input[i]=='S'){cout<<"  ";}
    if(input[i]=='T'){cout<<"   ";}
    if(input[i]=='U'){cout<<"   ";}
    if(input[i]=='V'){cout<<"    ";}
    if(input[i]=='W'){cout<<"      ";}
    if(input[i]=='X'){cout<<"  ";}
    if(input[i]=='Y'){cout<<"   ";}
    if(input[i]=='Z'){cout<<"  ";}
    if(input[i]=='a'){cout<<"   ";}
    if(input[i]=='b'){cout<<"   ";}
    if(input[i]=='c'){cout<<"  ";}
    if(input[i]=='d'){cout<<"   ";}
    if(input[i]=='e'){cout<<"   ";}
    if(input[i]=='f'){cout<<"   ";}
    if(input[i]=='g'){cout<<" _|";}
    if(input[i]=='h'){cout<<"   ";}
    if(input[i]=='i'){cout<<" ";}
    if(input[i]=='j'){cout<<"L|";}
    if(input[i]=='k'){cout<<"  ";}
    if(input[i]=='l'){cout<<" ";}
    if(input[i]=='m'){cout<<"     ";}
    if(input[i]=='n'){cout<<"   ";}
    if(input[i]=='o'){cout<<"   ";}
    if(input[i]=='p'){cout<<"|  ";}
    if(input[i]=='q'){cout<<"  |/";}
    if(input[i]=='r'){cout<<"  ";}
    if(input[i]=='s'){cout<<"  ";}
    if(input[i]=='t'){cout<<"   ";}
    if(input[i]=='u'){cout<<"   ";}
    if(input[i]=='v'){cout<<"  ";}
    if(input[i]=='w'){cout<<"      ";}
    if(input[i]=='x'){cout<<"  ";}
    if(input[i]=='y'){cout<<"/ ";}
    if(input[i]=='z'){cout<<"  ";}
    if(input[i]==32){cout<<"  ";}
    if(input[i]=='\n'){cout<<"\n";}
      }
  cout << "\n";
}

//this function checks to see the game state and return a string with the winner, tie or null.
string isGameOver(vector<string> options, bool& gameComplete, string& winner){
  bool spotsEmpty=false;
 
  if(options[0]!="-"&&(options[0]==options[1]&&options[1]==options[2])){gameComplete=true;winner=options[0];return winner;}
  if(options[4]!="-"&&(options[3]==options[4]&&options[4]==options[5])){gameComplete=true;winner=options[4];return winner;}
  if(options[6]!="-"&&(options[6]==options[7]&&options[7]==options[8])){gameComplete=true;winner=options[6];return winner;}
  if(options[0]!="-"&&(options[0]==options[3]&&options[3]==options[6])){gameComplete=true;winner=options[0];return winner;}
  if(options[1]!="-"&&(options[1]==options[4]&&options[4]==options[7])){gameComplete=true;winner=options[1];return winner;}
  if(options[2]!="-"&&(options[2]==options[5]&&options[5]==options[8])){gameComplete=true;winner=options[2];return winner;}
  if(options[0]!="-"&&(options[0]==options[4]&&options[4]==options[8])){gameComplete=true;winner=options[0];return winner;}
  if(options[2]!="-"&&(options[2]==options[4]&&options[4]==options[6])){gameComplete=true;winner=options[2];return winner;}
  
  for(int i=0;i<options.size();i++){
    if(options[i]=="-"){spotsEmpty=true;return "null";}
  }
    return "tie";
}

// Specification A2 - Simple Prompt
// reused function to output final menu will add more comentary inside the function
void finalMenu(string& winner){
 int endInput;
  if(winner!="tie"){
     cout << "\n\nTHE WINNER IS: "<<winner<<"!"<<"\nPress space bar to play again, any key to go to main menu.";
  }else{
    cout<< "\nIt's a tie.\n\nPress space bar to play again, esc to end program or any other key to go to main menu.";
  }
   
   
    while(1) {
      //this line of code sets the console to raw mode which is a way to take input without needing a delimiter, like enter.
        
        endInput = getRawInput();
      // here the console is set back to cooked which is default.
    
      //console checks to see if I pressed anything but the esc or enter key.
        if(endInput != 10 && endInput!= 27 && endInput!= 32){
          clear();
          main();
          }
     //if esc is pressed the program ends.
        if(endInput == 27) {
    //cleared the console and end the program.
            clear();
            main();
        } 
        if(endInput == 32) {
      //if space bar is pressed start a new game
            clear();
            initializegame();
        } 
    }
}

// I used an object here because it made things easier, but there were probably faster ways to do this.
scores Scores=scores(1,-1,0);


// (options,depth,false, alpha, beta, gameComplete, winner, searchTree, debugMode, dotAnimation);

int minmax(vector<string>& options,int depth, bool isMaximizing,  int alpha, int beta,bool& gameComplete, string& winner, int& searchTree, bool& debugMode, int& dotAnimation){
  string result;
  int score;
  //minimax checks to see it's current recursion layer state, by calling isGameOver;
  result = isGameOver(options, gameComplete, winner);
  gameComplete=false;
  winner ="tie";
  searchTree++;
  depth++;
  if(debugMode==true){
  cout << "The depth is: "<<depth<<"\nRecursive calls: "<<searchTree;
  vector<string> board={"\n\n        1","        2","        C\n"
    "            |","        |\n",
    "a       ",options[0],"   |","    ",options[3],"   |","    ",options[6],"   \n",
    "    ________|","________|","________\n"
   "            |","        |\n",
    "b       ",options[1],"   |","    ",options[4],"   |","    ",options[7],"   \n",
    "    ________|","________|","________\n",
       "            |","        |\n",
    "c       ",options[2],"   |","    ",options[5],"   |","    ",options[8],"   \n"};
   for(int i=0;i<board.size();i++){
      cout<<board[i];
    };
     cout <<"\nThe score for this board is: "<< result<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
  }
  if(searchTree%1500==0){
    dotAnimationFunction(dotAnimation);
    cout.flush();
  }
 

//if result is null meaning once the board is a terminal state, then it should record the score and send it back up.
  if(result !="null"){
    score = Scores.resultValue(result);
    return score;
  }
  //during the AI's turn the minmax function is trying to maximize the value of it's own move.
  if(isMaximizing){
    int bestScore = -1;
        for(int i=0;i<options.size();i++){
          if(options[i]=="-"){
            options[i]="0";
            //minimax calls itself recursively this time switching it's isMaximizing variable
            score = minmax(options,depth,false,alpha, beta, gameComplete, winner, searchTree, debugMode, dotAnimation);
            options[i]="-";
          bestScore=max(bestScore,score);
          alpha=max(alpha,score);
          if(beta<= alpha){
            break;
          }
       }
     }
    return bestScore; 
  //during the players turn minimax tries to find the move that minimizes their score. This code is repeated, but again it was good enough.
  }else{
     int bestScore = 1;
        for(int i=0;i<options.size();i++){
          if(options[i]=="-"){
            options[i]="X";
              //minimax calls itself recursively this time switching it's isMaximizing variable
            score = minmax(options,depth,true, alpha, beta, gameComplete, winner, searchTree, debugMode, dotAnimation);
            options[i]="-";
          bestScore=min(bestScore,score);
          beta = min(beta, score);
          if(beta<=alpha){
            break;
          }
       }
     }
    return bestScore; 
  }
  }

//Specification B2 
//basic function to make single input validation for multiple choice menus easier.
char basicABC_SIV(char input, int size) {
  int i = 0;
  vector<char> valid_array;
  //loops takes the size variable and creates a valid array of char letters in alphabetical order.
  for (int i = 0; i < size; i++) {
    valid_array.push_back(65 + i);
  }
  valid_array.push_back(27);//add esc to the array to allow the use of esc key.
  while (i < 2) {
    //get input while in raw mode then make it uppercase and compare against valid array.
    input = getRawInput();
    int intInput = input - '0';
    input = toupper(input);
    cout << " " << '\n';
    //check for empty input, then compare against array, and return or output an error message while in the loop.
    if (!(input)) {
      cout << "Incorrect input. Please try again.\n";
      cin.clear();
      while (cin.get() != '\n')
        ;
    }
    
    bool correctInput = false;
    for (int j = 0; j < size+1; j++) {
      if (input == valid_array[j]) {
        correctInput = true;
        return input;
        i = 2;
      }
    }
    //error message outputs the correct inputs.
    if (correctInput == false) {
      cout << "Err, only enter " << valid_array[0];
      for (int j = 1; j < size; j++) {
        cout << " or " << valid_array[j];
      }
      cout << "." << endl;
    }
  }
  return 0;
}


//I decided to add a loading animation, the cout makes the program slower, but I thought it was worth it, I would like to add prunning to the minimax function to make it faster, but maybe for another time.

void dotAnimationFunction(int& index){
  index++;
  string output="\rThe Ai is starting as 0. Please wait. Thinking";
  const int SIZE=55;
  if(index>SIZE-48){index=0;}
  for(int i=0;i<index;i++){
    output=output+".";
  }
  while(output.size()<SIZE){
      output=output+" ";
  }
  this_thread::sleep_for(chrono::milliseconds(50));
  cout<<output;
  cout.flush();
  
}



void clear(){
    #ifdef __MINGW32__ 
        system("CLS");
    #endif
    #ifdef __linux__
        system("clear");
    #endif
 
};
char getRawInput(){
     #ifdef __MINGW32__ 
        return _getch();
    #endif
    #ifdef __linux__
        int rawInput;
        system("stty -echo");
        system("stty raw");
        rawInput = getchar();
        system("stty cooked");
        system("stty sane");
        return rawInput;
    #endif
};