//============================================================================
// Name        : tp2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
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
	bool argg=false;
	bool argl=false;
	bool argx=false;
	bool argt=false;

	for(int i=1; argv[i] ;i++){

		if(argv[i] == "-g"){
			argg=true;
			nomGraph = argv[i+1];
			i++;
		}

		if(argv[i] == "-l"){
			argl=true;
			nbHits = argv[i+1];
			i++;
		}

		if(argv[i] == "-x"){
			argx=true;
		}

		if(argv[i] == "-t"){
			argt=true;
			heure = argv[i+1];
			i++;
		}

		if(i == (argc-1)){
			nomFichier = argv[i];
		}
	}
	return 0;
}

