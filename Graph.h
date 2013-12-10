/*************************************************************************
Graph  -  description
 -------------------
 début                : 1 déc. 2013
 copyright            : (C) 2013 par Mehdi
 *************************************************************************/

//---------- Interface de la classe <Graph> (fichier Graph.h) ------
#if ! defined ( GRAPH_H_ )
#define GRAPH_H_


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include "Log.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types



//------------------------------------------------------------------------
// Rôle de la classe <Graph>
//Cette classe contient un ensemble de methodes permettant de generer
//Un fichier graph a partir de la structure map et de l'index
//renvoyee par la classe Log
//------------------------------------------------------------------------
//
//------------------------------------------------------------------------

class Graph
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- Méthodes publiques
    void genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index);
    // Mode d'emploi :
    // Genere notre fichier graph et le stocke en memoire
    // Contrat :
    // Donner une structure bien remplie
    
    void ecrireGraph();
    // Mode d'emploi :
    //  Ecrit le contenu du graph dans le fichier specifie dans le constructeur
    // Contrat :
    //  Donner un nom de fichier valide
    
    void afficherGraph();
    // Mode d'emploi :
    //  Affiche le contenu du graph dans le terminal
    // Contrat :
    //
    
    void activerOptionL(int nb);
    // Mode d'emploi :
    //  Rend l'option L active
    //  c'est a dire prise en compte par les autres methodes dans leur execution
    // Contrat :
    //


    
    //------------------------------------------------- Surcharge d'opérateurs
    //Graph & operator = ( const Graph & unGraph );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    
    //-------------------------------------------- Constructeurs - destructeur
    Graph ( const Graph & unGraph );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //
    
    Graph ( string nmFichier );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    virtual ~Graph ( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- Méthodes protégées
    int sommeTableau(int tab[]);
    string genereGraphVizAvecOptionL(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index);
    string genereGraphVizSansOptionL(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index);
    
    //----------------------------------------------------- Attributs protégés
    string nomFichier;
    string digraph;
    int nbHits;
    bool optionL;
};

//--------------------------- Autres définitions dépendantes de <Graph>

#endif // GRAPH_H_
