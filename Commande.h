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
    //Vérifie que le nom de fichier inséré à la fin de la commande correspond bien à un fichier .log ou .txt.
    // Contrat :
    //
    
    bool checkIfValidDotFile(string s);
    // Mode d'emploi :
    //Vérifie que le paramètre de l’option -g correspond bien à un fichier .dot.     // Contrat :
    // Contrat :
    //
    
    bool checkIfOption(string s);
    // Mode d'emploi :
    //Vérifie si une chaine de caractère passée en paramètre correspond à une option et récupère le paramètre pour certaines options. Retourne vrai si la chaine de caractères est une option.
    // Contrat :
    //
    
    bool checkIfNeedParam(string arg);
    // Mode d'emploi :
    //Vérifie si une option a besoin d’un paramètre.
    // Contrat :
    //
    
    bool checkIfValidParam(string param);
    // Mode d'emploi :
    //Vérifie si la syntaxe d’un paramètre d'une option est valide, si oui retourne vrai.
    // Contrat :
    // 
    
    string getNameOfOption(string s);
    // Mode d'emploi :
    //Retourne le nom de l’option sans le tiret qui la précède.
    // Contrat :
    // Lui donner un nom commençant avec un tiret, IE c'est bien une option
    
}
#endif /* defined(__tp2__Commande__) */
