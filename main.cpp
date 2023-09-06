//Analizador Lexico Fase 1
// Elaborado por:
// Froylan Adair Villegas Castro 2022670123
// Aurelio Flores Nava 2022670038

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

class AnalizadorLexico{
    private:
        char nextCharacter;
        char auxCharacter = 0;
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
    char c = this -> nextCharacter;

    if (auxCharacter != 0){
        this -> nextCharacter = auxCharacter;
        auxCharacter = 0;
        return c;
    }
    
    file.get(this -> nextCharacter);
    return c;

}

string AnalizadorLexico::checkRegularExpresion(){
    string palabra;
    start:
    palabra += getNextCharacter(); 
    //# Palabra Reservada
    if (palabra[0] == '#'){
        if(isUpperCase(nextCharacter)){
            palabra += getNextCharacter();
            while(isLowerCase(nextCharacter)){
                palabra += getNextCharacter();
            }
        }
        goto end;
    }

    //@ identificador
    if(palabra[0] == '@'){
        if(isLowerCase(nextCharacter)){
            while(isLowerCase(nextCharacter)){
                palabra += getNextCharacter();
            }
            while(isNumber(nextCharacter)){
                palabra += getNextCharacter(); 
            }
        }
        goto end;
    }

    //Numeros
    if(isNumber(palabra.back())){ //Numero
        while(isNumber(this -> nextCharacter)){
            palabra += getNextCharacter();
        }

        //Comprobar que despues del punto haya un numero realmente
        if(this -> nextCharacter == '.'){
            file.get(auxCharacter);
            //Si lo que hay despues del punto no es numero, el punto no se añade y se retorna
            //el numero hasta antes de él
            if(!isNumber(auxCharacter)){
                goto end;
            }
        }

        palabra += getNextCharacter();
        while(isNumber(this -> nextCharacter)){
            palabra += getNextCharacter();
        }
        goto end;
    }

    //Eliminar Espacios y saltos de linea
    if((palabra.back() == ' ' || palabra.back() == '\n') && !hasFileEnded()){
        palabra.clear();
        goto start;
    }

    end:
    return palabra;
}

int main(){
    AnalizadorLexico analizador;
    while(!analizador.hasFileEnded()){
    cout << analizador.checkRegularExpresion() << endl;
    }
    return 0;
}  