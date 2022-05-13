#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include <thread>
#include <chrono>
#ifdef __MINGW32__ 
       #include <conio.h>
#endif

using std::cout;
using std::string;
using std::vector;
// using namespace std::chrono;

//we could display the entire game history, or maybe just clear the screen every time, then we use a timer.


void clear();
char getRawInput();
string getStringInRawMode(int, int, string&);
// string liveInput;



void bar(int time, string& liveInput){
    string stuff="";
    while(2){

        stuff=getStringInRawMode(20,20, liveInput);
        // exit(0); 
    }
    if(liveInput=="exit"){
		system("stty sane");
        exit(0);
    }
}

void timerMinutes(vector<string>& display, int minutesLeft, int secondsLeft, int millileft,string& liveInput){
    int minutes=0;
    int seconds=0;
    int milliSeconds=0;
    int totalTimeLeftMinutes=3;
    // int minutesLeft=0;
    // int secondsLeft=30;
    // int millileft;
    string displayMillis="00";
    string timerString;
    auto start = std::chrono::steady_clock::now();
    int current_ms_elapsed=0;
    while(2){
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto end = std::chrono::steady_clock::now();
    //change the seconds on display array every second;
      // if(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()%1==0&&std::chrono::duration_cast<std::chrono::seconds>(end - start).count()!=current_s_elapsed){
      //     current_s_elapsed= std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
      //     clear();
      //     string timerString ="Time Left- "+std::to_string(minutes)+":"+std::to_string(seconds)+":"+std::to_string(miliSeconds);
      //     cout<<timerString;
      // }
      //    if(std::chrono::duration_cast<std::chrono::minutes>(end - start).count()%1==0&&std::chrono::duration_cast<std::chrono::minutes>(end - start).count()!=current_s_elapsed){
      //     current_s_elapsed= std::chrono::duration_cast<std::chrono::minutes>(end - start).count();
      //     clear();
      //     cout<<"This is my program with a built in timer\n\n";
      //     cout<<"\rseconds: "<<current_s_elapsed<<"\n\n";
      //     cout<<"\rinput: "<<liveInput;
      //     cout.flush();
      
      // }
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
          timerString ="Time Left-> "+std::to_string(minutesLeft)+":"+std::to_string(secondsLeft)+":"+displayMillis+"\n\n";
           string inputDisplay="\rInput: "+liveInput;
          display[2]=inputDisplay;
          display[1]=timerString;
          for(int i=0;i<display.size();i++){
            cout<<"\r"<<display[i];
          }
         
            cout.flush();

          if(millileft>0){
            displayMillis="0"+std::to_string(millileft-1);
            millileft--;}

            if(millileft==0&&secondsLeft>0){
            secondsLeft--;
            millileft=10;
          }

          if(secondsLeft==0&&millileft==0&&minutesLeft>0){
            minutesLeft--;
            secondsLeft=60;
            millileft=10;
            }
        

          // if(current_ms_elapsed>0){milliSeconds=milliSeconds-current_ms_elapsed;}
      
      
      }



    if(minutesLeft==0&secondsLeft==0&millileft==0){
		    system("stty sane");
        exit(0);
    }
    
}
}


int main(){
    string liveInput;
    const int countDownTime=3;
    string titleMessage="\rWelcome to dark cave\n\n";
    vector<string> display;
    int minutes=3;
    int seconds=0;
    int miliSeconds=0;
    // string timerString ="Time Left- "+std::to_string(minutes)+":"+std::to_string(seconds)+":"+std::to_string(miliSeconds)+"\n\n";
    // string inputDisplay="\rInput: "+liveInput;
    // display[2]=inputDisplay;
    display={titleMessage,timerString,inputDisplay};
    cout<<"this is stuff";
    clear();
    string input;
    // while(getline(cin, input)){
    //     cout<<"this is an output that will stop once there is input taken.";
    //     if(input=="stop"){exit(0);}
    // }
    // auto start = std::chrono::steady_clock::now();
    int current_s_elapsed=0;
    

    cout<<timerString;
    // for(int i=0;i<display.size();i++){
    //   cout<<display[i];
    // }
    cout.flush();
    // thread first (foo);
    std::thread second(bar,2,std::ref(liveInput));;
    std::thread timeout(timerMinutes,std::ref(display),0,30,0,std::ref(liveInput));;
    // second= std::thread
    // timeout=std::thread





    // first.join();
    second.join();
    timeout.join();

    cout<<"executing both threads";




    



}




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


string getStringInRawMode(int minSize, int maxSize, string& liveInput){
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
            liveInput=liveInput+char(rawInput);
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
          liveInput="ss";
          liveInput="";
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
        if(insideinput.size()>0||liveInput.size()>0){
           cout<<" \b";
             liveInput = liveInput.substr(0,liveInput.size()-1);
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
