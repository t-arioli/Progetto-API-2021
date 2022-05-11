# Prova finale di Algoritmi e Strutture dati - Anno Accademico 2020/2021

La specifica del progetto è visibile nel file "Presentazione.pdf".  
Il codice del progetto è interamente nel file "GraphRanker.c".


## Compiling
Aprire Bash e lanciare uno dei tre scripts:  
   ``$ ./compileForLocal`` : compilazione semplice  
   ``$ ./compileForServer`` : compilazione effettuata come dal tool di valutazione  
   ``$ ./compileWithAddressSanitiezer`` : compilazione con AddressSanitizier (ASan)   
  

## Testing
Aprire Bash e lanciare lo script:  
  ``$ ./testVerificator``
(Permette la verifica dei soli testi già presenti nel package ``test``)

## Analisys
Il sorgente C dovrà essere già compilato

Valgrind (installazione: ``$ sudo apt-get install valgrind``)
- Analisi con memcheck: ``$ ./memcheck``
- Analisi con kcachegrind: ``$ ./callgrind``

Valgrind - massif (installazione della GUI: ``$ sudo apt-get install massif-visualizer``)
- Analisi con massif (GUI): ``$ ./massif``



