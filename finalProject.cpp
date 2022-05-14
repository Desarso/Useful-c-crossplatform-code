// Final Project;
// Gabriel Malek
// 5/12/2022

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>
//I use a windows prepocessor so that I can edit my code on my laptop and it uses a .h library but it doesn't utilize the library unless it's on windows.
#ifdef __MINGW32__ 
       #include <conio.h>
       #include <windows.h>
#endif

using std::cout;
using std::string;
using std::vector;
using std::fstream;
// using std::ref;
// using std::thread;

//I want the dungeon game to use verbs ans stuff, so I'm thinking that the rooms can have verbs
//and then the monsters can also have verbs, and stuff
//Possible verbs for room:
//look around,
const string DEFAULT_FILE_NAME="data.dat";
const string out="out";
const string app="app";
void largeType(string input);
void clear();

struct displayObject{
    string liveInput, lastInput, itemDescription, invItemDesc;
    int order;
    bool titleBool, descBool, itemDescB, invDesB;
    vector<string> currentDisplay;
    int title, description;
    void displayItemDescription(){

    }

    
};
struct timerVariables{
    int minutesLeft,secondsLeft, millileft;
};
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
  int descriptionRead=0;
  bool monsterSpawn=false;
  bool monsterKilled=false;
  int amountOfTimeAccessed;
  vector<item> items;
  room(string name, string desc, int id, vector<item> ite, int n, int s, int e, int w, bool descRead){
    room_name=name;
    room_description=desc;
    room_id=id;
    items=ite;
    N=n;
    S=s;
    E=e;
    W=w;
    descriptionRead=descRead;
  }


  void getItemsDescByName(string Nam){
    for(int i=0;i<items.size();i++){
        if(items[i].name==Nam){
            cout<<items[i].description;
        }
    }
}
  int getNextRoomId(string cords){
       if(cords=="N"||cords=="n"){return N;}
       if(cords=="E"||cords=="e"){return E;}
       if(cords=="S"||cords=="s"){return S;}
       if(cords=="W"||cords=="w"){return W;}
    return 0;
   }
   
   int getCurrentRoomId(){
       return room_id;
   }

  void displayRoomName(){
      largeType(room_name);
  }
  void toggleDescriptionRead(){
      descriptionRead=1;
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
struct player{
    string name;
    int lives=8;
    vector<item> inventory;
    player(string n, vector<item> i){
        name=n;
        inventory=i;
    };
    void setLives(int l){
        lives=l;
    };

    void getItemsDescByName(string Nam){
        for(int i=0;i<inventory.size();i++){
            if(inventory[i].name==Nam){
                cout<<inventory[i].description;
            }
        }
    };
};

class game{
 
  
public:
  string input;
  int currentId=1;
  bool validInput=false;
  bool gunFound=false;
  bool singleThread=true;
  bool shootable=false;
  bool multiThreadingOn=false;
  player player1={"",{}};
  vector<room> rooms;
  string name;
  game(string n, vector<room> r){
    name=n;
    rooms=r;
  };
  room getRoomByID(int ID);
  void changeCurrentId(int id);
//   game fetchData();
//   void writeData(string mode);
//   void displayAllGameData();
//   vector<item> getItems();
//   void getItemsDescByName(string Nam); 
};
//this function serializes the game object data to an external file

// void game::writeData(string mode){
//   const string myName= "data.dat";
//   const string end="~";
//   fstream myFile;
//   if(mode=="app"){myFile.open(DEFAULT_FILE_NAME, std::ios::app);}
//   if(mode=="out"){myFile.open(DEFAULT_FILE_NAME,std::ios::out);}
//    if (myFile.is_open()){
//      myFile<<"`A Dark Cave`~";
//      for(int i=0;i<rooms.size();i++){
//        myFile<<"$"<<rooms[i].room_name<<end
//        <<rooms[i].room_id<<end
//        <<rooms[i].room_description<<end
//        <<rooms[i].N<<"|"<<rooms[i].S<<"|"<<rooms[i].E<<"|"<<rooms[i].W<<end;
//      }
//      for(int i=0;i<rooms.items.size();i++){
//        myFile<<"%"<<rooms.items[i].name<<end
//        <<items[i].description<<end;
//        for(int j=0;j<items[i].subObjects.size();j++){
//          myFile<<"*"<<items[i].subObjects[j].name<<end
//          <<items[i].subObjects[j].description<<end;
//        }
//      }
//      myFile.close();
//    }
// };

// //this horribly function deserializes the object data, it's all by hand, I'm sure there's better ways to do this, but I couldn't find any built in short libraries.

// game game::fetchData(){
//    fstream fileRead;
//    string line;
//    int roomsIndex=0;
//    int itemsIndex=0;
//    int index =0;
//    string roomName,roomDescription,itemName,itemDesc,subItemName, subItemDesc;
//    int roomId;
//    int N,S,W,E;
//    vector<game> games={};
//    vector<room> roomHelper={};
//    vector<item> itemHelper={};
//    vector<item> subItemsHelper={};
//    int subObjectsIndex;
//    fileRead.open(DEFAULT_FILE_NAME, std::ios::in);
//    if(fileRead.is_open()){
//      while(getline(fileRead, line,'~')){
//         if(!line.size()){cout << "empty file";fileRead.close(); break;}
//         if(line[0]=='`'){
//           name=line.substr(1,line.size()-2);
//           getline(fileRead, line,'~');
//           index++;
//           index=1;
//             }//get game name
//         if(line[0]=='$'){  
//           roomName=line.substr(1,line.size());
//           getline(fileRead, line,'~');
//           index=1;
//           if(index%3==1||index==1){
//             roomId=stoi(line);
//              getline(fileRead, line,'~');
//              index++;
//         }
//           if(index%3==2||index==2){
//             roomDescription=line;
//             getline(fileRead, line,'~');
//             index++;
//           }
//           if(index%3==0||index==3){
//             N=stoi(line.substr(0,1));
//             S=stoi(line.substr(2,3));
//             E=stoi(line.substr(4,5));
//             W=stoi(line.substr(6,7));
//             roomHelper.push_back(room(roomName, roomDescription, roomId,N,S,E,W));
//           }
//           roomsIndex++;
//           index=1;
//          }//get rooms
//         if(line[0]=='%'){
//           index=1;
//           if(index%2==1||index==1){
//             itemName=line.substr(1,line.size());
//             getline(fileRead, line,'~');
//             index++;
//         }//item name
//           if(index%2==0||index==2){
//             itemDesc=line.substr(1,line.size());
//             getline(fileRead, line,'~');
//             index++;
//           }//item desc
//           while(line[0]=='*'){
//              subObjectsIndex=0;
//              if(index%2==1||index==1){
//             subItemName=line.substr(1,line.size());
//             getline(fileRead, line,'~');
//             index++;
//         }
//           if(index%2==0||index==2){
//             subItemDesc=line.substr(1,line.size());
//             getline(fileRead, line,'~');
//             index++;
//           }
//             subItemsHelper.push_back(item(subItemName,subItemDesc));
//             subObjectsIndex++;
//           }//get sub items
//           itemHelper.push_back(item(itemName, itemDesc, subItemsHelper));
//           subItemsHelper={};
//           itemsIndex++;
//           index=1;
//          }//get items and subItems
//         index++;
//       }
//      games.push_back(game(roomName,roomHelper, itemHelper));
//      fileRead.close();
//    };
//   return games[0];
// }

void game::changeCurrentId(int id){
  currentId=id;
};
room game::getRoomByID(int ID){
    return rooms[ID-1];
  }

// void game::displayAllGameData(){
//   cout<<"GAME NAME: "<<name<<"\n\n";
//   for(int i=0;i<rooms.size();i++){
//     rooms[i].displayRoomData();
//   }
//   for(int i=0;i<items.size();i++){
//     items[i].displayItemData();
//   }
// }
// vector<item> game::getItems(){
//   return items;
// };
// void game::getItemsDescByName(string Nam){
//     for(int i=0;i<items.size();i++){
//         if(items[i].name==Nam){
//             cout<<items[i].description;
//         }
//     }
// }
//function declarations
void greetingModule();

//this function is help, i and look. Need seperate functions for more complex tasks.
void useUserInput(game&);


//verb functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void examineFunction(game&);
void useFunction(game&);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//this is where I gave up and started using global variables
displayObject displayObj;
timerVariables timerVars;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void help(string input);
void helperMessage();
string getStringInRawMode(int minSize, int maxSize);
char getRawInput();
void mainGameLoop(game& game);
void multiThreadProgram(game& game);
void timerMinutes(game&);
void displayVerb(game&);
void moveToRoom(game& game);






int main() {
  clear();
  string playerName;
  cout<<"Before we being, please input your name.";
  playerName=getStringInRawMode(20,20);
  player player1=player(playerName, {item("coat", "A heavy brown coat, keeps, you warm, also seems to have many pockets.",{item("gun","A small handheld pistol")})} );

//north,south,east,west.
  game game={"Death in the Dark",{room("Dark Cave",
                 "A small dark cave, smells faintly like sulfur, there is a dim candle attached to the wall. You can barely make out the smooth and damp texture of the walls, the room is earily silent and cold, good thing you are wearing a coat.",
                1,{item("passage","A small passage way to another room.")},
                2,0,0,0,false),room("Cave Room 2",
    "You run thru a corridor of stone, and make it to an opening with a small amount of faint light. You Panic as you realize the room is a small ledge with a large bottomless pit in the middle that you are currently running towards. You attempt to stop digging your heel into the ground, and your hurt leg sends shocks of agony thru your body, you fail to come to a complete stop, and just before you fall you manage to grab the ledge. You are now hanging from your left hand...'AHHHHH!' you yell as you dangle from one arm. Your strength catches you by surprise as you are able to easily hold yourself.",
  2,{},
  0,1,0,0,false)}};
  game.player1=player1;

  int currentRoomId=game.rooms[0].getCurrentRoomId();
//   game.player1.inventory = game.items;

  ////main program code
 
  greetingModule();
  largeType("Welcome to");
  largeType(game.name);
  cout<<"\n\n";
  game.getRoomByID(currentRoomId).displayRoomName();
  cout<<"\n\n";
  game.getRoomByID(currentRoomId).displayDescription();  
  helperMessage();
  mainGameLoop(game);
 



}


void mainGameLoop(game& game){
    while(2){
    if(game.singleThread==false&&game.multiThreadingOn==false){
        multiThreadProgram(game);
    }
    cout<<"\n\n >";
    bool skipFunctions=false;
    game.input=getStringInRawMode(0,30);
    clear();
    displayObj.titleBool=false;
    displayObj.descBool=false;
    displayObj.invDesB=false;
    displayObj.itemDescB=false;
    displayObj.currentDisplay={};
     displayObj.title=0;
    displayObj.description=0;
   
    skipFunctions=false;
    vector<string> validInputs={"n","north","s","south","e","east","w","west"};
    for(int i=0;i<validInputs.size();i++){
      if(game.input==validInputs[i]){
        moveToRoom(game);
        skipFunctions=true;
      }
    }
    
    if(game.input.find("use")!=string::npos&&skipFunctions==false){
      useFunction(game);
      skipFunctions=true;
    }
    
    if((game.input.find("examine")!=string::npos||game.input.substr(0,1)=="x")&&skipFunctions==false){
      examineFunction(game);
      skipFunctions=true;
    }

    if(skipFunctions==false){useUserInput(game);}
  }
  
}

void multiThreadProgram(game& game){
    game.multiThreadingOn=true;
    string input;
    string liveInput;
    timerVars.minutesLeft=3;
    timerVars.secondsLeft=30;
    std::thread mainThread(mainGameLoop, std::ref(game));;
    std::thread timeout(timerMinutes, std::ref(game));

    mainThread.join();
    timeout.join();
}


void greetingModule(){
  cout << "Welcome to Dark Cave a very small text based game\n\nBy Gabriel Malek\nMay 12, 2022\n\n";
}



//this is the main user loop.
//Basic andventure, obviously requires 5 monsters, and 5 rooms, the monsters should require some level of competence to defeat, and they should be in increasing dificulty. 
//how would they need to be defeated? Common ideas, are riddles?--doesn not sound very fun tbh,
//maybe, minigames?-- too much code-- 
void moveToRoom(game& game){
  int nextRoom;
  if(game.input=="n"||game.input=="north"){
    nextRoom=game.getRoomByID(game.currentId).getNextRoomId("n");
    if(nextRoom!=0){
      game.changeCurrentId(nextRoom);
      game.getRoomByID(game.currentId).displayRoomName();
      displayObj.title=game.currentId;
      if(game.getRoomByID(game.currentId).descriptionRead==false){
        game.getRoomByID(game.currentId).displayDescription();
        game.rooms[game.currentId-1].descriptionRead=1;
        displayObj.description=game.currentId;
      }else{
        displayObj.description=0;
      }
    }else{
      cout<<"You can't go that way.";
    }
    
    return;
  }
  if(game.input=="s"||game.input=="south"){
    nextRoom=game.getRoomByID(game.currentId).getNextRoomId("s");
     if(nextRoom!=0){
      game.changeCurrentId(nextRoom);
      game.getRoomByID(game.currentId).displayRoomName();
      displayObj.title=game.currentId;
      if(game.getRoomByID(game.currentId).descriptionRead==false){
        game.getRoomByID(game.currentId).displayDescription();
        game.rooms[game.currentId-1].descriptionRead=1;
        displayObj.description=game.currentId;
      }else{
        displayObj.description=0;
      }
    }else{
      cout<<"You can't go that way.";
    }
    return;
  }
  if(game.input=="w"||game.input=="west"){
    nextRoom=game.getRoomByID(game.currentId).getNextRoomId("w");
     if(nextRoom!=0){
      game.changeCurrentId(nextRoom);
      game.getRoomByID(game.currentId).displayRoomName();
      displayObj.title=game.currentId;
      if(game.getRoomByID(game.currentId).descriptionRead!=true){
        game.getRoomByID(game.currentId).displayDescription();
        game.getRoomByID(game.currentId).toggleDescriptionRead();
        displayObj.description=game.currentId;
      }
    }else{
      cout<<"You can't go that way.";
    }
    return;
  }
  if(game.input=="e"||game.input=="east"){
    nextRoom=game.getRoomByID(game.currentId).getNextRoomId("e");
     if(nextRoom!=0){
      game.changeCurrentId(nextRoom);
      game.getRoomByID(game.currentId).displayRoomName();
      displayObj.title=game.currentId;
      if(game.getRoomByID(game.currentId).descriptionRead!=true){
        game.getRoomByID(game.currentId).displayDescription();
        game.getRoomByID(game.currentId).toggleDescriptionRead();
        displayObj.description=game.currentId;
      }
    }else{
      cout<<"You can't go that way.";
    }
    return;
  }

}

void useUserInput( game& game){
    displayObj.titleBool =false;
    displayObj.descBool = false;
    displayObj.invDesB = false;
    displayObj.itemDescB = false;
    displayObj.currentDisplay={};
    vector<string> allowedInput;
  //help if statements

    allowedInput={"help","h","-help","-h","help basics","h b","help b","h basics"};

  for(int i=0;i<allowedInput.size();i++){
       if(game.input==(allowedInput[i])){ 
        displayObj.currentDisplay.push_back("\n\nThese are the commands you will use most often.\n\n\"look\" or \"l\": Look around the room -- repeat the description of everything you see.\n\"examine thing\" or \"x thing\": Look more closely at something -- learn more about it.\n\"inventory\" or \"i\": List everything you're carrying.\n\"north\", \"south\", \"east\", \"west\", etc., or \"n\", \"s\", \"e\", \"w\", etc.: Walk in some direction.");
        cout<<displayObj.currentDisplay[0];
        game.validInput=true;
        return;

        }
  }
   




 //inventory if statments
 allowedInput={"inv","i","inventory","in","inve"};
    
   for(int i=0;i<allowedInput.size();i++){
       if(game.input==(allowedInput[i])){ 
          displayObj.currentDisplay.push_back("Currently your inventory contains:\n");               
          cout<<displayObj.currentDisplay[0];
          int counter=1;
     
     for(int i=0;i<game.player1.inventory.size();i++){
         if(game.player1.inventory[i].name!="gun"||game.gunFound==false){
            displayObj.currentDisplay.push_back(std::to_string(counter)+". "+game.player1.inventory[i].name+"\n"); 
            cout<<counter<<". "<<game.player1.inventory[i].name<<"\n";
            counter++;
         }else if(game.gunFound==true){
             displayObj.currentDisplay.push_back(std::to_string(counter)+". "+game.player1.inventory[i].name+"\n");
             cout<<counter<<". "<<game.player1.inventory[i].name<<"\n";
             counter++;
         }
        if(game.player1.inventory[i].subObjects.size()>0){
            for(int j=0;j<game.player1.inventory[i].subObjects.size();j++){
                if(game.gunFound==false&&game.player1.inventory[i].subObjects[j].name!="gun"){
                  displayObj.currentDisplay.push_back(std::to_string(counter)+". "+game.player1.inventory[i].subObjects[j].name+"\n");
                  cout<<counter<<". "<<game.player1.inventory[i].subObjects[j].name<<"\n";
                  counter++;
                }else if(game.gunFound==true){
                    displayObj.currentDisplay.push_back(std::to_string(counter)+". "+game.player1.inventory[i].subObjects[j].name+"\n");
                    cout<<counter<<". "<<game.player1.inventory[i].subObjects[j].name<<"\n";
                }
                
            }
        }
              
     
     game.validInput=true;
        }}
  }

 
  //look if statements
  allowedInput={"look","l","look around","l around"};
    for(int i=0;i<allowedInput.size();i++){
       if(game.input==(allowedInput[i])){ 
            cout<<"\n";
            game.getRoomByID(game.currentId).displayRoomName();
            displayObj.title=game.currentId;
            displayObj.titleBool=true;
            cout<<"\n\n";
            displayObj.description=game.currentId;
            displayObj.descBool=true;
            game.getRoomByID(game.currentId).displayDescription();
            game.getRoomByID(game.currentId).toggleDescriptionRead();
            game.validInput=true; 
       
        if(game.gunFound==true&&game.currentId==1){
            displayObj.currentDisplay.push_back("\rYou suddenly hear a loud noice, you turn around but can't see anything around you, your heart starts beating very fast, then you see it, a small hint of a giant hairless beast, it charges at you.");
            cout<<"You suddenly hear a loud noice, you turn around but can't see anything around you, your heart starts beating very fast, then you see it, a small hint of a giant hairless beast, it charges at you."; 
            game.singleThread=false;
        } 
        game.validInput=true;
        }
        if(game.validInput=false){
             displayObj.currentDisplay.push_back("I'm sorry I don't know how to do that.");
            cout<<"I'm sorry I don't know how to do that.";
        }
  }

  



  };

void examineFunction(game& game){
    //examine if statements.
  //self note, must be able to examine all objects, self, inventory,
  //when in a certain room where an object is meant to be the center of focus, most codes should point to it. 
  //must also be able to examine any obvious features of the room, and any things that is implied to exist, even if they are not important
  //the rooms should get more intricate over time, meaning that the amount of items should increase, last room should have at least 10 items, embedded items are optional.
  //I need to also figure out a way to manage the inventory display in a more effective way. Instead of setting game items to inventory, I should  add one item at a time, and start with the items already on me. 
  displayObj.titleBool= false;
  displayObj.descBool = false;
  displayObj.invDesB = false;
  displayObj.itemDescB=false;
  displayObj.currentDisplay={};
  if(game.input=="examine room"||game.input=="x room"){
    cout<<"\n\rThere is no need to refer to the room directly, rather refer to it's items and features";
    displayObj.currentDisplay.push_back("\n\rThere is no need to refer to the room directly, rather refer to it's items and features");
    return;
  }
  if(game.input=="examine"||game.input=="x"){
    cout<<"\n\nWhat would you like to examine?";
    displayObj.currentDisplay.push_back("\n\nWhat would you like to examine?");
    return;
  }
  if(game.input=="examine coat"||game.input=="x coat"){
     game.player1.getItemsDescByName("coat");
     displayObj.itemDescription=("coat");
     displayObj.invDesB=true;
     return;
 } 
  if(game.input=="examine pockets"||game.input=="x pockets"||game.input=="x pocket"||game.input=="examine pocket"){
      if(game.gunFound==false){
    displayObj.currentDisplay.push_back("You pat down on your coat and feel a solid object on your chest pocket, you reach in a pull out a small metal pistol, your are startled at the sight of it.");
     cout<<"You pat down on your coat and feel a solid object on your chest pocket, you reach in a pull out a small "<<
     "metal pistol, your are startled at the sight of it. GUN HAS BEEN ADDED TO INVENTORY.";
     game.gunFound=true;
     return; 
     }else{
         displayObj.currentDisplay.push_back("There is a gun in there. Might be useful if you find enemies.");
         cout<<"There is a gun in there. Might be useful if you find enemies.";
         return;
     }
}
  if(game.gunFound==true&&(game.input=="x gun"||game.input=="examine gun"||game.input=="x pistol"||game.input=="examine pistol")){
      displayObj.currentDisplay.push_back("A small pistol seems to be loaded.");
      cout<<"A small pistol seems to be loaded.";
      return;
  }  
  for(int i=0;i<game.getRoomByID(game.currentId).items.size();i++){
      if(game.input.size()<=0){return;}
      if((game.input.find("examine")!=string::npos||game.input.substr(0,1).find("x")!=string::npos)&&(game.input.find(game.getRoomByID(game.currentId).items[i].name)!=string::npos||game.input.find(game.getRoomByID(game.currentId).items[i].name)!=string::npos)){

            game.getRoomByID(game.currentId).getItemsDescByName(game.getRoomByID(game.currentId).items[i].name);
            displayObj.itemDescription=(game.getRoomByID(game.currentId).items[i].name);
            displayObj.itemDescB=true;
            return;
      }
  }
  for(int i=0;i<game.player1.inventory.size();i++){
      if(game.input.size()<=0){return;}
      if(game.input.size()>=game.player1.inventory[i].name.size()){
      if((game.input.find("examine")!=string::npos||game.input.substr(0,1).find("x")!=string::npos)&&(game.player1.inventory[i].name.find(game.input)!=string::npos||game.player1.inventory[i].name.find(game.input)!=string::npos)){
          cout<<game.player1.inventory[i].description;
          displayObj.invDesB=true;
          displayObj.invItemDesc=game.player1.inventory[i].name;
          return;
      }}
  }
}

void useFunction(game& game){
     displayObj.titleBool= false;
  displayObj.descBool = false;
  displayObj.invDesB = false;
  displayObj.itemDescB=false;
    displayObj.currentDisplay={};
  //use if statements

  if(game.input=="use"){
    cout<<"What would you like to use";
  }
  if((game.gunFound==true)&(game.input=="use gun"||game.input=="use pistol"||game.input=="u gun"||game.input=="u pistol")){
    cout<<"What would you like to use the gun for.\nUse connecting words like on or at such as 'verb' on 'noun' or 'verb' at 'noun.";
  }

}

void helperMessage(){
  cout<< "If you are stuck type -help";
}

string getStringInRawMode(int minSize, int maxSize){
      string insideinput="";
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
            displayObj.liveInput=displayObj.liveInput+char(rawInput);
          insideinput=insideinput+char(rawInput);
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
        //  cout<<"\b \b";
         inputReceived=true;
        cout<<"\n";
          // clear();
          // cout<<insideinput;
          // exit(0);
          displayObj.liveInput="ss";
          displayObj.liveInput="";
        //here I reset all console settings to default
         return insideinput;
        } 

        //backspace
      if(rawInput == 127||rawInput==8){
       
        // cout<< "input is: |"<< input;
        // cout<<"size: "<<input.size();f
          #ifdef __linux__
            cout<<"\b";
          #endif
        // if(liveInput.size()>0){
           
        // }
        if(insideinput.size()>0||displayObj.liveInput.size()>0){
           cout<<" \b";
             displayObj.liveInput = displayObj.liveInput.substr(0,displayObj.liveInput.size()-1);
           insideinput=insideinput.substr(0,insideinput.size()-1);
           
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
  cout<< "\n\r";
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
   cout<< "\n\r";
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
  cout << "\n\r";
}

void displayVerb(game& game){
    game.getRoomByID(game.currentId).displayRoomName();
    for(int i=0;i<displayObj.currentDisplay.size();i++){
        cout<<displayObj.currentDisplay[i];
    }
};

void timerMinutes(game& game){
    int minutes=0;
    int seconds=0;
    int milliSeconds=0;
    string displayMillis="00";
    string timerString;
    auto start = std::chrono::steady_clock::now();
    int current_ms_elapsed=0;
    while(2){
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto end = std::chrono::steady_clock::now();
 
         if((std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())%100==0&&(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())!=current_ms_elapsed){
          current_ms_elapsed++;
          milliSeconds++;
   
    
         
          if(milliSeconds>10){
            milliSeconds=0;
            seconds++;
            }
          if(seconds>=60){
            seconds=0;
            minutes++;
          }

          //time down

          clear();
          timerString ="\n\n\nTime Left-> "+std::to_string(timerVars.minutesLeft)+":"+std::to_string(timerVars.secondsLeft)+":"+displayMillis+"\n";
           string inputDisplay="\rInput: "+displayObj.liveInput;
            // game.getRoomByID(game.currentId).displayRoomName();
           if(displayObj.title!=0){game.getRoomByID(displayObj.title).displayRoomName();cout<<"\n\n\r";}
           if(displayObj.description!=0){game.getRoomByID(displayObj.description).displayDescription();}
           if(displayObj.invDesB==true){game.player1.getItemsDescByName(displayObj.itemDescription);}
           if(displayObj.itemDescB==true){game.getRoomByID(game.currentId).getItemsDescByName(displayObj.itemDescription);}
        
            cout<<"\n";
            for(int i=0;i<displayObj.currentDisplay.size();i++){
                cout<<"\r"<<displayObj.currentDisplay[i];
            }  
            cout<<"\nr"<<timerString;
            cout<<"\r";
            for(int i=0;i<game.player1.lives;i++){
              cout<<"\033[1;31m❤\033[0m";
            }
            cout<< "\n\n\r> "<<displayObj.liveInput;
            cout.flush();

          if(timerVars.millileft>0){
            displayMillis="0"+std::to_string(timerVars.millileft-1);
            timerVars.millileft--;}

            if(timerVars.millileft==0&&timerVars.secondsLeft>0){
            timerVars.secondsLeft--;
            timerVars.millileft=10;
          }

          if(timerVars.secondsLeft==0&&timerVars.millileft==0&&timerVars.minutesLeft>0){
            timerVars.minutesLeft--;
            timerVars.secondsLeft=60;
            timerVars.millileft=10;
            }
    //                 cout<<"this works";
    // exit(0);

          // if(current_ms_elapsed>0){milliSeconds=milliSeconds-current_ms_elapsed;}
      
      
      }



    if(timerVars.minutesLeft==0&timerVars.secondsLeft==0&timerVars.millileft==0){
      clear();
      timerString ="\n\n\nTime Left-> "+std::to_string(timerVars.minutesLeft)+":"+std::to_string(timerVars.secondsLeft)+":"+displayMillis+"\n";
        string inputDisplay="\rInput: "+displayObj.liveInput;
        // game.getRoomByID(game.currentId).displayRoomName();
        if(displayObj.title>0){game.getRoomByID(displayObj.title).displayRoomName();cout<<"\n\n\r";}
        if(displayObj.description>0){game.getRoomByID(displayObj.description).displayDescription();}
        for(int i=0;i<displayObj.currentDisplay.size();i++){
            cout<<"\n\r"<<displayObj.currentDisplay[i];
        }
        cout<<"\n\n\r"<<timerString;
        cout<<"\r";
        for(int i=0;i<game.player1.lives;i++){
          cout<<"\033[1;31m❤\033[0m";
        }
        cout<< "\n\n\r> "<<displayObj.liveInput;
        cout.flush();
		    system("stty sane");
        exit(0);
    }
    
}
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