/*************************************************************************
 Commande  -  description
 -------------------
 début                : 28 oct. 2013
 copyright            : (C) 2013 par Mehdi
 *************************************************************************/

//---------- Interface du namespace <commande> (fichier Commande.h) ------

#ifndef __tp2__Commande__
#define __tp2__Commande__

//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------------------------
// Rôle du namespace <commande>
// Cette classe contient un ensemble de fonction qui aident à l'analyse
// d'une ligne de commande
//------------------------------------------------------------------------

namespace commande{
    //----------------------------------------------------------------- PUBLIC
    bool checkIfValidNameFile(string s);
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    //
    
    bool checkIfValidDotFile(string s);
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // L'adresse du fichier a lire doit être valide
    
    bool checkIfOption(string s);
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // L'adresse du fichier a lire doit être valide
    
    bool checkIfNeedParam(string arg);
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // L'adresse du fichier a lire doit être valide
    
    bool checkIfValidParam(string param);
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // L'adresse du fichier a lire doit être valide
    
    string getNameOfOption(string s);
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // L'adresse du fichier a lire doit être valide
    
}
#endif /* defined(__tp2__Commande__) */
