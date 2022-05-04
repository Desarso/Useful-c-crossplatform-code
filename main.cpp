
#include <iostream> 
  #ifdef __MINGW32__ 
       #include <conio.h>
    #endif

using namespace std;


void clear();
char getRawInput();


int main(){
    cout<< "stuff\n";
    int rawInput;
    char charInput;
    rawInput=getRawInput();
    charInput=rawInput;
    cout<<"Your raw input was: "<<"\n";
    cout<<"Your char input was:"<<charInput<<"\n";
    // cout<<"this also";
    // <<" and also: "<<charInput;

}

void clear(){
    #ifdef __MINGW32__ 
     system("CLS");
    #endif
    #ifdef __linux__
        system("clear");
    #endif
 
}


char getRawInput(){
     #ifdef __MINGW32__ 
        return _getch();
    #endif
    #ifdef __linux__
        system("stty raw");
        rawInput = getchar();
        system("stty cooked");
        return rawInput;
    #endif
}