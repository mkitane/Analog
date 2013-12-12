/*************************************************************************
 Log  -  description
 -------------------
 début                : 28 nov. 2013
 copyright            : (C) 2013 par Mehdi et Karim
 *************************************************************************/

//---------- Réalisation de la classe <Log> (fichier Log.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <sstream>      // std::ostringstream
#include <stdlib.h>     /* strtol */
#include <algorithm>  //std::sort

//------------------------------------------------------ Include personnel
#include "Log.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void Log::lire()
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
    
    ligneLog l;
    
    if(nomFichier != "") {
        
        ifstream file(nomFichier);
        string temp;
        
        
        if(file.is_open()){
            while(getline(file, temp)) {
                analyseLigne(temp, &l);
                
                switch (1*optionT + 10*optionX) {
                    case 0:
                        //Aucune des deux options n'est activee
                        remplir(l.cible, l.referer, l.heure);
                        break;
                    case 1:
                        //OptionTSeulement activee
                        if(l.heure == optionHeure) {
                            remplir(l.cible, l.referer, l.heure);
                        }
                        break;
                    case 10:
                        //OptionX Seulement Activee
                        if(isAsset(l.cible) == false) {
                            remplir(l.cible, l.referer, l.heure);
                        }
                        break;
                    case 11:
                        //OptionX et T activee
                        if(isAsset(l.cible) == false && l.heure==optionHeure) {
                            remplir(l.cible, l.referer, l.heure);
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
            cerr<< "Impossible d'ouvrir le fichier " << nomFichier <<endl;
            exit(44);
        }

        
    }
    
} //----- Fin de lire

void Log::testStructure()
// Algorithme :
//
{
    
    for(int i = 0; i < (int)referencesTab.size(); i++) {
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

void Log::afficherDix()
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
                    
                    sort(top10.begin(), top10.end(), [=](const std::vector< int >& a, const std::vector< int >& b){
                        return a[1] > b[1]; } );
                }
                else if (nbHits>top10.back()[1]) {
                    top10.back()[0] = (int)it1->first;
                    top10.back()[1] = nbHits;
                    sort(top10.begin(), top10.end(), [=](const std::vector< int >& a, const std::vector< int >& b){
                        return a[1] > b[1]; } );
                }
                
            }
            
        }
        i++;
    }
    
    vector< vector<int> >::iterator top10it;
    
    for (top10it = top10.begin(); top10it < top10.end(); top10it++) {
        cout << referencesTab[top10[top10it-top10.begin()][0]] << " (" << top10[top10it-top10.begin()][1] << " hits)"<< endl;
    }
    
} //----- Fin de afficherDix

void Log::activerOptionX()
// Algorithme :
//
{
    optionX=true;
} //----- Fin de activerOptionX

void Log::activerOptionT(int h)
// Algorithme :
//
{
    optionT=true;
    optionHeure = h;
} //----- Fin de activerOptionT

bool Log::isAsset(string s)
// Algorithme :
//Debut Methode
//  Recupere lextension du string
//  Verifie si elle correspond aux extensions interdites
//Fin Methode
{
    
    string extension;
    for (size_t i=(s.length()-1); i>0 ; i--){
        if(s.at(i) == '.'){
            extension=s.substr(i+1, s.length()-i );
            break;
        }
    }
    
    
    //si == npos , il n'a pa trouve lextension
    if(extensionAchercher.find(extension) != std::string::npos){
        return true;
    }else{
        return false;
    }
    
    
} //----- Fin de isAsset

map< size_t, map < size_t, tabHeure> > Log::getStructure() const
// Algorithme :
//
{
    return structure;
} //----- Fin de getStructure

vector<string> Log::getReferencesTab() const
// Algorithme :
//
{
    return referencesTab;
} //----- Fin de getReferencesTab

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
Log::Log( string nmFichier)
// Algorithme :
//
{
    nomFichier=nmFichier; 
    optionX=false;
    optionT=false;
#ifdef MAP
    cout << "Appel au constructeur de <Log>" << endl;
#endif
} //----- Fin de Log

Log::Log(const Log & unLog)
{
    nomFichier=unLog.nomFichier;
    optionT=unLog.optionT;
    optionX=unLog.optionX;
    optionHeure=unLog.optionHeure;
    structure = unLog.structure;
    referencesTab = unLog.referencesTab;
#ifdef MAP
    cout << "Appel au constructeur de copie de <Log>" << endl;
#endif
}//-- Fin de Log

Log::~Log ( )
// Algorithme :
//
{
    
} //----- Fin de ~Log


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
bool Log::analyseLigne (string ligne, ligneLog *l)
// Algorithme :
//
//
//Chaine urlLocale "http://intranet-if.insa-lyon.fr"
//
//entier = nombreOccurenceGuillemets = 0
//
//Tant que (il reste des caracteres dans la ligne a analyser)
//      Si caractere(i)==':' et heure n'a pas encore ete trouvee
//          heure = sousstring(i+1 jusqua i+2);  // On recupere les deux prochains caracteres
//      Fin si
//
//      Si caractere(i)=' " ' et PremiereOccurenceGuillemet
//          int debutCible = PremiereOccurenceDeLespace
//          int finCible = DeuxiemeOccurenceDeLespace
//          cible = soustring debutCible jusqua finCible
//      FinSi
//
//      Si caractere(i) = ' " ' et DeuxiemeOccurenceGuillemet
//          int debutCible = TroisiemeOccurenceGuillemets
//          int finCible = QuatriemeOccurenceGuillemets
//          referer = sousstring (i+1 jusqua finCible)
//
//          Si referer contient la baseUrl
//              referer= referer-baseUrl
//          FinSI
//      FinSi
//FinTantQue
//
//
//FinMethode
{
    

    
    //cout<< UrlLocale << endl;
    //cout << SizeUrlLocale << endl;
    

    size_t longueur = ligne.length();
    char* end;

    
    int finAdresseIp = chercherChar(ligne,longueur, 0, sepEspace);
    
    int debutDate = chercherChar(ligne, longueur, finAdresseIp, sepCrochetOuvrant)+1;
    int debutHeure = chercherChar(ligne,longueur, debutDate, sepPointPoint)  +1;
    int finDate = chercherChar(ligne, longueur, debutHeure, sepCrochetFermant);
    
    

    
    int debutTypeAction = chercherChar(ligne, longueur, debutHeure, sepGuillemets)  +1;
    int finTypeAction = chercherChar(ligne, longueur, debutTypeAction, sepEspace);
    
    int debutCible = chercherChar(ligne, longueur, finTypeAction, sepEspace) +1;
    int finCible = chercherChar(ligne, longueur, debutCible, sepEspace);
    int finGuillemetsCible = chercherChar(ligne, longueur, finCible,sepGuillemets)+1;

    
    int debutReturnCode = finGuillemetsCible+1;
    int finReturnCode = chercherChar(ligne, longueur, debutReturnCode+1, sepEspace);
    
    
    int debutReferer = chercherChar(ligne,longueur, finReturnCode, sepGuillemets) + 1;
    int finReferer = chercherChar(ligne,longueur, debutReferer,sepGuillemets);
    
    
    l->date=ligne.substr(debutDate, finDate-debutDate );
    l->heure = (int)strtol(ligne.substr(debutHeure,2).c_str(),&end,10);
    l->adresseIP=ligne.substr(0,finAdresseIp);
    l->typeAction=ligne.substr(debutTypeAction,finTypeAction-debutTypeAction );
    l->returnCode=(int)strtol(ligne.substr(debutReturnCode,finReturnCode-debutReturnCode ).c_str(), &end,10);
    l->cible = ligne.substr(debutCible,finCible-debutCible );
    

    /*
    int debutHeure = chercherChar(ligne,longueur, finAdresseIp, sepPointPoint)+1;
    char* end;
    l->heure = (int)strtol(ligne.substr(debutHeure,2).c_str(),&end,10);
    
    

    int debutCible = chercherChar(ligne, longueur, debutHeure+2 ,sepGuillemets) + 1;
    debutCible = chercherChar(ligne, longueur, debutCible, sepEspace)+1;
    int finCible = chercherChar(ligne, longueur, debutCible, sepEspace);
    int finGuillemetsCible = chercherChar(ligne, longueur, debutCible,sepGuillemets)+1;

    
    
    l->cible = ligne.substr(debutCible,(finCible-debutCible));

    */
    
    
    
    //PartieReferer
    string refererProbable = ligne.substr(debutReferer,(finReferer-debutReferer));
    
    if(refererProbable.compare(0,sizeUrlLocale,urlLocale) != 0){
        l->referer = refererProbable;
    }else{
        l->referer = refererProbable.substr(sizeUrlLocale,refererProbable.length());
    }

    /*
    cout<<"------------"<<endl;
    cout<<l->date<<endl;
    cout<<l->heure<<endl;
    cout<<l->adresseIP<<endl;
    cout<<l->typeAction<<endl;
    cout<<l->returnCode<<endl;
    cout<<l->cible<<endl;
    cout<<l->referer<<endl;
    cout<<"------------"<<endl;
    */
    
    return true;
    
}



int Log::chercherChar(string l, size_t longueur, int posDebut, char separateur)
// Algorithme :
//
{
    for( size_t i=posDebut; i<longueur;i++){
        if(l.at(i)== separateur){
            return (int)i;
        }
    }
    return -1;
} // ----- Fin de chercherGuillemetsFermants

void Log::remplir(string cible, string referer, int heure)
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
