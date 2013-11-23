//
//  log.h
//  TP2
//
//  Created by Karim Benhmida on 22/11/2013.
//  Copyright (c) 2013 Karim Benhmida. All rights reserved.
//

#ifndef __TP2__log__
#define __TP2__log__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>      // std::ostringstream
#include <stdlib.h>     /* strtol */

using namespace std;
struct tabHeure {
    int tab[24] = {0};
};

class log
{
    public :
    bool optionX;
    bool optionT;
    int heure;
    
    
    vector<string> referencesTab;
    
    map< size_t, map < size_t, tabHeure> > structure;
    
    
    public :
        log();
        bool analyseLigne(string ligne, string *cible, string *referer, int *heure);
        int chercherGuillemetsFermants(string l, int posDebut);
        void lire(string s);
        void remplir(string cible, string referer, int heure);
        void testStructure();
        void genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index);
        int sommeTableau(int tab[]);
        void activerOptionX();
        void activerOptionT(int h);
        bool isAsset(string s);
};

#endif /* defined(__TP2__log__) */
