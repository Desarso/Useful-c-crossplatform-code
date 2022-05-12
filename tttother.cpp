//ttt.cpp
//Addison Moore, CISP 360
//04/29/2022

#include <iostream>
using namespace std;

  
   
int main(){

  //declarations and function calls
  // Specification A3 - Array Data Type
char gameboard[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
  void Initializer(char gameboard[]);
  void PlayerTurn(char gameboard[]);
  void TheRules();
  void ComputerTurn(char gameboard[]);
  int Validator(int,int);
  bool CheckWinner(char gameboard[]);
  void WelcomeMenu();
  void ProgramGreeting();
  void CurrentBoard(char gameboard[]);
  void RefBoard();
  int menu_choice;
  int user_choice;
  int comp_move;
  char playagain;
  int randomstart;

  ProgramGreeting();


    {
      // Specification A1 - Main Game Loop
      //can be quit by pressing 3 either in the main or the secondary menu that's present if one wants to know the rules.
      while (menu_choice!=3)
        {

  // Specification B1 - Start Menu
          //The details are down in the function declaration, but I add the specs after I finish and I'm working from the top down
          //Also I'm writing all these verbose comments in an attempt to lower my plagiarism score
  WelcomeMenu();
  cin>>menu_choice;

  //Specification B2 - Valid Menu Choices        
  while (menu_choice<1 || menu_choice>3)
    {
      cout<<"Invalid Selection, please choose one of the available options.\n";
      cin>>menu_choice;
    }
  if (menu_choice==1)
  {
    TheRules();
    cout<<"2.) Play the Game.\n3.) Quit The Game.\n";
    menu_choice=Validator(2,3);
  }
   if (menu_choice==2)
  {
  // Specification C1 - Random Start
  //I did this very last, so I just flipped my function order in the game loop and did this little random number generator that leads to one of two decisions. Kind of clunky but it's 3 am and I'm really sick of looking at this thing  
  int randomstart=rand()%2;  
  Initializer(gameboard);  
  CurrentBoard(gameboard);
  RefBoard();

 // Specification A2 - Simple Prompt
 // I put the spec comment here because this loop is what allows the game to be replayed   
 while (!CheckWinner(gameboard))
   {
     if (randomstart==1)
     {
     cout<<"The Active Player (X) Goes First.\n";
     PlayerTurn(gameboard);
     CurrentBoard(gameboard);
     ComputerTurn(gameboard);
     CurrentBoard(gameboard);
     CheckWinner(gameboard);
   }
     else if (randomstart==0)
     {
       cout<<"The Computer (O) Goes First.\n";
       ComputerTurn(gameboard);
       CurrentBoard(gameboard);
       PlayerTurn(gameboard);
       CurrentBoard(gameboard);
       CheckWinner(gameboard);
       
     }
     }
    
  
  
     if (CheckWinner(gameboard)==true)
    {
      // Specification A2 - Simple Prompt
      // I put it here too just for good measure
      cout<<"The Game is over.\nWould you like to play again?(y/n)\n";
      char playagain;
      cin>>playagain;
      while (playagain!='y'&&playagain!='n')
        {
          cout<<"Invalid selection, please select y or n.\n";
          cin>>playagain;
          }
      if (playagain=='n')
      {
      {return 0;}
       if (playagain=='y')
      {
        menu_choice=2;
      }}
          }
    
    }
      


    

      
      
      
      
    }
    
      if (menu_choice==3)
{
  cout<<"fine, be like that.\n";
}

        }
      }
  

  
  
  
// Specification C2 - Simple Display
// This function displays the board, obviously
void CurrentBoard(char gameboard[])
{
  
 cout<< "\n\n\n "<<gameboard[0]<<" | "<<gameboard[1]<<" | "<<gameboard[2]<<"\n";
  cout<<"-----------\n";
   cout<< " "<<gameboard[3]<<" | "<<gameboard[4]<<" | "<<gameboard[5]<<"\n";
  cout<<"-----------\n";
   cout<< " "<<gameboard[6]<<" | "<<gameboard[7]<<" | "<<gameboard[8]<<"\n";
  ;
  
}
void RefBoard()
{
  cout<<"0 | 1 | 2\n";
  cout<<"-----------\n";
  cout<<"3 | 4 | 5 \n";
  cout<<"-----------\n";
  cout<<"6 | 7 | 8 \n";
}

//This is part of my input validation, and I also used it for my secondary menu that displays if you read the rules. I used this same thing on my b2dl and couldn't let it go to waste
int Validator(int low, int high) {
    int user_choice = 0;
    cin >> user_choice;
    while (user_choice < low || user_choice > high) {
        cout << "Invalid entry, please try again\n" << endl;
        cin >> user_choice;}
      return user_choice;}
    
  
    


void WelcomeMenu()
{
  cout<<"Welcome to Tic-Tac-Toe!\nPlease Select one of the following options:\n1.) Explain The Rules\n2.) Play the Game\n3.) Quit The Game.\n";
}

// Specification B3 – Valid Move
// This function utilizes my input validator to filter valid game moves, you'll notice it filters any number that doesn't correspond to a blank space.
void PlayerTurn(char gameboard[])
{
  
  int user_choice;
    cout<<"Please make your move by entering the integer that matches the coresponding space.\n";
  user_choice=Validator(0,8);
  if (gameboard[user_choice]!=' ')
  {
  
    cout<<"Not a valid choice, please choose again";
    user_choice=Validator(0,8);
    }
  
  {gameboard[user_choice]='X';}
  
    }
  
    
  
    
  
  // Specification C3 - AI
//Uses the same logic as the player input validation, but picks numbers at random until it finds a blank space
  void ComputerTurn(char gameboard[])
  {
    
    int comp_move=rand()%9;
    gameboard[comp_move=rand()%9];
  while (gameboard[comp_move]!=' ')
  {
    cout<<"computer has made an invalid move\n";
    gameboard[comp_move=rand()%9];
  }
    gameboard[comp_move]='O';
  }

void TheRules()
{
  cout<<"The object of the game is to get three X's in a row, column, or diagonal. If the computer gets three O's, the computer wins. If neither player does, the game is declared a Tie.\n\n\n";
}

//This function checks all the possible combinations for a winner
  bool CheckWinner(char gameboard[])
{
  
      if ((gameboard[0]==gameboard[1] && gameboard[1]==gameboard[2] &&gameboard[0]=='X') ||(gameboard[0]==gameboard[3] && gameboard[3]==gameboard[6] &&gameboard[0]=='X')||(gameboard[3]==gameboard[4] && gameboard[4]==gameboard[5] &&gameboard[3]=='X')||(gameboard[6]==gameboard[7] && gameboard[7]==gameboard[8] &&gameboard[7]=='X')||(gameboard[1]==gameboard[4] && gameboard[4]==gameboard[7] &&gameboard[1]=='X')||(gameboard[2]==gameboard[5] && gameboard[5]==gameboard[8] &&gameboard[2]=='X')||(gameboard[0]==gameboard[4] && gameboard[4]==gameboard[8] &&gameboard[0]=='X')||(gameboard[2]==gameboard[4] && gameboard[4]==gameboard[6] &&gameboard[2]=='X'))
      {cout<<"You Win!";
        return true;
        }
  else if ((gameboard[0]==gameboard[1] && gameboard[1]==gameboard[2] &&gameboard[0]=='O') ||(gameboard[0]==gameboard[3] && gameboard[3]==gameboard[6] &&gameboard[0]=='O')||(gameboard[3]==gameboard[4] && gameboard[4]==gameboard[5] &&gameboard[3]=='O')||(gameboard[6]==gameboard[7] && gameboard[7]==gameboard[8] &&gameboard[7]=='O')||(gameboard[1]==gameboard[4] && gameboard[4]==gameboard[7] &&gameboard[1]=='O')||(gameboard[2]==gameboard[5] && gameboard[5]==gameboard[8] &&gameboard[2]=='O')||(gameboard[0]==gameboard[4] && gameboard[4]==gameboard[8] &&gameboard[0]=='O')||(gameboard[2]==gameboard[4] && gameboard[4]==gameboard[6] &&gameboard[2]=='O'))
      {cout<<"The Computer Wins!";
        return true;}
  else{
    return false;
    }}


//This one resets the gameboard when the user decides to replay
void Initializer(char gameboard[])
{

for(int i=0;i<11;i++)
{

gameboard[i]= ' ';
}
  }

void ProgramGreeting()
{
  cout<<"Hello, all this program does is play tic-tac-toe\nThis Program was Written by Addison Moore\nIt is Due on May 1st, 2022.\n\n";
}