#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#ifdef __MINGW32__ 
       #include <conio.h>
#endif

using std::cout;
using std::string;
// using namespace std::chrono;


void clear();
char getRawInput();
string getStringInRawMode(int, int);
string liveInput;



void bar(int time){
    string stuff="";
    while(2){

        liveInput=getStringInRawMode(20,20);
        // exit(0); 
    }
    if(liveInput=="exit"){
		system("stty sane");
        exit(0);
    }
}

void timer(){
    auto start = std::chrono::steady_clock::now();
    int current_s_elapsed=0;
    while(2){
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    auto end = std::chrono::steady_clock::now();
    if(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()%1==0&&std::chrono::duration_cast<std::chrono::seconds>(end - start).count()!=current_s_elapsed){
    current_s_elapsed= std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    clear();
    cout<<"This is my program with a built in timer\n\n";
    cout<<"\rseconds: "<<current_s_elapsed<<"\n\n";
    cout<<"\rinput: "<<liveInput;
    cout.flush();
}
    if(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()==30){
		system("stty sane");
        exit(0);
    }
    
}
}


int main(){
    cout<<"this is stuff";
    clear();
    string input;
    // while(getline(cin, input)){
    //     cout<<"this is an output that will stop once there is input taken.";
    //     if(input=="stop"){exit(0);}
    // }
    auto start = std::chrono::steady_clock::now();
    int current_s_elapsed=0;
    
// while(2){
//     this_thread::sleep_for(chrono::milliseconds(50));
//     auto end = chrono::steady_clock::now();
//     if(chrono::duration_cast<chrono::seconds>(end - start).count()%1==0&&chrono::duration_cast<chrono::seconds>(end - start).count()!=current_s_elapsed){
//     cout << "\nseconds passed: " << chrono::duration_cast<chrono::seconds>(end - start).count();
//     current_s_elapsed= chrono::duration_cast<chrono::seconds>(end - start).count();
// }
//     if(chrono::duration_cast<chrono::seconds>(end - start).count()==30){
//         exit(0);
//     }
    
// }
   
    cout<<"\rThis is my program with a built in timer\n\n";
    cout<<"\rseconds: 0\n\n";
    cout<<"\rinput: ";
    cout.flush();
    // thread first (foo);
    std::thread second;
    second= std::thread(bar,2);
    std::thread timeOut(timer);





    // first.join();
    second.join();
    timeOut.join();

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
