/*************************************************************************
 Commande  -  description
 -------------------
 début                : 28 nov. 2013
 copyright            : (C) 2013 par Mehdi et Karim
 *************************************************************************/

//---------- Réalisation du namespace <commande> (fichier Commande.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Commande.h"


namespace commande {
    bool checkIfValidNameFile(string s)
    // Algorithme :
    // Si taille du string inférieur à 4
    //      Retourne faux
    // Fin si
    // Si le string finit par .log ou par .txt
    //      Retourne vrai
    // Fin si
    //
    // Retourne faux
    {
        if (s.size() <= 4) {
            return false;
        }
        if(s.substr(s.size()-4,4).compare(".log") ==0 || s.substr(s.size()-4,4).compare(".txt") == 0){
            return true;
        }
        return false;
        
        
    }
    bool checkIfValidDotFile(string s)
    // Algorithme :
    // Si taille du string inférieur à 4
    //      Retourne faux
    // Fin si
    // Si le string finit par .dot
    //      Retourne vrai
    // Fin si
    //
    // Retourne faux
    {
        if (s.size() <= 4) {
            return false;
        }
        if(s.substr(s.size()-4,4).compare(".dot") ==0){
            return true;
        }
        return false;
    }
    bool checkIfOption(string s)
    // Algorithme :
    // Si le string commence par un tiret
    //      Retourne vrai
    // Sinon
    //      Retourne faux
    //  Fin si
    {
        if(s[0]=='-'){
            return true;
        }
        return false;
    }
    
    bool checkIfNeedParam(string arg)
    // Algorithme :
    // Si le string est egal à 'g'
    //      Retourne vrai
    // Fin si
    // Si le string est egal à 'l'
    //      Retourne vrai
    // Fin si
    // Si le string est egal à 't'
    //      Retourne vrai
    // Fin si
    // Retourne faux sinon
    {
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
    bool checkIfValidParam(string param)
    // Algorithme :
    // Si le param de l'option n'a pas la syntaxe d'une option et n'a pa la syntaxe du fichier Log
    // Fin si
    {
        //si n'a pas la syntaxe d'une option et n'a pa la syntaxe du fichier Log
        return (!checkIfOption(param) && !checkIfValidNameFile(param));
    }
    string getNameOfOption(string s)
    // Algorithme :
    // Retourner de la seconde à la derniere lettre de s
    {
        return s.substr(1,s.size());
    }
    
    void generateMan()
    {
        cout << "Nom\r\n\
./analog —— ANAlyseur de fichiers LOG Apache\r\n\
\r\n\
Synopsis\r\n\
./analog [-x | -h | -t heure | -l nbhits | -g graphe.dot]  fichier.log\r\n\
\r\n\
Description\r\n\
La commande analog permet d'analyser des fichiers logs apache et d’afficher les 10 documents les plus consultés du log.\r\n\
La commande n’accepte que les fichiers au format .log ou .txt.\r\n\
Selon les options considérées, le comportement de l’utilitaire est modifié.\r\n\
\r\n\
Voici les différentes options disponibles:\r\n\
\r\n\
-g nomfichier.dot	Cette option permet de produire un fichier au format GraphViz du graphe analysé. Chaque page internet apparaitra sous forme d’un noeud et chaque arc indiquera le nombre de parcours associés.\r\n\
\r\n\
\r\n\
-l nbhits	Ne considère que les noeuds du graphe qui sont liés par un arc dont le nombre de hits est supérieur à une valeur nbhits. Cette option n’agit que sur le fichier .dot généré.\r\n\
\r\n\
\r\n\
-x 	Exclut tous les documents qui ont une extension de type image, css ou javascript.\r\n\
\r\n\
\r\n\
-t heure 	Ne prend en compte que les documents qui ont étés visités entre heure et heure+1.\r\n\
\r\n\
-h	Affiche l’aide.\r\n\
\r\n\
Exemples\r\n\
./analog fichier.log\r\n\
Va analyser le contenu du fichier fichier.log et afficher les 10 documents les plus consultés.\r\n\
\r\n\
./analog -x -t 10 fichier.log\r\n\
Analyse le contenu du fichier fichier.log tout en ignorant les documents de type image, css et en ignorant les documents consultés entre 10 et 11h. Elle va ensuite afficher les 10 documents les plus consultés selon les critères précédents.\r\n\
\r\n\
./analog -x -g f1.dot fichier.log\r\n\
Analyse le contenu du fichier fichier.log tout en ignorant les documents de type image, css et js. Elle va ensuite afficher les 10 documents les plus consultés, puis générer un fichier f1.dot qui contiendra les documents non ignorés par la commande.\r\n\
Diagnostic\r\n\
L’utilitaire analog quitte avec le code de retour 0.\r\n\
\r\n\
Tout autre code signifie une erreur :\r\n\
\r\n\
100	Fichier dot invalide, il faut un fichier avec l’extension .dot\r\n\
110	Il faut un entier pour l’option -l\r\n\
111	Il faut un nombre positif pour l’option -l\r\n\
120	Il faut un entier pour l’option -t\r\n\
121	L’heure doit être comprise entre 0 et 23\r\n\
130	L’option utilisée a besoin d’un argument\r\n\
3	Option inconnue\r\n\
200	Nom de fichier Log invalide. doit être de type .log ou .txt\r\n\
210	Syntaxe invalide\r\n\
220	Vous devez renseigner un fichier log\r\n\
44	Impossible d’ouvrir le fichier\r\n\
45	Impossible d’écrire le fichier .dot\r\n\
\r\n\
Auteurs\r\n\
Mehdi Kitane et Karim Benhmida" << endl;
    }
} //Fin du namespace commande

