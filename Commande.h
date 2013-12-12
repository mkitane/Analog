//
//  Commande.h
//  tp2
//
//  Created by Mehdi Kitane on 12/12/2013.
//  Copyright (c) 2013 Mehdi Kitane. All rights reserved.
//

#ifndef __tp2__Commande__
#define __tp2__Commande__

#include <iostream>
#include <string>
using namespace std;

namespace commande{
    bool checkIfValidNameFile(string s);
    bool checkIfValidDotFile(string s);
    bool checkIfOption(string s);
        
    bool checkIfNeedParam(string arg);
    bool checkIfValidParam(string param);
    string getNameOfOption(string s);
}
#endif /* defined(__tp2__Commande__) */
