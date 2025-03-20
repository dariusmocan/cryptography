
## Compilare si executare
    Aplicatia se utilizeaza din linia de comanda, deci, pentru inceput, trebuie folosit un compilator C, ca de exemplu: "gcc -o app main.c"
    Pentru executare trebuie sa folosim numele executabilului format urmat de datele introduse, cu formatul corespunzator. 
    Daca nu se foloseste acel format, ne va fi afisat un mesaj : "Please insert an input like: -e|-d input_file -o output_file\n". 
    Un exemplu pentru utilizarea corecta ar fi: "./app -e input.txt -o output.txt" 

## Abordarea Implementarii
    Pentru inceput, am verificat daca formatul este corect.
    Apoi am utilizat o variabila decrypt, ce ne va transmite daca vrem sa criptam sau decriptam mesajul. 
    Aceasta va lua valoarea 1 daca argv[1] este "-d" (deci decriptam), si 0 in caz contrar.
    In functia proccess_file am verificat daca fisierele exista, in caz negativ, opream rularea.
    Daca exista, atat timp cat putem citi, vom lua linie cu linie, text din fisierul de input, si vom trece fiecare linie prin criptare, 
    folosind Caesar, iar apoi un cifru de transpozitie. Rezultatul fiind scris in fisierul de output.

### Caesar
    Pentru Caesar, am folosit o shiftare de 3 biti (folosind un parametru implicit), iar la decriptare, deplasarea se va face in sens 
    invers (-shift || +shift).
    Am parcurs textul caracter cu caracter, am verificat daca e litera, si am shiftat fiecare litera cu 3 pozitii, folosind un
    caracter auxiliar 'A' sau 'a' pentru a nu iesi din intervalul literelor. apoi ne-am asigurat ca nu iese din intervat le decriptare
    folosind o adaugare de +26. Iar intr-un final am folosit %26 cu acelasi motiv.

### Transpozitie
    Pentru cifrul de transpozitie, am grupat literele 2 cate 2 si le-am schimbat ordinea, in cazul unui cuvant cu numar de
    litere impare, ultima a ramas neschimbata.
    Am parcurs tot sirul, am verificat daca sunt litere caracterul curent si urmatorul, in caz in care le-am interschimbat, si am crescut
    cu indicele cu 2. Pentru decriptare am folosit acelasi algoritm.

## Exemplu de utilizare a interfetei liniei de comanda
    Sa zicem ca input.txt contine textul : hello , iar fisierele encrypt.txt si decrypt.txt sunt goale.
    Dupa compilarea programului apelam aplicatia "./app -e input.txt -o encrypt.txt".
    In CDI ni se va afisa mesajul "Success! Output saved to encrypt.txt".
    In fisierul encrypt.txt acum vom avea textul : hkoor (mesajul criptat).
    Apoi, apeland "./app -d encrypt.txt -o decrypt.txt", in fisierul decrypt.txt vom avea textul : hello (mesajul decriptat)