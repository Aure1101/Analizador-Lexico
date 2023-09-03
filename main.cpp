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
};

AnalizadorLexico::AnalizadorLexico(){
    fileName = "codigo.txt";

}

int main(){
    return 0;
}  