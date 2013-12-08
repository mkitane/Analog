/*************************************************************************
 log  -  description
 -------------------
 début                : 28 oct. 2013
 copyright            : (C) 2013 par Mehdi
 *************************************************************************/

//---------- Interface de la classe <log> (fichier log.h) ------
#if ! defined ( __TP2__log__)
#define __TP2__log__

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include <map>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <log>
//
//
//------------------------------------------------------------------------
struct tabHeure {
    int tab[24] = {0};
};

class log
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- Méthodes publiques
    bool analyseLigne(string ligne, string *cible, string *referer, int *heure);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    int chercherGuillemetsFermants(string l, int posDebut);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void lire(string s);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void remplir(string cible, string referer, int heure);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void testStructure();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void activerOptionX();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void activerOptionT(int h);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    bool isAsset(string s);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void afficherDix();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    map< size_t, map < size_t, tabHeure> > getStructure() const;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    vector<string> getReferencesTab() const;
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    
    //------------------------------------------------- Surcharge d'opérateurs
    
    //-------------------------------------------- Constructeurs - destructeur
    log(const log & unlog);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //
    
    log();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    virtual ~log ();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    //------------------------------------------------------------------ PRIVE
    
protected:
    //----------------------------------------------------- Méthodes protégées
    
    //----------------------------------------------------- Attributs protégés
    bool optionX;
    bool optionT;
    int optionHeure;
    
    vector<string> referencesTab;
    vector<int> referencesHits;
    map< size_t, map < size_t, tabHeure> > structure;
};

//--------------------------- Autres définitions dépendantes de <log>

#endif // __TP2__log__