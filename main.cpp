//
//  main.cpp
//  TP2
//
//  Created by Karim Benhmida on 20/11/2013.
//  Copyright (c) 2013 Karim Benhmida. All rights reserved.
//

#include <iostream>
#include <stdlib.h>     /* strtol */
#include "Log.h"
#include "Graph.h"
#include <ctime>

using namespace std;

bool checkIfValidNameFile(string s){
    if (s.size() <= 4) {
        return false;
    }
    if(s.substr(s.size()-4,4).compare(".log") ==0){
        return true;
    }
    return false;
    
    
}
bool checkIfValidDotFile(string s){
    if (s.size() <= 4) {
        return false;
    }
    if(s.substr(s.size()-4,4).compare(".dot") ==0){
        return true;
    }
    return false;
}
bool checkIfOption(string s){
    if(s[0]=='-'){
        return true;
    }
    return false;
}

bool checkIfNeedParam(string arg){
    if(arg.compare("g")==0){
        return true;
    }
    if(arg.compare("l")==0){
        return true;
    }
    if(arg.compare("t")==0){
        return true;
    }
    return false;
}
bool checkIfValidParam(string param){
    //si n'a pas la syntaxe d'une option et n'a pa la syntaxe du fichier Log
    return (!checkIfOption(param) && !checkIfValidNameFile(param));
}
string getNameOfOption(string s){
    return s.substr(1,s.size());
}

int main(int argc, const char * argv[])
{
    
    //METHODE 2
	// VOIR SI IL FAUT GERER LES ERREURS !
    
	string nomFichier;
	string nomGraph;
	int nbHits;
	int heure;
    
    
	bool argg=false;
	bool argl=false;
	bool argx=false;
	bool argt=false;
    
    
    
    if(argc<2){
        cerr<<"Error : please specify at least the name of the file to analyse" <<endl;
        return -1;
    }
    
    for(int i=1; argv[i]; i++){
        if(checkIfOption(argv[i])==true){
            string nomOption = getNameOfOption(argv[i]);
            if(checkIfNeedParam(nomOption)==true){
                if (i + 1 < argc) { // Make sure we aren't at the end of argv!
                    if(checkIfValidParam(argv[i+1])){
                        if(nomOption.compare("g")==0){
                            argg=true;
                            nomGraph = argv[++i];
                            if(!checkIfValidDotFile(nomGraph)){
                                cerr<<"Invalid Dot File, -g option must have a file ending with a .dot extension" << endl;
                                return 100;
                            }
                            //test
                            //cout<<"Option -g activee, Il ya bien un graph a creer dans le fichier :" << nomGraph << endl;
                        }
                        if(nomOption.compare("l")==0){
                            argl=true;
                            char* end;
                            nbHits = (int)strtol(argv[++i],&end,10);
                            if (*end){
                                cerr<<"You need to specify an integer number" <<endl;
                                return 110;
                            }
                            if(nbHits<0){
                                cerr<<"You need to specify a positive number of Hits" << endl;
                                return 111;
                            }
                            //test
                            //cout<<"Option -l activee, Le nombre de hits demande est :" << nbHits << endl;
                        }
                        if(nomOption.compare("t")==0){
                            argt=true;
                            char* end;
                            heure = (int)strtol(argv[++i],&end,10);
                            if (*end){
                                cerr<<"You need to specify an integer number" <<endl;
                                return 120;
                            }
                            if(heure<0 || heure>23){
                                cerr<<"You need to specify an hour between 0 and 23" << endl;
                                return 121;
                            }
                            //test
                            //cout << "Option -t activee, Heure prise en compte : " << heure << endl;
                        }
                    }else{
                        cerr << "Option " << nomOption << " requires one argument." << std::endl;
                        return 130;
                    }
                    
                    
                }
            }
            else{
                //Options That Doesn't Need Params!
                if(nomOption.compare("x")==0){
                    //test
                    //cout<<"Option x activee"<<endl;
                    argx=true;
                }else
                if(nomOption.compare("h")==0){
                    cout << "Manuel ./analog Help" << endl;
                    return 2;
                }else{
                    cerr<<"Illegal option : " << nomOption <<endl;
                    return 3;
                }
                
                    
            }
        }else{
            //Si ce n'est pas une Option
            //C'est donc obligatoirement le nom d'un fichier!
            if(i == argc-1){
                if(checkIfValidNameFile(argv[i])){
                    nomFichier = argv[i];
                }else{
                    cerr<<"Invalid file name, name must finish with .Log extension" << endl;
                    return 200;
                }
            }else{
                cerr<< "Invalid Syntax, you must only specify options or name of the file" << endl;
                return 210;
            }
        }
        
        
    }

    
    if(nomFichier.empty()){
        cerr<<"You must enter the name of a log file to execute this command" <<endl;
        return 220;
    }
    if(argl && !argg){
        cout<<"Warning: option -l ignored because used without -g" << endl;
    }
    Log monLog;
    Graph monGraph(nomGraph);

	if(argx){
        monLog.activerOptionX(); // Agit sur la commande lire
	}
	if(argt){
        cout<<"Warning : only hits between " << heure <<"h and " << heure+1 << "h have been taken into account" << endl;
        monLog.activerOptionT(heure);
	}
    
	//cout << "Le nom du fichier est :" << nomFichier << endl;
    //cout<< "Debut Lecture" <<endl;
    
    //const clock_t begin_time = clock();
    // do something
    
    monLog.lire(nomFichier);
    //monLog.testStructure();
    
    
    
    if(argl){
        monGraph.activerOptionL(nbHits);
	}
    if(argg){
        cout<<"Dot-file " << nomGraph << " generated" << endl;
        monGraph.genereGraphViz(monLog.getStructure(), monLog.getReferencesTab());
        monGraph.ecrireGraph();
	}
    //std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;

    
    monLog.afficherDix();

    return 0;
}



