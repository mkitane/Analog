/*************************************************************************
 Log  -  description
 -------------------
 début                : 28 oct. 2013
 copyright            : (C) 2013 par Mehdi
 *************************************************************************/

//---------- Interface de la classe <Log> (fichier Log.h) ------
#if ! defined ( __TP2__Log__)
#define __TP2__Log__

//--------------------------------------------------- Interfaces utilisées
#include <string>
#include <vector>
#include <map>
using namespace std;

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Log>
// Cette classe contient un ensemble de methodes permettant de manipuler un fichier .Log : le lire, identifier et stocker les informations necessaires dans une structure appropriee
//
//------------------------------------------------------------------------
struct ligneLog {
    string adresseIP;
    string date;
    int heure;
    string typeAction;
    string cible;
    string returnCode;
    string quantiteDonnee;
    string referer;
};

struct tabHeure {
    int tab[24] = {0};
};

class Log
{
    //----------------------------------------------------------------- PUBLIC
    
public:
    //----------------------------------------------------- Méthodes publiques
    void lire();
    // Mode d'emploi :
    // Permet de lire un fichier .Log et de remplir la structure de donnes au fur et a mesure
    // Contrat :
    // L'adresse du fichier a lire doit être valide
    
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
    // Il suffit d'appeler la methode avec les heures à considerer
    
    bool isAsset(string s);
    // Mode d'emploi :
    // Detecte si un string contient certains mots predefinis dans la methode et renvoie vrai le cas écheant
    // Contrat :
    // Il faut passer un string (vide ou non) comme parametre
    
    void afficherDix();
    // Mode d'emploi :
    // Affiche sur la sortie standard les 10 (au maximum) pages les plus vues du fichier Log analysé
    // Contrat :
    // Il suffit d'appeler la méthode aucun parametre n'est pris en compte
    
    map< size_t, map < size_t, tabHeure> > getStructure() const;
    // Mode d'emploi :
    // Renvoie la structure (access depuis l'exterieur)
    // Contrat :
    // Aucun parametre
    
    vector<string> getReferencesTab() const;
    // Mode d'emploi :
    // Renvoie le tableau index
    // Contrat :
    // Pas de parametres
    
    
    //------------------------------------------------- Surcharge d'opérateurs
    
    //-------------------------------------------- Constructeurs - destructeur
    Log(const Log & unLog);
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //
    
    Log( string nmFichier);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    virtual ~Log ();
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
    // ligne doit etre une ligne de Log Apache
        
    int chercherChar(string l, size_t longueur, int posDebut, char separateur);
    // Mode d'emploi :
    // Recherche le separateur dans un string a partir d'une position
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
    string nomFichier;
    
    vector<string> referencesTab;
    map< size_t, map < size_t, tabHeure> > structure;
};

//--------------------------- Autres définitions dépendantes de <Log>

#endif // __TP2__Log__