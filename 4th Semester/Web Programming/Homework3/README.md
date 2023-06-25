# <b>Tema 3 - HTTP</b>

## Exemplul 1

Fisierul demo.c, se va compila ca demo.cgi.

    #include <stdio.h>

    int main() {
    printf("Content-type: text/html\n");
    printf("\n");
    printf("Hello world!");
    }

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex1/demo.cgi">See it in action</a>

## Exemplul 2

Fisierul contor.cgi. I se vor atribui drepturi de executie pentru serverul web (o+x).

    #!/bin/bash
    echo "Content-type: text/html"
    echo
    n=`cat contor.txt`
    n=`expr $n + 1`
    echo $n > contor.txt
    echo $n

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex2/contor.cgi">See it in action</a>

## Exemplul 3 – Incapsularea parametrilor trimisi din browser prin GET

    <!DOCTYPE html>
    <html>
    <head>
    <title>Query String Demo</title>
    </head>
    <body>
    <form method="GET" action="show_input_data.cgi">
        <input type="text" name="nume" placeholder="Nume"><br>
        <input type="text" name="telefon" placeholder="Telefon"><br>
        <input type="text" name="varsta" placeholder="Varsta"><br>
        <input type="submit" value="Trimite">
    </form>
    </body>
    </html>

Fisierul show_input_data.c, se va compila ca show_input_data.cgi

    #include <stdio.h>
    #include <stdlib.h>

    int main() {
    printf("Content-type: text/html\n\n");
    printf("Am primit de la browser query string-ul %s", getenv("QUERY_STRING"));
    }

In locul variantei de mai sus scrise in C, se poate folosi varianta scrisa ca shell Unix:

    #!/bin/bash
    echo "Content-type: text/html"
    echo
    echo Am primit de la browser query string-ul $QUERY_STRING

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex3/index.html">See it in action</a>

## Exemplul 4 – Incapsularea parametrilor trimisi din browser prin POST

Acelasi exemplu ca exemplul 3, dar datele sunt trimise prin POST.

    <!DOCTYPE html>
    <html>
    <head>
    <title>Demo submit prin POST</title>
    </head>
    <body>
    <form method="POST" action="show_input_data.cgi">
        <input type="text" name="nume" placeholder="Nume"><br>
        <input type="text" name="telefon" placeholder="Telefon"><br>
        <input type="text" name="varsta" placeholder="Varsta"><br>
        <input type="submit" value="Trimite">
    </form>
    </body>
    </html>

Fisierul show_input_data.c, se va compila ca show_input_data.cgi

    #include <stdio.h>
    #include <stdio.h>

    int main() {
    char line[1000];
    printf("Content-type: text/html\n\n");
    fgets(line, 1000, stdin);
    printf("Am primit de la browser %s", line);
    }

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex4/index.html">See it in action</a>

## Exemplul 5 – Incapsularea continutului unui fisier prin POST

    <!DOCTYPE html>
    <html>
    <head>
    <title>Formular input file</title>
    </head>
    <body>
    <form method="POST" action="show_input_data.cgi" enctype="multipart/form-data">
        <input type="text" name="dummy1" placeholder="Dummy 1"><br>
        <input type="file" name="fisier"><br>
        <input type="text" name="dummy2" placeholder="Dummy 2"><br>
        <input type="submit" value="Trimite">
    </form>
    </body>
    </html>

Fisierul show_input_data.c, se va compila ca show_input_data.cgi

    #include <stdio.h>

    int main() {
    char line[1000];
    printf("Content-type: text/html\n\n");
    while (! feof(stdin)) {
        fgets(line, 1000, stdin);
        if (! feof(stdin))
        printf("%s<br/>", line);
    }
    }

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex5/index.html">See it in action</a>

## Exemplul 6 – Afisarea antetelor din cadrul cererii HTTP

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex6/headers.cgi">See it in action</a>

Intrebare: Unde puteti gasi si cum puteti vizualiza codul sursa al exemplului 6 de mai sus?
Raspuns: Ar trebui sa stiti pana in acest moment pe baza cunostintelor dobandite :).

## Exemplul 7 – URL Decoding

Fisierul decodeURL.c, se va compila ca decodeURL.cgi.

    #include <stdio.h>
    #include <string.h>

    int hexatoint(char c) {
    if ((c>='a') && (c<='f'))
        return c - 'a' + 10;
    if ((c>='A') && (c<='F'))
        return c - 'A' + 10;
    return c - '0';
    }

    void decode(char *s) {
    int i = 0, j;
    while (s[i] != 0) {
        if (s[i] == '+')
        s[i] = ' ';
        if (s[i] == '%') {
        char c = 16 * hexatoint(s[i+1]) + hexatoint(s[i+2]);
        s[i] = c;
        j = i + 1;
        do {
            s[j] = s[j + 2];
            j++;
        } while (s[j] != 0);
        }
        i++;
    }  
    }

    int main() {
    char s[] = "http%3A%2F%2Fwww.cs.ubbcluj.ro%2F%7Ebufny%2Fprogramare%2Dweb%2F";
    printf("Content-type: text/html\n\n");
    printf("Original string: %s<br>\n", s);
    decode(s);
    printf("Decoded string: %s", s);
    }

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex7/decodeURL.cgi">See it in action</a>

Cerinta facultativa pentru extra puncte la laborator: Modificati exemplul de mai sus astfel incat sirul care trebuie decodificat sa fie trimis serverului prin intermediul unui formular.

## Exemplul 8 – Managementul sesiunii si caracterul stateless al protocolului HTTP

Fisierul play.c, se va compila ca play.cgi.

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>

    struct data {
    int nr;
    int tries;
    };

    int getIdFromQueryString() {
    char buffer[2048];
    int id;
    strcpy(buffer, getenv("QUERY_STRING"));
    sscanf(buffer, "id=%d&", &id);
    return id;  
    }

    int getNumberFromQueryString() {
    char buffer[2048];
    int id, nr;
    strcpy(buffer, getenv("QUERY_STRING"));
    sscanf(buffer, "id=%d&nr=%d", &id, &nr);
    return nr;  
    }

    int init() { 
    int r, id;
    int code;
    char filename[100];
    struct data d;
    
    srand(getpid());
    r = random() % 100;

    do {
        id = random();
        sprintf(filename, "/tmp/%d.txt", id);
        code = creat(filename, O_CREAT | O_EXCL | 0600);
    }
    while (code < 0);

    d.nr = r;
    d.tries = 0;
    write(code, &d, sizeof(d));
    close(code);
    
    return id;
    }

    void destroy(int id) {
    char filename[100];
    sprintf(filename, "/tmp/%d.txt", id);
    unlink(filename);
    }

    int getNumberFromFile(int id) {
    char filename[100];
    int fd;
    
    sprintf(filename, "/tmp/%d.txt", id);
    struct data d;
    fd = open(filename, O_RDWR);
    if (fd < 0)
        return -1;
    read(fd, &d, sizeof(d));
    d.tries++;
    lseek(fd, 0, SEEK_SET);
    write(fd, &d, sizeof(d));  
    close(fd);
    return d.nr;
    }

    int getNoOfTries(int id) {
    char filename[100];
    int fd;
    sprintf(filename, "/tmp/%d.txt", id);
    struct data d;
    fd = open(filename, O_RDONLY);
    read(fd, &d, sizeof(d));
    close(fd);
    return d.tries;    
    }

    int isNewUser() {
    if (getenv("QUERY_STRING") == NULL)
        return 1;
    if (strcmp(getenv("QUERY_STRING"), "") == 0)
        return 1;
    return 0;  
    }

    void printForm(int id) {
    printf("<form action='play.cgi' method='get'>\n");
    printf("<input type='hidden' name='id' value='%d'>\n", id);
    printf("Nr: <input type='text' name='nr'><br>\n");
    printf("<input type='submit' value='Trimite'>\n");
    printf("</form>");;
    }

    int main() {
    int id, status;
    if (isNewUser()) {
        id = init();    
        status = 0;
    }
    else {
        int nr, nr2;
        id = getIdFromQueryString();
        nr = getNumberFromQueryString();
        nr2 = getNumberFromFile(id);
        if (nr2 == -1)
        status = 1;
        else if (nr == nr2)
        status = 2;
        else if (nr < nr2)
        status = 3;
        else if (nr > nr2)
        status = 4;                
    }
    printf("Content-type: text/html\n\n");
    printf("<html>\n<body>\n");
    
    switch (status) {
        case 0 : printf("Ati inceput un joc nou.<br>\n"); printForm(id); break;
        case 1 : printf("Eroare. Click <a href='play.cgi'>here</a> for a new game!"); break;
        case 2 : printf("Ati ghicit din %d incercari. Click <a href='play.cgi'>here</a> for a new game!</body></html>", getNoOfTries(id)); destroy(id); break;
        case 3 : printf("Prea mic!<br>\n"); printForm(id); break;
        case 4 : printf("Prea mare!<br>\n"); printForm(id);
    }
    
    printf("</body>\n</html>");
    }

<a href="http://www.scs.ubbcluj.ro/~bufny/cgi-bin/ex8/play.cgi">See it in action</a>

Cerinta facultativa pentru extra puncte la laborator: Modificati exemplul de mai sus astfel incat managementul sesiunii sa nu se faca prin intermediul unui input de tip hidden ci prin intermediului unui cookie.