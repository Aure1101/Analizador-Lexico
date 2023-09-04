#include <iostream>
#include <stdio.h>

using namespace std;

class AnalizadorLexico{
    private:
        string fileName;
        int location;
    public:
        char getNextCharacter();
        int regularExpresionChecker();
        AnalizadorLexico();
        AnalizadorLexico(string);
};

AnalizadorLexico::AnalizadorLexico(){
    fileName = "codigso.txt";
}

AnalizadorLexico::AnalizadorLexico(string fileName){
    this -> fileName = fileName;
}

int main(){
    return 0;
}  