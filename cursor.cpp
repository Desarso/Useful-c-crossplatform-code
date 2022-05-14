#include <windows.h>
#include <iostream>

using namespace std;
int main(){
cout<<"1234a6789\n";//1/
cout<<"1234b6789\n";//2
cout<<"123456789\n";//3
cout<<"123456789\n";//4
cout<<"123456789\n";//5
cout<<"123456789\n";//6
cout<<"123456789\n";//7
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos = {0, 0};
SetConsoleCursorPosition(hConsole, pos);
for(int i=0;i<40;i++){
    cout<<"                                                                                                   \n";
}
SetConsoleCursorPosition(hConsole, pos);
// cout<<"123456789\n";//8
// cout<<"123456789\n";//9
// cout<<"123456789\n";//10
// cout<<"123456789\n";//11
// cout<<"1234y6789\n";//12
// cout<<"1234x6789\n";//13
// cout<<"1234z6789\n";//14


// WriteConsole(hConsole, "Hello", 5, NULL, NULL);
return 0;
}