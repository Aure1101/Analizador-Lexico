//Analizador Lexico Fase 1
// Elaborado por:
// Froylan Adair Villegas Castro 2022670111
// Aurelio Flores Nava 2022670038

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

class AnalizadorLexico{
    private:
        char getNextCharacter();
        bool isLowerCase(char);
        bool isUpperCase(char);
        bool isNumber(char);
        ifstream file;
    public:
        string checkRegularExpresion();
        AnalizadorLexico();
        bool hasFileEnded();
        AnalizadorLexico(string);
        ~AnalizadorLexico();
};

AnalizadorLexico::AnalizadorLexico(){
    file.open("codigo.txt");
    if(!file.is_open()){
        exit(EXIT_FAILURE);
    }
}


AnalizadorLexico::AnalizadorLexico(string fileName){
    file.open(fileName);
        if(!file.is_open()){
        exit(EXIT_FAILURE);
    }
}

AnalizadorLexico::~AnalizadorLexico(){
    file.close();
}

bool AnalizadorLexico::isLowerCase(char c){
    if(int(c)>= 97 && int(c)<=122){
        return true;
    }
    return false;
}

bool AnalizadorLexico::isUpperCase(char c){
    if(int(c)>= 65 && int(c)<=90){
        return true;
    }
    return false;
}

bool AnalizadorLexico::isNumber(char c){
    if(int(c)>= 48 && int(c)<=57){
        return true;
    }
    return false;
}

bool AnalizadorLexico::hasFileEnded(){
    return file.eof();
}

char AnalizadorLexico::getNextCharacter(){
    char c;
    file.get(c);
    return c;
}

string AnalizadorLexico::checkRegularExpresion(){
    string palabra;
    palabra += getNextCharacter(); 
    switch(int(palabra[0])){
        case 64: //@ Identificador
            palabra += getNextCharacter(); 
            if(!isLowerCase(palabra.back()) || (palabra.back() == ' ' && file.eof())){
                return palabra;
            }
            while(palabra.back() != ' ' && !file.eof() && isLowerCase(palabra.back())){
                palabra += getNextCharacter();
            }
            while(palabra.back() != ' ' && !file.eof() && isNumber(palabra.back())){
                palabra += getNextCharacter();
            }
            if(palabra.back() == ' ' || file.eof()){
                return palabra;
            }
            return palabra;
        break;

        case 35: //# Palabra Reservada
            palabra += getNextCharacter(); 
            if(!isUpperCase(palabra.back()) || (palabra.back() == ' ' && file.eof())){
                return palabra;
            }
            palabra += getNextCharacter(); 
            while(palabra.back() != ' ' && !file.eof() && isLowerCase(palabra.back())){
                palabra += getNextCharacter();
            }
            while(palabra.back() != ' ' && !file.eof() && isNumber(palabra.back())){
                palabra += getNextCharacter();
            }
            if(palabra.back() == ' ' || file.eof()){
                return palabra;
            }
            return palabra;
        break;
        
        default:
            if(isNumber(palabra.back())){ //Numero
                while(isNumber(palabra.back())){
                    palabra += getNextCharacter();
                }
                if(palabra.back() == ' ' || file.eof()){
                    return palabra;
                }
                if(palabra.back() == '.'){
                    palabra += getNextCharacter();
                }
                while(isNumber(palabra.back())){
                    palabra += getNextCharacter();
                }
                if(palabra.back() == ' ' || file.eof()){
                    return palabra;
                }
            }
            //ninguno
            return palabra;
        break;
    }
    return palabra;
}

int main(){
    AnalizadorLexico hola;
    while(!hola.hasFileEnded()){
    cout << hola.checkRegularExpresion() << endl;
    }
    return 0;
}  