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
        char nextCharacter;
        char auxCharacter = NULL;
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

//Constructores y Destructor------------------------------------------
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

//Banderas-------------------------------------------------
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

//Metodos 
char AnalizadorLexico::getNextCharacter(){
    char c = this -> nextCharacter;
    if (auxCharacter == NULL){
        file.get(this -> nextCharacter);
        return c;
    }
    this -> nextCharacter = auxCharacter;
    auxCharacter = NULL;
    return c;
}

string AnalizadorLexico::checkRegularExpresion(){
    string palabra;
    start:
    palabra += getNextCharacter(); 
    switch(int(palabra[0])){
        case 64: //@ Identificador
            if(!isLowerCase(this -> nextCharacter) || (this -> nextCharacter == ' ' && file.eof())){
                return palabra;
            }
            palabra += getNextCharacter(); 
            while(this -> nextCharacter != ' ' && !hasFileEnded() && isLowerCase(this -> nextCharacter)){
                palabra += getNextCharacter();
            }
            while(this -> nextCharacter != ' ' && !hasFileEnded() && isNumber(this -> nextCharacter)){
                palabra += getNextCharacter();
            }
            if(this -> nextCharacter == ' ' || hasFileEnded()){
                return palabra;
            }
            return palabra;
        break;

        case 35: //# Palabra Reservada
            if(!isUpperCase(this -> nextCharacter) || (this -> nextCharacter == ' ' && file.eof())){
                return palabra;
            }
            palabra += getNextCharacter(); 
            while(this -> nextCharacter != ' ' && !file.eof() && isLowerCase(this -> nextCharacter)){
                palabra += getNextCharacter();
            }
            if(this -> nextCharacter == ' ' || file.eof()){
                return palabra;
            }
            return palabra;
        break;
        
        default:
            if(isNumber(palabra.back())){ //Numero
                while(isNumber(this -> nextCharacter)){
                    palabra += getNextCharacter();
                }
                if(this -> nextCharacter == ' ' || hasFileEnded()){
                    return palabra;
                }
                if(this -> nextCharacter == '.'){
                    file.get(auxCharacter);
                }
                if(!isNumber(auxCharacter)){
                    return palabra;
                }
                    palabra += getNextCharacter();
                while(isNumber(this -> nextCharacter)){
                    palabra += getNextCharacter();
                }
                if(this -> nextCharacter == ' ' || file.eof()){
                    return palabra;
                }
            }
            if((palabra.back() == ' ' || palabra.back() == '\n')&& !hasFileEnded()){
                palabra.clear();
                goto start;
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