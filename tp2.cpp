//============================================================================
// Name        : tp2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>      // std::ostringstream
#include <stdlib.h>     /* strtol */
#include <ostream>

using namespace std;


bool optionExists(char** debut,char **fin, const string nomOption){
	return  0;
}

string getOption(char** debut,char **fin, const string nomOption){
	//PseudoCode:
	//Aller de debut a fin et chercher l'option, si elle existe
	//et si elle est differente de char fin
	//retourner lelement d'apres
	return "test";
}
//http://stackoverflow.com/questions/865668/parse-command-line-arguments
/*
int main( int argc, char* argv[] ){

	
	string nomFichier;
	string nomGraph;
	int nbHits;
	int heure;

	nomGraph = getOption(argv,argv+argc,"-g");
	//if(nomGraph){
		//Faire fonction qui genere le graphViz
	//}

	nbHits = getOption(argv,argv+argc,"-l");
	if(nbHits){
		//faire fonction
	}

	if( getOption(argv,argv+argc,"-x")){
		//faire fonction -x
	}

	heure = getOption(argv,argv+argc,"-t");
	if( getOption(argv,argv+argc,"-t")){
		//faire fonction ac heure
	}


	//faire default


	


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

	cout << "Il y a " << argc << "arguments" << endl;
	if(argg){
		cout<<"Option -g activee, Il ya bien un graph a creer dans le fichier :" << nomGraph << endl;
	}
	if(argl){
		cout<<"Option -l activee, Le nombre de hits demande est :" << nbHits << endl;
	}
	if(argx){
		cout << "Option -x activee" << endl;
	}
	if(argt){
		cout << "Option -t activee, Intervalle a prendre : " << heure << endl;
	}

	cout << "Le nom du fichier est :" << nomFichier << endl;





	string trucBase = "192.168.0.0 - - [08/Sep/2012:11:16:02 +0200] \"Get /temps/4IF16.html HTTP/1.1\" 200 12106 \"http://intranet-if.insa-lyon.fr/temps/4IF15.html\" MOZILLA";
	string cible ;
	string referer;
	int heure;

	cout<<trucBase<<endl;
	analyseLigne(trucBase,&cible, &referer, &heure);

	cout<<"---------"<<endl;
	cout<<"---------"<<endl;

	trucBase = "192.168.0.0 - - [08/Sep/2012:15:16:02 +0200] \"Get /temps.html HTTP/1.1\" 200 12106 \"http://google.fr/temps/4IF19.html\" MOZILLA";
	cout<<trucBase<<endl;
	analyseLigne(trucBase,&cible, &referer, &heure);

	return 0;
}
*/






