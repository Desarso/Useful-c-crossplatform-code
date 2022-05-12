// Final Project;
// Gabriel Malek
// 5/12/2022

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
//I use a windows prepocessor so that I can edit my code on my laptop and it uses a .h library but it doesn't utilize the library unless it's on windows.
#ifdef __MINGW32__ 
       #include <conio.h>
#endif

using std::cout;
using std::string;
using std::vector;
using std::fstream;

//I want the dungeon game to use verbs ans stuff, so I'm thinking that the rooms can have verbs
//and then the monsters can also have verbs, and stuff
//Possible verbs for room:
//look around,
const string DEFAULT_FILE_NAME="data.dat";
const string out="out";
const string app="app";
void largeType(string input);

struct item{
  string name;
  string description;
  vector<item> subObjects;
  item(string n, string desc){
    name=n;
    description=desc;
  }
  item(string n, string desc, vector<item> sub){
   name=n;
   description=desc;
   subObjects=sub;
}
void displayItemData(){
    cout<<"\nItem Name: "<<name<<"\n"
    <<"Item Desc: "<<description<<"\n"
    <<"SubItem: "<<"\n";
    for(int i=0; i<subObjects.size();i++){
      cout<<"  subItem Name: "<<subObjects[i].name<<"\n"
        <<"  Desc: "<<subObjects[i].description<<"\n\n";
    };

  }

};
struct room{
  string room_name, room_description;
  int room_id;
  bool occupied=false;
  int  N,S,E,W;
  bool descriptionRead=false;
  bool monsterSpawn=false;
  bool monsterKilled=false;
  room(string name, string desc, int id, int n, int s, int e, int w){
    room_name=name;
    room_description=desc;
    room_id=id;
    N=n;
    S=s;
    E=e;
    W=w;
   

  }

  int getNextRoomId(string cords){
       if(cords=="N"||cords=="n"){return N;}
       if(cords=="E"||cords=="E"){return E;}
       if(cords=="S"||cords=="S"){return S;}
       if(cords=="W"||cords=="W"){return W;}
    return 0;
   }
   
   int getCurrentRoomId(){
       return room_id;
   }

  void displayRoomName(){
      largeType(room_name);
  }
  void toggleDescriptionRead(bool t){
      descriptionRead=t;
  }

  string getName(){
    return room_name;  
  }

  void displayDescription(){
    cout<<room_description<<"\n\n";
    descriptionRead=true;
  }

  void displayRoomData(){
    cout<<"\n\nRoom Name: "<<room_name<<"\n"
     <<"Room ID: "<<room_id<<"\n"
     <<"N: "<<N<<", S: "<<S<<", E: "<<E<<", W: "<<W<<"\n\n";
  }
  void toggleMonsterSpawn(bool t){
      monsterSpawn=t;
  }
  void toggleMonsterKilled(bool t){
      monsterKilled=t;
  }

};
class game{
 
  
public:
    vector<room> rooms;
  string name; 
  vector<item> items; 
  game(string n, vector<room> r, vector<item> i){
    name=n;
    rooms=r;
    items=i;
  }
  room getRoomByID(int ID);
  game fetchData();
  void writeData(string mode);
  void displayAllGameData();
  vector<item> getItems();
  void getItemsDescByName(string Nam); 
};
//this function serializes the game object data to an external file
void game::writeData(string mode){
  const string myName= "data.dat";
  const string end="~";
  
  fstream myFile;
  if(mode=="app"){myFile.open(DEFAULT_FILE_NAME, std::ios::app);}
  if(mode=="out"){myFile.open(DEFAULT_FILE_NAME,std::ios::out);}
   if (myFile.is_open()){
     myFile<<"`A Dark Cave`~";
     for(int i=0;i<rooms.size();i++){
       myFile<<"$"<<rooms[i].room_name<<end
       <<rooms[i].room_id<<end
       <<rooms[i].room_description<<end
       <<rooms[i].N<<"|"<<rooms[i].S<<"|"<<rooms[i].E<<"|"<<rooms[i].W<<end;
     }
     for(int i=0;i<items.size();i++){
       myFile<<"%"<<items[i].name<<end
       <<items[i].description<<end;
       for(int j=0;j<items[i].subObjects.size();j++){
         myFile<<"*"<<items[i].subObjects[j].name<<end
         <<items[i].subObjects[j].description<<end;
       }
     }
     myFile.close();
   }
  
}
//this horribly function deserializes the object data, it's all by hand, I'm sure there's better ways to do this, but I couldn't find any built in short libraries.
game game::fetchData(){
   fstream fileRead;
   string line;
   int roomsIndex=0;
   int itemsIndex=0;
   int index =0;
   string roomName,roomDescription,itemName,itemDesc,subItemName, subItemDesc;
   int roomId;
   int N,S,W,E;
   vector<game> games={};
   vector<room> roomHelper={};
   vector<item> itemHelper={};
   vector<item> subItemsHelper={};
  
   
   int subObjectsIndex;
   fileRead.open(DEFAULT_FILE_NAME, std::ios::in);
   if(fileRead.is_open()){
     while(getline(fileRead, line,'~')){
        if(!line.size()){cout << "empty file";fileRead.close(); break;}
        if(line[0]=='`'){
          name=line.substr(1,line.size()-2);
          getline(fileRead, line,'~');
          index++;
          index=1;
            }//get game name
       
        if(line[0]=='$'){  
          roomName=line.substr(1,line.size());
          getline(fileRead, line,'~');
          index=1;
          if(index%3==1||index==1){
            roomId=stoi(line);
             getline(fileRead, line,'~');
             index++;
        }
          if(index%3==2||index==2){
            roomDescription=line;
            getline(fileRead, line,'~');
            index++;
          }
          if(index%3==0||index==3){
            N=stoi(line.substr(0,1));
            S=stoi(line.substr(2,3));
            E=stoi(line.substr(4,5));
            W=stoi(line.substr(6,7));
            roomHelper.push_back(room(roomName, roomDescription, roomId,N,S,E,W));
          }
          roomsIndex++;
          index=1;
         }//get rooms
    
        if(line[0]=='%'){
          index=1;
          if(index%2==1||index==1){
            itemName=line.substr(1,line.size());
            getline(fileRead, line,'~');
            index++;
        }//item name
          if(index%2==0||index==2){
            itemDesc=line.substr(1,line.size());
            getline(fileRead, line,'~');
            index++;
          }//item desc
          
          while(line[0]=='*'){
             subObjectsIndex=0;
             if(index%2==1||index==1){
            subItemName=line.substr(1,line.size());
            getline(fileRead, line,'~');
            index++;
        }
          if(index%2==0||index==2){
            subItemDesc=line.substr(1,line.size());
            getline(fileRead, line,'~');
            index++;
          }
            subItemsHelper.push_back(item(subItemName,subItemDesc));
            subObjectsIndex++;
          }//get sub items
          itemHelper.push_back(item(itemName, itemDesc, subItemsHelper));
          subItemsHelper={};
          itemsIndex++;
          index=1;
         }//get items and subItems
       
        index++;
      }
     games.push_back(game(roomName,roomHelper, itemHelper));
     fileRead.close();
     
   };
  return games[0];
}
room game::getRoomByID(int ID){
    return rooms[ID-1];
  }
void game::displayAllGameData(){
  cout<<"GAME NAME: "<<name<<"\n\n";
  for(int i=0;i<rooms.size();i++){
    rooms[i].displayRoomData();
  }
  for(int i=0;i<items.size();i++){
    items[i].displayItemData();
  }
}
vector<item> game::getItems(){
  return items;
};
void game::getItemsDescByName(string Nam){
    for(int i=0;i<items.size();i++){
        if(items[i].name==Nam){
            cout<<items[i].description;
        }
    }
}
//function declarations
void greetingModule();
void useUserInput(string input, int currentRoomID, game, vector<item>&, bool& validInput, bool& gunFound);
void help(string input);
void helperMessage();
string getStringInRawMode(int minSize, int maxSize);
char getRawInput();
// void spacer();
// void divider();
void mainGameLoop(int& currentRoomId, game& game, vector<item>& inventory, bool& validInput, bool& gunFound);


        
int main() {

  game game={"Death in the Dark",{room("Dark Cave",
                 "A small dark cave, smells faintly like sulfur, there is a dim candle attached to the wall. You can barely make out the smooth and damp texture of the walls, the room is earily silent.",
                1,
                2,0,0,0),room("Cave Room 2",
    "You run thru a corridor of stone, and make it to an opening with a small amount of faint light. You Panic as you realize the room is a small ledge with a large bottomless pit in the middle that you are currently running towards. You attempt to stop digging your heel into the ground, and your hurt leg sends shocks of agony thru your body, you fail to come to a complete stop, and just before you fall you manage to grab the ledge. You are now hanging from your left hand...'AHHHHH!' you yell as you dangle from one arm. Your strength catches you by surprise as you are able to easily hold yourself.",
  2,
  3,1,4,5)},{item("coat", "A heavy brown coat, keeps, you warm, also seem to have many pockets.",{item("gun","A small handheld pistol")})}};
 // game game={"",{},{}};
 // game = game.fetchData();
 // game.displayAllGameData();
  int currentRoomId=game.rooms[0].getCurrentRoomId();
  vector<item> inventory;
  inventory = game.items;

  ////main program code
  bool validInput=false;
  bool gunFound=false;
  bool singleGameThread=true;
  greetingModule();
  largeType("Welcome to");
  largeType(game.name);
  cout<<"\n\n";
  game.getRoomByID(currentRoomId).displayRoomName();
  cout<<"\n\n";
  game.getRoomByID(currentRoomId).displayDescription();  
  helperMessage();

 mainGameLoop(currentRoomId, game, inventory, validInput, gunFound);
 



}


void mainGameLoop(int& currentRoomId, game& game, vector<item>& inventory, bool& validInput, bool& gunFound){
   string userInput="";
   bool singleGameThread=true;
    while(singleGameThread==true){
    cout<<"\n\n>";
    userInput=getStringInRawMode(0,30);
    useUserInput(userInput, currentRoomId, game, inventory, validInput, gunFound);
  }
}



void greetingModule(){
  cout << "Welcome to Dark Cave a very small text based game\n\nBy Gabriel Malek\nMay 12, 2022\n\n";
}



//this is the main user loop.
//Basic andventure, obviously requires 5 monsters, and 5 rooms, the monsters should require some level of competence to defeat, and they should be in increasing dificulty. 
//how would they need to be defeated? Common ideas, are riddles?--doesn not sound very fun tbh,
//maybe, minigames?-- too much code--       
void useUserInput(string input, int currentRoom, game game, vector<item>& inv, bool& validInput, bool& gunFound){
  
  //help if statements
  if(input=="help"||input=="h"){ cout<<"\nTo get the most basic commands type: help basics or help b";validInput=true;};
  if(input=="help basics"||input=="h b"||input=="help b"||input=="h basics"){
    cout<< "\n\nThese are the commands you will use most often.\n\n\"look\" or \"l\": Look around the room -- repeat the description of everything you see.\n\"examine thing\" or \"x thing\": Look more closely at something -- learn more about it.\n\"inventory\" or \"i\": List everything you're carrying.\n\"north\", \"south\", \"east\", \"west\", etc., or \"n\", \"s\", \"e\", \"w\", etc.: Walk in some direction.";validInput=true;
  };




 //inventory if statments
  if(input=="i"||input=="inventory"){
      cout<<"Currently your invetory contains:\n";
      int counter=1;
     for(int i=0;i<inv.size();i++){
         if(inv[i].name!="gun"||gunFound==false){
           cout<<counter<<". "<<inv[i].name<<"\n";
           counter++;
         }else if(gunFound==true){
             cout<<counter<<". "<<inv[i].name<<"\n";
             counter++;
         }
        if(inv[i].subObjects.size()>0){
            for(int j=0;j<inv[i].subObjects.size();j++){
                if(gunFound==false&&inv[i].subObjects[j].name!="gun"){
                  cout<<counter<<". "<<inv[i].subObjects[j].name<<"\n";
                  counter++;
                }else if(gunFound==true){
                    cout<<counter<<". "<<inv[i].subObjects[j].name<<"\n";
                }
                
            }
        }
     }
  } 
 
 
 
 
  //look if statements
  if(input=="look"||input=="l"){
    cout<<"\n";
    if(currentRoom==1&&game.getRoomByID(currentRoom).descriptionRead==false){
        game.getRoomByID(currentRoom).displayRoomName();
        cout<<"\n\n";
        game.getRoomByID(currentRoom).displayDescription();  
        cout<<"You suddenly hear a loud noice, you turn around but can't see anything around you, your heart starts beating very fast, then you see it, a small hint of a giant hairless beast, it charges at you."; 
        game.getRoomByID(currentRoom).toggleDescriptionRead(true);
    }
    
  }
  if(input.substr(0,3)=="look "&&input.size()>5){
      cout<<"I'm sorry I don't know how to do that.";
  }
  

  //examine if statements.
  //self note, must be able to examine all objects, self, inventory,
  //when in a certain room where an object is meant to be the center of focus, most codes should point to it. 
  //must also be able to examine any obvious features of the room, and any things that is implied to exist, even if they are not important
  //the rooms should get more intricate over time, meaning that the amount of items should increase, last room should have at least 10 items, embedded items are optional.
  //I need to also figure out a way to manage the inventory display in a more effective way. Instead of setting game items to inventory, I should  add one item at a time, and start with the items already on me. 
  if(input=="examine"||input=="x"){
    cout<<"\n\nWhat would you like to examine?";
  }
  if(input=="examine coat"||input=="x coat"){
     game.getItemsDescByName("coat");
 } 
  if(input=="examine pockets"||input=="x pockets"){
      if(gunFound==false){
     cout<<"You pat down on your coat and feel a solid object on your chest pocket, you reach in a pull out a small"<<
     "metal pistol, your are startled at the sight of it";
     gunFound=true; 
     }else{
         cout<<"There is a gun in there. Might be useful if you find enemies.";
     }
}
  if(gunFound==true&&(input=="x gun"||input=="examine gun")){
      cout<<"A small pistol seems to be loaded.";
  }  
  };



void helperMessage(){
  cout<< "If you are stuck type -help";
}
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
        if(rawInput != 10 && rawInput!= 27 && rawInput != 127 && rawInput!=13&& rawInput!=8){
          
          input=input+char(rawInput);
          // cout<<input.size();
          }
     //if esc is pressed the program ends.
        if(rawInput == 27) {
    //cleared the console and end the program.
           // cout<< "I pressed esc;";
          exit(0); 
        } 
      if(rawInput == 13) {
    //if space bar is pressed start a new game
         cout<<"\b \b";
         inputReceived=true;
    
        cout<<"\n";
        //here I reset all console settings to default
         return input;
        } 
      if(rawInput == 127||rawInput==8){
       
        // cout<< "input is: |"<< input;
        // cout<<"size: "<<input.size();f
          #ifdef __linux__
            cout<<"\b";
          #endif
        if(input.size()>0){
           cout<<" \b";
           input = input.substr(0,input.size()-1);
        }else{
            cout<<" ";
        }
        // if(input.size()==0){
          
        // }
        // if(input.size()!=0||input.size()!='0'){
        //   // cout<<input.size();
          
          
        //   }
      }
    }
  //here I reset all console settings to default
  
  return "";
};
 
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



//the following function have preprocessors so that I can edit the code on windows.
void clear(){
    #ifdef __MINGW32__ 
     std::system("CLS");
    #endif
    #ifdef __linux__
      std::system("clear");
    #endif
 
}
char getRawInput(){

     #ifdef __MINGW32__ 
        return _getch();
    #endif
    
    #ifdef __linux__
        int rawInput;
        std::system("stty raw");
		std::system("stty -echo");
        rawInput = getchar();
        std::system("stty cooked");
		system("stty sane");
        return rawInput;
    #endif
}