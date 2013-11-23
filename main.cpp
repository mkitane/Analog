//
//  main.cpp
//  TP2
//
//  Created by Karim Benhmida on 20/11/2013.
//  Copyright (c) 2013 Karim Benhmida. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "log.h"
using namespace std;

int main(int argc, const char * argv[])
{
    log monLog;
    monLog.lire("court.log");
    monLog.testStructure();
    monLog.genereGraphViz(monLog.structure, monLog.referencesTab);
    return 0;
}

