# <b>Gestiunea unei firme de transport</b>

O firmă de transport are mai multe oficii prin țară unde clienții pot suna și pot rezerva locuri pentru diferite 
destinații. Firma folosește un sistem soft pentru gestiunea rezervărilor. Persoana de la oficiu folosește o aplicație 
desktop cu următoarele funcționalități: 
1. <i><b>Login</b></i>. După autentificarea cu succes, o nouă fereastră se deschide în care sunt afișate toate cursele 
(destinația, data și ora plecării și numărul de locuri disponibile). Pentru o anumită destinație pot exista 
mai multe curse. 
2. <i><b>Căutare</b></i>. După autentificarea cu succes, persoana de la oficiu poate căuta o anumită cursă introducand 
destinația, data și ora plecării. Aplicația va afișa în altă listă/alt tabel toate locurile pentru cursa 
respectivă: numărul locului și numele clientului care a rezervat locul respectiv (daca locul este deja 
rezervat). Dacă un loc nu este rezervat se va afișa ‘-‘. Fiecare autocar are 18 locuri pentru clienți.
3. <i><b>Rezervare</b></i>. Persoana de la oficiu poate rezerva locuri pentru clienți la o anumita cursă. Când se face o 
rezervare se introduce numele clientului și numărul de locuri pe care dorește să le rezerve. După ce s-a 
făcut o rezervare, toate persoanele de la celelalte oficii văd lista acutalizată a curselor și a numărului de 
locuri disponibile. De asemenea numele clientului apare la rezultatul afișat la cerința 2. 
4. <i><b>Logout</b></i>.

<h1><b>Versiuni</b></h1>
<h2><b>Tema 7</b></h2>

- crearea <b>servicilor REST</b> în Java și a unui <b>client REST</b> atât în Java, cât și în C#

<h2><b>Tema 5</b></h2>

- aplicația rulează cross-platform folosind <b>Protocol Buffers</b>, clientul a rămas în Java, iar serverul în C#

<h2><b>Tema 4</b></h2>

- împărțirea aplicației în module după modelul <b>client-server</b> și crearea claselor aferente

<h2><b>Tema 3</b></h2>

- crearea clasei <b>Service</b> în pachetul <i>service</i> și a interfeței grafice în pachetul <i>gui</i>
- crearea claselor <b>LoginController</b> și <b>MainController</b> în pachetul <i>controller</i>
- crearea clasei <b>ControllerUtils</b> pentru a ușura transmiterea resurselor principale ale aplicației
- repararea unor greșeli din pachetele din <i>models</i>  și <i?>repository</i>

<h2><b>Tema 2</b></h2>

- crearea interfețelor de Repository pentru fiecare clasă din <b>models</b>
- crearea unei <b>baze de date</b> pentru aplicație (folosind PostgreSQL)
- crearea clasei <b>DbUtils</b> pentru a ușura procesul de colectare a datelor din bază de date
- crearea Repository-urilor cu persistența datelor facută cu baza de date pentru fiecare interfață
- adăugarea log-urilor pentru fiecare operație

<h2><b>Tema 1</b></h2>

- crearea claselor <b>Entity</b>, <b>User</b>, <b>Client</b>, <b>Ride</b>, <b>ReservedSeat</b> și <b>Reservation</b> în pachetul <i>models</i>
- crearea clasei <b>ICrudRepository</b> în pachetul <i>repository</i>