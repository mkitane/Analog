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

void Graph::genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index)
// Algorithme :
//Verifie si option L est activee et lance la methode de generation du graph adequate
//Stocke le resultat dans la variable de classe digraph
{
    
    
    //On a choisit de faire deux methodes differentes pour generer le graph avec ou sans loption
    //car la methode sans option est plus optimisée, (ne check pas des trucs inutiles) et donc
    //plus optimisee pour la recherche sans optionL, mais ne convient pas pour la methode avec optionL
    if(optionL==true){
        digraph = genereGraphVizAvecOptionL(arbre, index);
    }else{
        digraph = genereGraphVizSansOptionL(arbre,index);
    }

} //----- Fin de Méthode



    
void Graph::ecrireGraph()
// Algorithme :
//
{
    ofstream theFile;
    theFile.open(nomFichier);
    theFile << digraph;
    theFile.close();
}//----- Fin de Méthode


void Graph::afficherGraph()
// Algorithme :
//
{
    cout<<digraph<<endl;
}//----- Fin de Méthode



void Graph::activerOptionL(int nb)
// Algorithme :
//
{
    optionL=true;
    nbHits=nb;
}//----- Fin de Méthode






//------------------------------------------------- Surcharge d'opérateurs
/*
Graph & Graph::operator = ( const Graph & unGraph )
// Algorithme :
//
{
} //----- Fin de operator =
*/

//-------------------------------------------- Constructeurs - destructeur

//A REVOIR !! CONSTRUCTEUR COPIE !
Graph::Graph ( const Graph & unGraph )
// Algorithme :
//
{
    optionL=unGraph.optionL;
    nomFichier = unGraph.nomFichier;
    digraph= unGraph.digraph;
    nbHits=unGraph.nbHits;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Graph>" << endl;
#endif
} //----- Fin de Graph (constructeur de copie)


Graph::Graph (string nmFichier )
// Algorithme :
//
{
	nbHits = -1 ;
    nomFichier = nmFichier;
    optionL=false;
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

int Graph::sommeTableau(int tab[])
// Algorithme :
//Debut Methode
//  entier somme =0
//  Pour tous les elements du tableau
//      ajouter valeur de cet element du tableau a somme
//  Fin Pour
//  Retourner Somme
//Fin Methode
{
	int somme = 0;
    
	for(int i=0;i< 24; i++){
		somme += tab[i] ;
	}
    
	return somme;
}//----- Fin de Méthode



string Graph::genereGraphVizAvecOptionL(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index)
// Algorithme :
//Debut Methode
//  string phrase = "digraph{\n"
//  string noeuds = string arcs = ""
//  set noeudsAjoutes
//
//
//  Pour tous les elements de notre map de cible
//      Pour tous les elements de notre map de referer
//          entier nbClic = On calcule le nombre de clic total pour le couple cible/referer donne
//          Si nbClic > (nombredehits specifie dans la commande)
//              On verifie si la structure noeudAjoute contient la cible
//              Si Oui
//                  Ne rien faire
//              Si non
//                  Ajouter a la structure noeudAjoute la cible
//                  noeud += "node (numeroCibleDansLindex) [label=\ nomCible];
//              FinSi
//
//              On verifie si la structure noeudAjoute contient le referer
//              Si Oui
//                  Ne rien faire
//              Si non
//                  Ajouter a la structure noeudAjoute le referer
//                  noeud += "node (numeroRefererDansLindex) [label=\ nomReferer];
//              FinSi
//
//              arcs += "node (numeroRefererDansLindex) -> node (numeroCibleDansLindex) [label="(nbClic)"];
//          Sinon
//              On ne fait rien
//          FinSi
//      Fin Pour
//  Fin Pour
//
//
//  phrase = phrase + noeuds + arcs + "}"
//  Retourner phrase
//Fin Methode
{
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
}//----- Fin de Méthode


string Graph::genereGraphVizSansOptionL(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index)
// Algorithme :
//Debut Methode
//  string phrase = "digraph {\n";
//  Pour tous les elements de Index
//      phrase = phrase + "node (numero de lelement actuel dans l'index) [label=\"(nomDeLelement)"]; "
//      phrase = phrase + "\" ;
//  Fin Pour
//
// Pour tous les elements de notre map de cible
//      Pour tous les elements de notre map de referer
//          entier nbClic = On calcule le nombre de clic total pour le couple cible/referer donne
//          Si nbClic > (nombredehits specifie dans la commande)
//              phrase += "node (numeroRefererDansLindex) -> node (numeroCibleDansLindex) [label="(nbClic)"];
//          Sinon
//              On ne fait rien
//          FinSi
//      Fin Pour
//  Fin Pour
//
//  phrase = phrase + "}"
//  Retourner phrase
//Fin Methode

{

    string phrase = "digraph {\n";
    
    
	for (int i=0; i<(int)index.size(); i++){
        
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
    

    
}//----- Fin de Méthode
