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
#include "Commande.h"
#include <ctime>

using namespace std;
using namespace commande;


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
                    generateMan();
                    return 0;
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
                    cerr<<"Invalid file name, name must finish with .log or .txt extensions" << endl;
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
    Log monLog(nomFichier);
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
    
    monLog.lire();
    //monLog.testStructure();
    
    
    
    if(argl){
        monGraph.activerOptionL(nbHits);
	}
    if(argg){
        cout<<"Dot-file " << nomGraph << " generated" << endl;
        monGraph.genereGraphViz(monLog.getStructure(), monLog.getReferencesTab());
        monGraph.ecrireGraph();
	}
    //cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;

    
    monLog.afficherDix();

    
    return 0;
}



