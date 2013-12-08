//
//  log.cpp
//  TP2
//
//  Created by Karim Benhmida on 22/11/2013.
//  Copyright (c) 2013 Karim Benhmida. All rights reserved.
//

#include "log.h"

log::log() {
    optionX=false;
    optionT=false;
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
                *heure = (int)strtol(ligne.substr(i+1,2).c_str(),&end,10);
                
                //cout<<"Lheure " << *heure<<endl;
            }
        }
        if(ligne.at(i) == '"' && nombreOccurenceGuillemets==0 ){
			int debut =(int)i ; //initilisation pour eviter erreurs
			int fin = (int)ligne.length(); //initilisation pour eviter erreurs
            
            
            
			//On cherche le / symbolisant le debut de ladresse
			for(size_t j=i; j<ligne.length();j++){
				if(ligne.at(j) == '/'){
					debut = (int)j;
                    
					//on cherche lespace symbolisant la fin de ladresse
					for(size_t k=j; k<ligne.length();k++){
						if(ligne.at(k) == ' '){
							fin = (int)k;
                            
                            
							//On cherche les guillemets fermants
							i=chercherGuillemetsFermants(ligne,(int)k)+1;
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
            int debutRef=(int)i+1;
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
			return (int)i;
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

    
    if(file.is_open()){
    while(getline(file, temp)) {
        analyseLigne(temp, &cible, &referer, &heure);
        switch (1*optionT + 10*optionX) {
            case 0:
                //Aucune des deux options n'est activee
                remplir(cible, referer, heure);
                break;
            case 1:
                //OptionTSeulement activee
                if(heure == optionHeure) {
                    remplir(cible, referer, heure);
                }
                break;
            case 10:
                //OptionX Seulement Activee
                if(isAsset(cible) == false) {
                    remplir(cible, referer, heure);
                }
                break;
            case 11:
                //OptionX et T activee
                if(isAsset(cible) == false && heure==optionHeure) {
                    remplir(cible, referer, heure);
                }
                break;
            default:
                break;
            }
        }
        file.close();
    }else{
        cout<< "Impossible d'ouvrir le fichier" << s <<endl;
    }
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
        if(refExists==true && cibExists==true){
            break;
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
    
    
    structure[cibIndex][refIndex].tab[heure]++;
    
}

void log::testStructure() {
    
    for(int i = 0; i < referencesTab.size(); i++) {
      //  cout << referencesTab[i] << endl;
    }
    


    map<size_t, map<size_t, tabHeure> >::iterator iter1;
    for (iter1 = structure.begin(); iter1 != structure.end(); iter1++)
    {
        cout << "Cible: " << referencesTab[iter1->first] << endl << "Referers:" << endl << endl;
        map<size_t, tabHeure>::iterator iter2;
        for (iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++) {
            cout << "          Referer: " << referencesTab[iter2->first] << endl << "          Hits: ";
            for(int i = 0; i < 24; i++) {
                //  cout << referencesTab[i] << endl;
                cout << structure[iter1->first][iter2->first].tab[i] << " ";
            }
            cout << endl << endl;
        }
        cout << endl << endl << endl;
    }
    
}


void log::afficherDix(){

    vector< vector<int> > top10;
    map<size_t, map<size_t, tabHeure> >::iterator it1; //Iterateur sur la structure
    int i = 1;
   // int ttlHits = 0;
    for (it1 = structure.begin(); it1 != structure.end(); it1++)
    {
        int nbHits = 0;
        map<size_t, tabHeure>::iterator it2;
        for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
            
            if(optionT==true) {
                nbHits+=structure[it1->first][it2->first].tab[optionHeure];
            }
            else {
                for(int i = 0; i < 24; i++) {
                    nbHits+=structure[it1->first][it2->first].tab[i];
                    //   ttlHits+=structure[it1->first][it2->first].tab[i];
                }
            }
            
            // Detection de la dernière iteration sur la même cible
            map<size_t, tabHeure>::iterator final_iter = it1->second.end();
            --final_iter;
            if (it2 == final_iter) {
                
                if(i<=10) {
                    vector<int> monvect;
                    monvect.push_back((int)it1->first);
                    monvect.push_back(nbHits);
                    
                    top10.push_back(monvect);
                    
                    sort(top10.begin(), top10.end(), [](const std::vector< int >& a, const std::vector< int >& b){
                        return a[1] > b[1]; } );
                }
                else if (nbHits>top10.back()[1]) {
                    top10.back()[0] = (int)it1->first;
                    top10.back()[1] = nbHits;
                    sort(top10.begin(), top10.end(), [](const std::vector< int >& a, const std::vector< int >& b){
                        return a[1] > b[1]; } );
                }
                
            }
            
        }
        i++;
    }
    
    vector< vector<int> >::iterator top10it;
    
    for (top10it = top10.begin(); top10it < top10.end(); top10it++) {
        cout << referencesTab[top10[top10it-top10.begin()][0]] << " : " << top10[top10it-top10.begin()][1] << endl;
    }
  /*
   
   // OLD VERSION - not working properly
   
    for(int i=0; i<10; i++) {
        cout << referencesTab[top10[i][0]] << " : " << top10[i][1] << endl;
    }
   */
}



void log::activerOptionX(){
    optionX=true;
}

void log::activerOptionT(int h){
    optionT=true;
    optionHeure = h;
}

bool log::isAsset(string s){
    
    string extension;
    for (size_t i=(s.length()-1); i>0 ; i--){
        if(s.at(i) == '.'){
            extension=s.substr(i+1, s.length()-i );
            break;
        }
    }
    
    string extensionAchercher = "css|js|jpg|jpeg|gif|png|ico";  //Pour ne pas ecrire un if super long
    
    //si == npos , il n'a pa trouve lextension
    if(extensionAchercher.find(extension) != std::string::npos){
        return true;
    }else{
        return false;
    }
    
}












