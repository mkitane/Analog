//
//  Commande.cpp
//  tp2
//
//  Created by Mehdi Kitane on 12/12/2013.
//  Copyright (c) 2013 Mehdi Kitane. All rights reserved.
//

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

