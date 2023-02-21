USE Contests;
GO

/*
	Task:
	7/5 interogari cu where
	3/3 interogari cu group by
	2/2 interogari cu distinct
	2/2 interogari cu having
	10/7 interogari cu minim 2 tabele
	2/2 interogari pentru relatie m-n
*/

/*
	1. Sa se afiseze studentii care au participat la un concurs organizat de matematica organizat de o institutie diferita de
'Ministerul Educatiei', ordonati crescator dupa numele concursului si descrescator dupa punctajul obtinut.
	+1 interogari cu where
	+1 interogari cu minim 2 tabele
	+1 interogari pentru relatie m-n
*/
SELECT S.name AS 'Student Name', C.name AS 'Contest', C.subject AS 'Subject', R.score AS 'Score', O.name AS 'Organisers'
FROM Students S
INNER JOIN Results R
ON S.student_id = R.student_id
INNER JOIN Contests C
ON C.contest_id = R.contest_id
INNER JOIN Organisers O
ON C.organiser_id = O.organiser_id
WHERE C.subject = 'mathematics' AND O.name != 'Ministerul Educatiei'
ORDER BY C.name ASC, R.SCORE DESC;

/*
	2. Sa se afiseze ID-ul si numele organizatorilor care au organizat cel putin o competitie online.
	+1 interogari cu where
	+1 interogari cu distinct
	+1 interogari cu minim 2 tabele
*/

SELECT DISTINCT O.organiser_id AS 'Organiser ID', O.name AS 'Organiser'
FROM Organisers O
INNER JOIN Contests C
ON O.organiser_id = C.organiser_id
WHERE C.reservation_id IS NULL;

/* 
	3. Sa se afiseze numele propunatorilor si problema propusa, dificultatea acesteia, concursul la care a aparut problema
si tipul concursului pentru concursurile pluridisciplinare, sortate crescator dupa nume si dupa dificultate.
	+1 interogari cu where
	+1 interogari cu minim 2 tabele
	+1 interogari pentru relatie m-n
*/

SELECT P.name AS 'Proposer', PR.problem AS 'Problem', PR.difficulty AS 'Difficulty', C.name AS 'Contest', C.type AS 'Contest Type'
FROM Proposers P
INNER JOIN Problems PR
ON P.proposer_id = PR.proposer_id
INNER JOIN Contests C
ON C.contest_id = PR.contest_id
WHERE C.subject = 'multidisciplinary'
ORDER BY C.name, PR.difficulty ASC;

/*
	4. Sa se afiseze in ordine descrescatoare dupa medie numele studentilor, scoala din care face parte si media rezultatelor
sale la fiecare concurs la care a participat pentru studentii a caror medie este mai mare decat 10.
	+1 interogari cu group by
	+1 interogari cu having
	+1 interogari cu minim 2 tabele
*/

SELECT S.name AS 'Student', S.school as 'School', FORMAT(AVG(1.0 * R.score), 'N2') AS 'Results average'
FROM Students S
INNER JOIN Results R
ON S.student_id = R.student_id
GROUP BY S.name, S.school
HAVING AVG(1.0 * R.score) > 10
ORDER BY AVG(1.0 * R.score) DESC;

/*
	5. Sa se afiseze numele concursurilor, de cine a fost organizat si dificultatea acestora. Dificultatea unui concurs se
defineste ca media aritmetica dintre dificultatile fiecarei probleme din cadrul acestuia. Afisarea se va face in ordine
descrescatoare dupa dificultate.
	+1 interogari cu group by
	+1 interogari cu minim 2 tabele
*/

SELECT C.name AS 'Contest', O.name AS 'Organiser', FORMAT(AVG(1.0 * P.difficulty), 'N2') AS 'Contest difficulty'
FROM Contests C
INNER JOIN Problems P
ON P.contest_id = C.contest_id
INNER JOIN Organisers O
ON O.organiser_id = C.organiser_id
GROUP BY C.name, O.name
ORDER BY AVG(1.0 * P.difficulty) DESC;

/*
	6. Sa se afiseze ID-ul si numele coordonatorilor studentilor care au obtinut cel putin odata punctajul de 8 la un concurs.
	+1 interogari cu where
	+1 interogari cu distinct
	+1 interogari cu minim 2 tabele
*/
SELECT DISTINCT C.coordinator_id AS 'ID', C.name AS 'Coordinator'
FROM Coordinators C
INNER JOIN Students S
ON S.coordinator_id = C.coordinator_id
INNER JOIN Results R
ON R.student_id = S.student_id
WHERE R.score = 8;

/*
	7. Sa se afiseze numele concursurilor si informatii despre rezervare daca s-au desfasurat in Bucuresti sau
in Cluj-Napoca.
	+1 interogari cu where
	+1 interogari cu minim 2 tabele
*/
SELECT C.name AS 'Contest', R.location AS 'Location', R.date AS 'Date'
FROM Contests C
INNER JOIN Reservations R
ON C.reservation_id = R.reservation_id
WHERE R.location LIKE '%Bucuresti' OR R.location LIKE '%Cluj-Napoca';

/*
	8. Sa se afiseze numele concursurilor si informatii despre rezervare daca s-au desfasurat in anul 2018.
	+1 interogari cu where
	+1 interogari cu minim 2 tabele
*/
SELECT C.name AS 'Contest', R.location AS 'Location', R.date AS 'Date'
FROM Contests C
INNER JOIN Reservations R
ON C.reservation_id = R.reservation_id
WHERE YEAR(R.date) = 2018;

/*
	9. Definim scorul unui coordonator ca fiind media dintre suma totala a scorurilor studentilor sai si a cator probleme
au rezolvat acestia. Afisati numele coordonatorilor si scorul acestora pentru coordonatorii cu scorul de minim 10, ordonati
descrescator dupa scor.
	+1 interogari cu group by
	+1 interogari cu having
	+1 interogari cu minim 2 tabele
*/

SELECT C.name AS 'Coordinator', FORMAT(AVG(1.0 * R.score), 'N2') AS 'Coordinator score'
FROM Coordinators C
INNER JOIN Students S
ON C.coordinator_id = S.coordinator_id
INNER JOIN Results R
ON R.student_id = S.student_id
GROUP BY C.name
HAVING AVG(1.0 * R.score) >= 10
ORDER BY AVG(1.0 * R.score) DESC;

/*
	10. Sa se afiseze numele concursurilor si informatii despre rezervare daca numarul strazii din locatia in care s-au
desfasurat este 10.
	+1 interogari cu where
	+1 interogari cu minim 2 tabele
*/
SELECT C.name AS 'Contest', R.location AS 'Location', R.date AS 'Date'
FROM Contests C
INNER JOIN Reservations R
ON C.reservation_id = R.reservation_id
WHERE R.location LIKE '%, nr. 10,%';


/*
	Sa se afiseze scorurile maxime ale fiecarui student si concursurile la care au fost atinse acestea.
*/
SELECT S.name as 'Student', C.name as 'Contest', R.score as 'Score'
FROM Students S
INNER JOIN Results R
ON S.student_id = R.student_id
INNER JOIN Contests C
ON C.contest_id = R.contest_id
WHERE R.score = (
	SELECT MAX(R1.score)
	FROM Results R1
	WHERE R1.student_id = S.student_id
)