//============================================================================
// Name        : tp2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

bool analyseLigne (string ligne, string *cible, string *referer, int *heure);
int chercherGuillemetsFermants(string l, int posDebut);

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
	/*
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
	*/
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


bool analyseLigne (string ligne, string *cible, string *referer, int *heure){
//bool analyseLigne(){
	static string urlLocale = "http://intranet-if.insa-lyon.fr";
	static int sizeUrlLocale = urlLocale.length();

	//cout<< UrlLocale << endl;
	//cout << SizeUrlLocale << endl;

	int nombreOccurenceGuillemets = 0;

	for(int i=0; i< ligne.length() ; i++){
		 if( ligne.at(i) ==':'){
			 if( (i+2)<sizeUrlLocale){
				 char* end;
				 *heure = strtol(ligne.substr(i+1,2).c_str(),&end,10);

				 cout<<"Lheure " << *heure<<endl;
			 }
		 }
		 if(ligne.at(i) == '"' && nombreOccurenceGuillemets==0 ){
			int debut =i ; //initilisation pour eviter erreurs
			int fin = ligne.length(); //initilisation pour eviter erreurs



			//On cherche le / symbolisant le debut de ladresse
			for(int j=i; j<ligne.length();j++){
				if(ligne.at(j) == '/'){
					debut = j;

					//on cherche lespace symbolisant la fin de ladresse
					for(int k=j; k<ligne.length();k++){
						if(ligne.at(k) == ' '){
							fin = k;


							//On cherche les guillemets fermants
							i=chercherGuillemetsFermants(ligne,k)+1;
							if(i!=-1){
								nombreOccurenceGuillemets++;
							}
							break;
						}
					}
					break;
				}
			}

			*cible = ligne.substr(debut,(fin-debut));
			cout<<"la cible est :  "<< *cible <<endl;
		}


		 if(ligne.at(i) == '"' && nombreOccurenceGuillemets==1 ){
			 int debutRef=i+1;
			 int finRef = chercherGuillemetsFermants(ligne,debutRef);
			 nombreOccurenceGuillemets++;

			 string refererProbable = ligne.substr(debutRef,(finRef-debutRef));

			 cout<<"Le Referer Probable est :"<<refererProbable<<endl;
			 if(refererProbable.compare(0,sizeUrlLocale,urlLocale) != 0){
				 //Pas les memes
				 *referer = refererProbable;
			 }else{
				 *referer = refererProbable.substr(sizeUrlLocale,refererProbable.length());
			 }


			 cout<<"le referer est :  "<< *referer <<endl;
		}

	}





	return true;
}


int chercherGuillemetsFermants(string l, int posDebut){
	for( int i=posDebut; i<l.length();i++){
		if(l.at(i)== '"'){
			return i;
		}
	}
	return -1;
}


