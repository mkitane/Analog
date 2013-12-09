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
#include "log.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types



//------------------------------------------------------------------------
// Rôle de la classe <Graph>
//
//
//------------------------------------------------------------------------

class Graph
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index);
    
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void ecrireGraph();
    
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void afficherGraph();
    
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //
    void activerOptionL(int nb);


    
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

    //----------------------------------------------------- Attributs protégés
    string nomFichier;
    string digraph;
    int nbHits;
    bool optionL;
};

//--------------------------- Autres définitions dépendantes de <Graph>

#endif // GRAPH_H_
