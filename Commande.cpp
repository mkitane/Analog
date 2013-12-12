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
    bool checkIfValidNameFile(string s)
    // Algorithme :
    // Si taille du string inférieur à 4
    //      Retourne faux
    // Fin si
    // Si le string finit par .log ou par .txt
    //      Retourne vrai
    // Fin si
    //
    // Retourne faux
    {
        if (s.size() <= 4) {
            return false;
        }
        if(s.substr(s.size()-4,4).compare(".log") ==0 || s.substr(s.size()-4,4).compare(".txt") == 0){
            return true;
        }
        return false;
        
        
    }
    bool checkIfValidDotFile(string s)
    // Algorithme :
    // Si taille du string inférieur à 4
    //      Retourne faux
    // Fin si
    // Si le string finit par .dot
    //      Retourne vrai
    // Fin si
    //
    // Retourne faux
    {
        if (s.size() <= 4) {
            return false;
        }
        if(s.substr(s.size()-4,4).compare(".dot") ==0){
            return true;
        }
        return false;
    }
    bool checkIfOption(string s)
    // Algorithme :
    // Si le string commence par un tiret
    //      Retourne vrai
    // Sinon
    //      Retourne faux
    //  Fin si
    {
        if(s[0]=='-'){
            return true;
        }
        return false;
    }
    
    bool checkIfNeedParam(string arg)
    // Algorithme :
    // Si le string est egal à 'g'
    //      Retourne vrai
    // Fin si
    // Si le string est egal à 'l'
    //      Retourne vrai
    // Fin si
    // Si le string est egal à 't'
    //      Retourne vrai
    // Fin si
    // Retourne faux sinon
    {
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
    bool checkIfValidParam(string param)
    // Algorithme :
    // Si le param de l'option n'a pas la syntaxe d'une option et n'a pa la syntaxe du fichier Log
    // Fin si
    {
        //si n'a pas la syntaxe d'une option et n'a pa la syntaxe du fichier Log
        return (!checkIfOption(param) && !checkIfValidNameFile(param));
    }
    string getNameOfOption(string s)
    // Algorithme :
    // Retourner de la seconde à la derniere lettre de s
    {
        return s.substr(1,s.size());
    }
} //Fin du namespace commande

