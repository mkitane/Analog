#Analog

The analog command allows you to analyse the apache log files and display the most consulted documents.

Furthermore, it allows you to generate a syntetic file in the GraphViz format (which can be converted into a graph).
##Build and Run

```
make./analog namefile.log
```
##Synopsis
$./analog [-x | -h | -t hour | -l nbhits | -g graph.dot] file.log##DescriptionThe command line only accept file in the .txt or .log format. 
Here are the different possible options :

*	**g** 	graph.dot	: Generate a GraphViz file.


*	**l** nbhits	: If the g option is active, only analyses the nodes that are linked by arcs wich the value is superior to nbHits

*	**x** 	: doesn't analyse css, javascript and images files.


*	**t** hour 	: only analyses the links visited between hour and hour+1.

*	**h**	: displays help.
##Examples```
./analog fichier.log
	Will analyse the .log file and display the 10 most consulted documents

```


##Diagnostic
L’utilitaire analog quitte avec le code de retour 0.

Tout autre code signifie une erreur :
	
	100	Invalid .dot file
	110	Not an integer for -l option
	111 Not a positive integer for -l option
	120	Not an integer for -t option
	121	Hour must be between 0 and 23
	130	The option needs an argument
	3	Invalid option
	200	Invalid .txt or .log file
	210	Invalid Syntax
	220	.log file absent
	44	Error reading .log/.txt file
	45	Error reading .dot file
	
	
##Go further
For more informations please see (In French) :

	/ docs / tp2_specs.pdf
	/ docs / ManAnalog.pdf
