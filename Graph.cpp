/*************************************************************************
 Graph  -  description
 -------------------
 début                : 1 déc. 2013
 copyright            : (C) 2013 par Mehdi
 *************************************************************************/

//---------- Réalisation de la classe <Graph> (fichier Graph.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>

using namespace std;

//------------------------------------------------------ Include personnel
#include "Graph.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Graph::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
void Graph::genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index){
    
    
    //On a choisit de faire deux methodes differentes pour generer le graph avec ou sans loption
    //car la methode sans option est plus optimisée, (ne check pas des trucs inutiles) et donc
    //plus optimisee pour la recherche sans optionL, mais ne convient pas pour la methode avec optionL
    if(optionL==true){
        digraph = genereGraphVizAvecOptionL(arbre, index);
    }else{
        digraph = genereGraphVizSansOptionL(arbre,index);
    }
    
    //system("dot -Tpng -o /Users/Mehdi/Library/Developer/Xcode/DerivedData/tp2-fztozmejudkrvqajmwpxaylckvqo/Build/Products/Debug/nomfichier.png /Users/Mehdi/Library/Developer/Xcode/DerivedData/tp2-fztozmejudkrvqajmwpxaylckvqo/Build/Products/Debug/nomFichier.dot");
}




// type Graph::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
void Graph::ecrireGraph(){
    ofstream theFile;
    theFile.open(nomFichier);
    theFile << digraph;
    theFile.close();
}

// type Graph::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
void Graph::afficherGraph(){
    cout<<digraph<<endl;
}


// type Graph::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode
void Graph::activerOptionL(int nb){
    optionL=true;
    nbHits=nb;
}





//------------------------------------------------- Surcharge d'opérateurs
/*
Graph & Graph::operator = ( const Graph & unGraph )
// Algorithme :
//
{
} //----- Fin de operator =
*/

//-------------------------------------------- Constructeurs - destructeur
Graph::Graph ( const Graph & unGraph )
// Algorithme :
//
{
    optionL=false;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Graph>" << endl;
#endif
} //----- Fin de Graph (constructeur de copie)


Graph::Graph (string nmFichier )
// Algorithme :
//
{
    nomFichier = nmFichier;
#ifdef MAP
    cout << "Appel au constructeur de <Graph>" << endl;
#endif
} //----- Fin de Graph


Graph::~Graph ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Graph>" << endl;
#endif
} //----- Fin de ~Graph


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

int Graph::sommeTableau(int tab[]){
	int somme = 0;
    
	for(int i=0;i< 24; i++){
		somme += tab[i] ;
	}
    
	return somme;
}


string Graph::genereGraphVizAvecOptionL(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index){
    string phrase = "digraph {\n";
    string noeuds;
    string arcs;
    
    unordered_set<int> noeudsAjoutes;
    
    map<size_t, map<size_t,tabHeure> >::iterator it; //Création d'un itérator sur le 'map'
    
    for(it = arbre.begin(); it != arbre.end(); it++)
    {
	    //int id = it->first;
	    map<size_t,tabHeure> sousarbre = it->second;
        
	    map<size_t,tabHeure>::iterator it2;
        
	    for( it2 = sousarbre.begin(); it2 != sousarbre.end() ; it2++){
            int nbHitsNoeud = sommeTableau((it2->second).tab) ;
            if(nbHitsNoeud>nbHits){
                //Si le noeud ou la cible n'ont pas deja ete ajoute dans mon tableau noeudAjoute
                //On les rajoute!
                if(noeudsAjoutes.find((int)it2->first) == noeudsAjoutes.end()){
                    noeudsAjoutes.insert((int)it2->first);
                    //Ecriture dans la partie noeuds
                    //Pour la cible
                    //On verifie si la cible na pa deja ete ajoutee au tableau noeudAjoute
                    ostringstream convert0;
                    convert0 << "node" << it2->first << " [label=\"" << index.at(it2->first) << "\"];" << endl ;
                    noeuds.append(convert0.str());
                }
                
                if(noeudsAjoutes.find((int)it->first) == noeudsAjoutes.end()){
                    noeudsAjoutes.insert((int)it->first);
                    //pour le ref
                    //On verifie si le ref na pa deja ete ajoutee au tableau noeudAjoute
                    ostringstream convert1;
                    convert1 << "node" << it->first << " [label=\"" << index.at(it->first) << "\"];" << endl ;
                    noeuds.append(convert1.str());
                }
                
                
                
                
                
                
                //Ecriture dans la partie Arcs
                arcs.append("node");
                
                ostringstream convert2;
                //On change lequel en premier vu que la struc a change
                convert2 << it2->first << " -> node" << it->first ;
                convert2 << " [label=\"" << nbHitsNoeud << "\"];" << endl;
                
                arcs.append(convert2.str());
                
            }
            
        }
        
        
    }
    
    
    
    phrase.append(noeuds);
    phrase.append(arcs);
    phrase.append("}");
    
    return phrase;
}

string Graph::genereGraphVizSansOptionL(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index){

    string phrase = "digraph {\n";
    
    
	for (int i=0; i<index.size(); i++){
        
		ostringstream convert;
        
		convert << "node" << i << " [label=\"" << index.at(i) << "\"];" << endl ;
        
        phrase.append(convert.str());
         //Methode C++11
         //phrase.append("node");
         //phrase.append(to_string(i));
         //phrase.append(" [label=\"");
         //phrase.append(index.at(i));
         //phrase.append("\"];\n");
        
	}
    
    
    
    
    
    map<size_t, map<size_t,tabHeure> >::iterator it; //Création d'un itérator sur le 'map'
    
    for(it = arbre.begin(); it != arbre.end(); it++)
    {
	    //int id = it->first;
	    map<size_t,tabHeure> sousarbre = it->second;
        
	    map<size_t,tabHeure>::iterator it2;
        
	    for( it2 = sousarbre.begin(); it2 != sousarbre.end() ; it2++){
            
            // rajouter
            //int nb
            //verifier si superieur a celui du nbhits
            //
            //Que faire si les deux arcs sont supprimés?
            int nbHitsNoeud = sommeTableau((it2->second).tab) ;
                if(nbHitsNoeud>nbHits){
                    phrase.append("node");
                    
                    ostringstream convert;
                    //On change lequel en premier vu que la struc a change
                    convert << it2->first << " -> node" << it->first ;
                    convert << " [label=\"" << nbHitsNoeud << "\"];" << endl;
                    
                    phrase.append(convert.str());
                    
                }
    
             //Methode En C++11
             //phrase.append(string::to_string(it->first));
             //phrase.append(" -> node");
             //phrase.append(string::to_string(it2->first));
             //phrase.append(" [label=\"");
             //phrase.append(string::to_string(sommeTableau(it2->second)));
             //phrase.append("\"];\n");
            
	    }
        
    }
    
    phrase.append("}");
    //cout << phrase << endl;
    
    
    //digraph(phrase);
    
    return phrase;
    

    
}