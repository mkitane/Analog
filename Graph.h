//
//  Graph.h
//  tp2
//
//  Created by Mehdi Kitane on 05/12/2013.
//  Copyright (c) 2013 Mehdi Kitane. All rights reserved.
//

#ifndef __tp2__Graph__
#define __tp2__Graph__

#include <iostream>
#include "log.h"

class Graph {
private:
    int nbHits;
    bool optionL;
    
public:
    void genereGraphViz(map<size_t, map<size_t,tabHeure> > arbre, vector<string> index,string nom);
    int sommeTableau(int tab[]);
    void activerOptionL(int nb);
    Graph();

};
#endif /* defined(__tp2__Graph__) */
