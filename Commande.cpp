/*************************************************************************
 Commande  -  description
 -------------------
 début                : 28 nov. 2013
 copyright            : (C) 2013 par Mehdi et Karim
 *************************************************************************/

//---------- Réalisation du namespace <commande> (fichier Commande.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Commande.h"


namespace commande {
    bool checkIfValidNameFile(string s){
        if (s.size() <= 4) {
            return false;
        }
        if(s.substr(s.size()-4,4).compare(".log") ==0 || s.substr(s.size()-4,4).compare(".txt") == 0){
            return true;
        }
        return false;
        
        
    }
    bool checkIfValidDotFile(string s){
        if (s.size() <= 4) {
            return false;
        }
        if(s.substr(s.size()-4,4).compare(".dot") ==0){
            return true;
        }
        return false;
    }
    bool checkIfOption(string s){
        if(s[0]=='-'){
            return true;
        }
        return false;
    }
    
    bool checkIfNeedParam(string arg){
        if(arg.compare("g")==0){
            return true;
        }
        if(arg.compare("l")==0){
            return true;
        }
        if(arg.compare("t")==0){
            return true;
        }
        return false;
    }
    bool checkIfValidParam(string param){
        //si n'a pas la syntaxe d'une option et n'a pa la syntaxe du fichier Log
        return (!checkIfOption(param) && !checkIfValidNameFile(param));
    }
    string getNameOfOption(string s){
        return s.substr(1,s.size());
    }
}

