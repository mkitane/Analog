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
// Cette classe contient un ensemble de methodes permettant de manipuler un fichier .log : le lire, identifier et stocker les informations necessaires dans une structure appropriee
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
    void lire(string s);
    // Mode d'emploi :
    // Permet de lire un fichier .log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // Prend en parametre un string qui contient l'adresse absolue ou relative du fichier a lire. Ne doit pas être vide
    
    void testStructure();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void activerOptionX();
    // Mode d'emploi :
    // Permet d'activer l'option X
    // Contrat :
    // Il suffit d'appeler la methode, aucun parametre à passer
    
    void activerOptionT(int h);
    // Mode d'emploi :
    // Permet d'activer l'option T
    // Contrat :
    // Il suffit d'appeler la methode, aucun parametre à passer
    
    bool isAsset(string s);
    // Mode d'emploi :
    // Detecte si un string contient certains mots predefinis dans la methode et renvoie vrai le cas écheant
    // Contrat :
    // Il faut passer un string (vide ou non) comme parametre
    
    void afficherDix();
    // Mode d'emploi :
    // Affiche sur la sortie standard les 10 (au maximum) pages les plus vues du fichier log analysé
    // Contrat :
    // Il suffit d'appeler la méthode aucun parametre n'est pris en compte
    
    map< size_t, map < size_t, tabHeure> > getStructure() const;
    // Mode d'emploi :
    // Renvoie la structure (access depuis l'exterieur
    // Contrat :
    // Aucun parametre
    
    vector<string> getReferencesTab() const;
    // Mode d'emploi :
    // Renvoie le tableau index
    // Contrat :
    // Pas de parametres
    
    
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
    bool analyseLigne(string ligne, string *cible, string *referer, int *heure);
    // Mode d'emploi :
    // Analyse la ligne passee en parametre a partir de laquelle elle renseigne les variables cible, referer et heure
    // Contrat :
    // ligne doit etre une ligne de log
    
    int chercherGuillemetsFermants(string l, int posDebut);
    // Mode d'emploi :
    // Recherche les guillements fermants dans un string a partir d'une position
    // Contrat :
    // posDebut doit etre positif et inferieur a la taille du string et le string ne doit pas etre vide
    
    void remplir(string cible, string referer, int heure);
    // Mode d'emploi :
    // Rempli la structure de donnees et l'index a partir de la cible, referer et heure
    // Contrat :
    // parametres non vides et heure entre 0 et 24

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