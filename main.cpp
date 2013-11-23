//
//  main.cpp
//  TP2
//
//  Created by Karim Benhmida on 20/11/2013.
//  Copyright (c) 2013 Karim Benhmida. All rights reserved.
//

#include <iostream>
#include <stdlib.h>     /* strtol */
#include "log.h"
using namespace std;

int main(int argc, const char * argv[])
{
    //METHODE 2
	// VOIR SI IL FAUT GERER LES ERREURS !
	string nomFichier;
	string nomGraph;
	int nbHits;
	int heure;
    
    
	bool argg=false;
	bool argl=false;
	bool argx=false;
	bool argt=false;
    
	for(int i=1; argv[i] ;i++){
		cout<< "argument"<< i << " <"<< argv[i]<<">" << endl;
		if( string(argv[i]).compare("-g") == 0){
			argg=true;
			nomGraph = argv[i+1];
			i++;
		}
        
		if( string(argv[i]).compare("-l") == 0){
			argl=true;
			char* end;
			nbHits = strtol(argv[i+1],&end,10);
			i++;
		}
        
		if( string(argv[i]).compare("-x") == 0){
			argx=true;
		}
        
		if( string(argv[i]).compare("-t") == 0){
			argt=true;
			char* end;
			heure = strtol(argv[i+1],&end,10);
			i++;
		}
        
		if(i == (argc-1)){
			nomFichier = argv[i];
		}
	}
    
    
    
	//faire default
    
	//cout << "Il y a " << argc << "arguments" << endl;

    log monLog;

	if(argl){
		cout<<"Option -l activee, Le nombre de hits demande est :" << nbHits << endl;
        monLog.activerOptionX(); // Agit sur la commande lire
	}
	if(argx){
		cout << "Option -x activee" << endl;
	}
	if(argt){
		cout << "Option -t activee, Intervalle a prendre : " << heure << endl;
	}
    
	//cout << "Le nom du fichier est :" << nomFichier << endl;
    
    
    monLog.lire(nomFichier);
    //monLog.testStructure();
    
    if(argg){
		cout<<"Option -g activee, Il ya bien un graph a creer dans le fichier :" << nomGraph << endl;
        monLog.genereGraphViz(monLog.structure, monLog.referencesTab);
	}
    
    

    return 0;
}

