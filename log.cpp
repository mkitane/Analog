//
//  log.cpp
//  TP2
//
//  Created by Karim Benhmida on 22/11/2013.
//  Copyright (c) 2013 Karim Benhmida. All rights reserved.
//

#include "log.h"

log::log() {
    
}

bool log::analyseLigne (string ligne, string *cible, string *referer, int *heure){
    //bool analyseLigne(){
	static string urlLocale = "http://intranet-if.insa-lyon.fr";
	static size_t sizeUrlLocale = urlLocale.length();
    
	//cout<< UrlLocale << endl;
	//cout << SizeUrlLocale << endl;
    
	int nombreOccurenceGuillemets = 0;
    
	for(size_t i=0; i< ligne.length() ; i++){
        if( ligne.at(i) ==':'){
            if( (i+2)<sizeUrlLocale){
                char* end;
                *heure = strtol(ligne.substr(i+1,2).c_str(),&end,10);
                
                //cout<<"Lheure " << *heure<<endl;
            }
        }
        if(ligne.at(i) == '"' && nombreOccurenceGuillemets==0 ){
			int debut =i ; //initilisation pour eviter erreurs
			int fin = ligne.length(); //initilisation pour eviter erreurs
            
            
            
			//On cherche le / symbolisant le debut de ladresse
			for(size_t j=i; j<ligne.length();j++){
				if(ligne.at(j) == '/'){
					debut = j;
                    
					//on cherche lespace symbolisant la fin de ladresse
					for(size_t k=j; k<ligne.length();k++){
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
			//cout<<"la cible est :  "<< *cible <<endl;
		}
        
        
        if(ligne.at(i) == '"' && nombreOccurenceGuillemets==1 ){
            int debutRef=i+1;
            int finRef = chercherGuillemetsFermants(ligne,debutRef);
            nombreOccurenceGuillemets++;
            
            string refererProbable = ligne.substr(debutRef,(finRef-debutRef));
            
            //cout<<"Le Referer Probable est :"<<refererProbable<<endl;
            if(refererProbable.compare(0,sizeUrlLocale,urlLocale) != 0){
                //Pas les memes
                *referer = refererProbable;
            }else{
                *referer = refererProbable.substr(sizeUrlLocale,refererProbable.length());
            }
            
            
            //cout<<"le referer est :  "<< *referer <<endl;
		}
        
	}
    
    
    
    
    
	return true;
}

int log::chercherGuillemetsFermants(string l, int posDebut){
	for( size_t i=posDebut; i<l.length();i++){
		if(l.at(i)== '"'){
			return i;
		}
	}
	return -1;
}

void log::lire(string s) {
    
    string cible;
    string referer;
    int heure;
    
    ifstream file(s);
    string temp;

    while(getline(file, temp)) {
        analyseLigne(temp, &cible, &referer, &heure);
        remplir(cible, referer, heure);
    }

    
    file.close();
}

void log::remplir(string cible, string referer, int heure) {
    
    size_t refIndex = 0;
    size_t cibIndex = 0;
    
    // On vérifie si le referer et la cible sont déjà referencés, si oui on récupere l'index
    
    bool refExists = false;
    bool cibExists = false;
    
    for(size_t i = 0; i < referencesTab.size(); i++) {
       // cout << i << endl;
        if(referer == referencesTab[i]) {
            refExists = true;
            refIndex = i;
        }
        if(cible == referencesTab[i]) {
            cibExists = true;
            cibIndex = i;
        }
    }
    
    // Sinon on reference referer et cible et on recupere l'index
    
    if(refExists == false) {
        referencesTab.push_back(referer);
        //cout << referencesTab.size() ;
        refIndex = referencesTab.size()-1;
    }
    if(cibExists == false) {
        referencesTab.push_back(cible);
        cibIndex = referencesTab.size()-1;
    }
    
    
    structure[refIndex][cibIndex].tab[heure]++;
    
}

void log::testStructure() {
    
    //cout << referencesTab.size() << endl;
    for(int i = 0; i < referencesTab.size(); i++) {
      //  cout << referencesTab[i] << endl;
    }
    


    map<size_t, map<size_t, tabHeure> >::iterator iter1;
    for (iter1 = structure.begin(); iter1 != structure.end(); iter1++)
    {
        cout << "referer: " << referencesTab[iter1->first] << endl << "Cibles:" << endl << endl;
        map<size_t, tabHeure>::iterator iter2;
        for (iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
            cout << "          Cible: " << referencesTab[iter2->first] << endl << "          Hits: ";
            for(int i = 0; i < 24; i++) {
                //  cout << referencesTab[i] << endl;
                cout << structure[iter1->first][iter2->first].tab[i] << " ";
            }
            cout << endl << endl;
        }
        cout << endl << endl << endl;
    }
    
}





void log::genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index){
    
    
    
    
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
	    	phrase.append("node");
            
	    	ostringstream convert;
	    	convert << it->first << " -> node" << it2->first ;
	    	convert << " [label=\"" << sommeTableau((it2->second).tab) << "\"];" << endl;
            
	    	phrase.append(convert.str());
            
            
            
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
    theFile.open("/Users/Mehdi/Desktop/court.dot");
    theFile << phrase;
    theFile.close();
    
    //system("dot -Tpng -o /Users/Mehdi/Desktop/court.png /Users/Mehdi/Desktop/court.dot");
}

int log::sommeTableau(int tab[]){
	int somme = 0;
    
	for(int i=0;i< 24; i++){
		somme += tab[i] ;
	}
    
	return somme;
}






















