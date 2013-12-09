/*************************************************************************
 log  -  description
 -------------------
 début                : 28 nov. 2013
 copyright            : (C) 2013 par Mehdi et Karim
 *************************************************************************/

//---------- Réalisation de la classe <log> (fichier log.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <sstream>      // std::ostringstream
#include <stdlib.h>     /* strtol */

//------------------------------------------------------ Include personnel
#include "log.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void log::lire(string s)
// Algorithme :
/*
chaine cible, referer
entier heure
 
ouvrirfichier(addresse du fichier)
 
Si(le fichier est lu)
    tant que (il reste des lignes dans le fichier)
        AnalyserLaLigne(ligne actuelle, &cible, &referer, &heure)
 
        Si(option t active)
            Si(heure = heureoption)
                Remplir(cible, referer, heure)
            fin Si
        Sinon Si(option x active)
            Si(extension de cible autorisee)
                Remplir(cible, referer, heure)
            fin Si
        Sinon Si(option x et t actives)
            Si(extension de cible autorisee ET heure = heureoption)
                Remplir(cible, referer, heure)
            fin Si
        Sinon
            Remplir(cible, referer, heure)
        fin Si
    fin Tant que
 
    fermerfichier()

Sinon
    cerr : "Impossible de lire le fichier"


*/
{
    
    string cible;
    string referer;
    int heure;
    
    if(s != "") {
        
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
        }
        else
        {
            cerr<< "Impossible d'ouvrir le fichier" << s <<endl;
        }

        
    }
    
} //----- Fin de lire

void log::testStructure()
// Algorithme :
//
{
    
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
    
} //----- Fin de testStructure

void log::afficherDix()
// Algorithme :
/*

tableau[ tableau[2] ] top10
 
tant que(il reste des cibles dans structure)
    nombreDeHits = 0 // nombre de hits pour la cible en cours
    tant que (il reste des referers pour cette cible)
        Si(option t active)
            nombreDeHits = Structure[cibleActuelle][refererActuel].tableauHeures[heureOptionT]
        Sinon
            Tant que (il reste des cases dans le tableau d'heures)
                nombreDeHits = Structure[cibleActuelle][refererActuel].tableauHeures[i] // i variable d'incrementation
            Fin tant que
        Fin Si
 
        Si(dernier referer de la cible en cours)
 
            Si(cible est parmis les 10 premieres de la structure)
                AjouterATop10(indexCible, nombreDeHits) // Ajoute a la fin
                OrganiserParOrdreDESC(top10)
            Sinon si (nombreDeHits > top10.dernierElement)
                SupprimerElement(top10)
                AjouterATop10(indexCible, nombreDeHits)
                OrganiserParOrdreDESC(top10)
            Fin Si
 
        Fin Si
    Fin Tant que
Fin tant que
 
AfficherTop10()
 
*/
{
    
    vector< vector<int> > top10;
    map<size_t, map<size_t, tabHeure> >::iterator it1; //Iterateur sur la structure
    int i = 1;
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
    
} //----- Fin de afficherDix

void log::activerOptionX()
// Algorithme :
//
{
    optionX=true;
} //----- Fin de activerOptionX

void log::activerOptionT(int h)
// Algorithme :
//
{
    optionT=true;
    optionHeure = h;
} //----- Fin de activerOptionT

bool log::isAsset(string s)
// Algorithme :
//
{
    
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
    
    
} //----- Fin de isAsset

map< size_t, map < size_t, tabHeure> > log::getStructure() const
// Algorithme :
//
{
    return structure;
} //----- Fin de getStructure

vector<string> log::getReferencesTab() const
// Algorithme :
//
{
    return referencesTab;
} //----- Fin de getReferencesTab

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
log::log()
// Algorithme :
//
{
    optionX=false;
    optionT=false;
} //----- Fin de log

log::~log ( )
// Algorithme :
//
{
    
} //----- Fin de ~log


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
bool log::analyseLigne (string ligne, string *cible, string *referer, int *heure)
// Algorithme :
/*

chaine urlLocale "http://intranet-if.insa-lyon.fr"

entier = nombreOccurenceGuillemets = 0
 
tant que (il reste des caracteres dans la ligne a analyser)
    si(caractere(i) = ":")
        si((i+2) < taillede urlLocale)
            *heure = (int)StringToLong(TronquerLigne(i+1,i+2)
 
 
 
*/
{
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
} // ----- Fin de analyseLigne

int log::chercherGuillemetsFermants(string l, int posDebut)
// Algorithme :
//
{
    for( size_t i=posDebut; i<l.length();i++){
        if(l.at(i)== '"'){
            return (int)i;
        }
    }
    return -1;
} // ----- Fin de chercherGuillemetsFermants

void log::remplir(string cible, string referer, int heure)
// Algorithme :
/*
 entier refIndex = cibIndex = 0
 Tant que(il reste des elements dans l'index)
 Si(referer existe deja dans l'index)
 refIndex = i // i variable d'incrementation de la boucle
 fin Si
 Si(cible existe deja dans l'index)
 cibIndex = i
 fin Si
 Si(referer et cible ont ete trouves)
 break
 fin Si
 fin Tant que
 
 Si(referer n'existe pas dans l'index)
 insererDansIndex(referer)
 refIndex=index.last
 fin Si
 
 Si(cible n'existe pas dans l'index)
 insererDansIndex(cible)
 refCible=index.last
 fin Si
 
 InsererDansMap(cle : cibIndex, InsererDansMap(cle : refIndex, tableauHeures[heure]++))
 
 */
{
    
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
    
} //----- Fin de remplir
