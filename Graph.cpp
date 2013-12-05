//
//  Graph.cpp
//  tp2
//
//  Created by Mehdi Kitane on 05/12/2013.
//  Copyright (c) 2013 Mehdi Kitane. All rights reserved.
//

#include "Graph.h"

Graph::Graph() {
    optionL=false;
}

void Graph::genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index, string nom){
    
    
    
    
	string phrase = "digraph {\n";
    
    
	for (int i=0; i<index.size(); i++){
        
		ostringstream convert;
        
		convert << "node" << i << " [label=\"" << index.at(i) << "\"];" << endl ;
        
        phrase.append(convert.str());
		/**Methode C++11
         phrase.append("node");
         phrase.append(to_string(i));
         phrase.append(" [label=\"");
         phrase.append(index.at(i));
         phrase.append("\"];\n");
         */
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
            if(nbHitsNoeud<nbHits){
                phrase.append("node");
                
                ostringstream convert;
                convert << it->first << " -> node" << it2->first ;
                convert << " [label=\"" << nbHitsNoeud << "\"];" << endl;
            
                phrase.append(convert.str());
            
            }
            
	    	/*
             //Methode En C++11
             phrase.append(string::to_string(it->first));
             phrase.append(" -> node");
             phrase.append(string::to_string(it2->first));
             phrase.append(" [label=\"");
             phrase.append(string::to_string(sommeTableau(it2->second)));
             phrase.append("\"];\n");
             */
	    }
        
    }
    
    phrase.append("}");
    cout << phrase << endl;
    
    
    ofstream theFile;
    theFile.open(nom);
    theFile << phrase;
    theFile.close();
    
    //system("dot -Tpng -o /Users/Mehdi/Library/Developer/Xcode/DerivedData/tp2-fztozmejudkrvqajmwpxaylckvqo/Build/Products/Debug/nomfichier.png /Users/Mehdi/Library/Developer/Xcode/DerivedData/tp2-fztozmejudkrvqajmwpxaylckvqo/Build/Products/Debug/nomFichier.dot");
}

int Graph::sommeTableau(int tab[]){
	int somme = 0;
    
	for(int i=0;i< 24; i++){
		somme += tab[i] ;
	}
    
	return somme;
}

void Graph::activerOptionL(int nb){
    optionL=true;
    nbHits=nb;
}

