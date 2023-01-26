USE master;
GO

USE Contests;
GO

-- Reservations values
INSERT INTO Reservations(location, date)
VALUES
	('STR. Arnsber, nr. 34, Alba Iulia', '2018-01-03'),
	('STR. Siretului, nr. 10, Craiova', '2018-02-27'),
	('BD. Coposu Corneliu, nr. 4, Bucuresti', '2018-03-23'),
	('STR. Oborului, nr. 2, Bihor', '2018-06-08'),
	('STR. Horea, nr. 10, Satu Mare', '2018-07-05'),
	('STR. Primaverii, nr. 11, Slatina', '2018-07-12'),
	('STR. Abatorului, nr. 5, Bacau', '2018-08-13'),
	('STR. Ipatescu Ana, nr. 3, Ploiesti', '2018-09-05'),
	('STR. Zola Emile, nr. 4, Ploiesti', '2018-09-13'),
	('STR. Republicii, nr. 33, Cluj-Napoca', '2018-10-12'),
	('STR. Rampei, nr. 18, Iasi', '2018-11-22'),
	('STR. Babadag, nr. 165, Tulcea', '2018-12-06'),
	('STR. Venus, nr. 22, Cluj-Napoca', '2019-07-25'),
	('STR. Puskin Alexandru, nr. 10, Bucuresti', '2020-04-28'),
	('BD. Aviatorilor, nr. 7, Bucuresti', '2020-09-10'),
	('BD. Gheorghe Magheru, nr. 10, Bucuresti', '2021-02-12'),
	('STR. Lacu Rosu, nr. 1, Cluj-Napoca', '2021-04-10'),
	('STR. Calea Bucuresti, nr. 5, Timisoara', '2021-05-07');

SELECT * FROM Reservations;

-- Organisers inserts
INSERT INTO Organisers(name)
VALUES
	('Ministerul Educatiei'),
	('Societatea de Stiinte Matematice din Romania'),
	('Societatea Romana de Fizica'),
	('infoarena'),
	('Mathematical Society of South Eastern Europe'),
	('Institute of Electrical and Electronics Engineers');

SELECT * FROM Organisers;

-- Contests values.
INSERT INTO Contests(name, type, subject, reservation_id, organiser_id)
VALUES
	('Olimpiada Nationala de Matematica', 'national', 'mathematics', 50014, 80000),
	('Olimpiada Nationala de Informatica', 'national', 'computer science', 50002, 80000),
	('Olimpiada Nationala de Fizica', 'national', 'physics', 50006, 80000),
	('Olimpiada Nationala de Astronomie si Astrofizica', 'national', 'physics', 50009, 80000),
	('Olimpiada Nationala "Stiintele Naturii"', 'national', 'multidisciplinary', 50010, 80000),
	('Olimpiada Pluridisciplinara "Tuymaada"', 'international', 'multidisciplinary', 50012, 80004),
	('Concursul "Gheorghe Lazar"', 'intercounty', 'mathematics', 50015, 80001),
	('Concursul "Laurentiu Panaitopol"', 'intercounty', 'mathematics', 50000, 80001),
	('Concursul "Dan Barbilian"', 'county', 'mathematics', 50011, 80001),
	('Concursul Online "Matematica, de drag"', 'national', 'mathematics', null, 80001), 
	('Concursul "Algoritmiada"', 'national', 'computer science', 50004, 80003),
	('Concursul Online "Happy Coding"', 'national', 'computer science', null, 80003),
	('Concursul "Grigore Moisil"', 'intercounty', 'computer science', 50005, 80000),
	('Concursul "Stelele Informaticii"', 'county', 'computer science', 50003, 80003),
	('Concursul Online "PHI"', 'national', 'physics', null, 80002),
	('Concursul "Augustin Maior"', 'intercounty', 'physics', 50007, 80002),
	('Concursul "Hands on Universe"', 'intercounty', 'physics', 50013, 80002),
	('Concursul "Evrika"', 'national', 'physics', 50010, 80002),
	('Concursul "Prosoft"', 'intercounty', 'multidisciplinary', 50001, 80000),
	('Olimpiada Balcanica de Matematica', 'international', 'mathematics', 50012, 80004),
	('Olimpiada Balcanica de Informatica', 'international', 'computer science', 50008, 80005),
	('Turneul International de Informatica "John Atanasoff"', 'international', 'computer science', null, 80005),
	('Concursul Online "Bolyai Farkas"', 'international', 'multidisciplinary', null, 80004);

SELECT * FROM Contests;

UPDATE Contests
SET reservation_id = 50017
WHERE contest_id = 10019;

SELECT * FROM Contests

-- Proposers inserts
INSERT INTO Proposers(name)
VALUES
	('Vasile Pop'), ('Marcel Roman'), ('Gabriel Mincu'), ('Tiberiu Trif'), ('Dorian Popa'), -- Mathematics proposers
	('Marinel Serban'), ('Dan Ghinea'), ('Chesca Ciprian'), ('Adrian Panaete'), ('Gabriel Mircea'), -- Computer science proposers
	('Florea Uliu'), ('Mihail Sandu'), ('Florin Maceseanu'), ('Victor Stoica'), ('Ion Toma'); -- Physics proposers

-- Problems inserts
INSERT INTO Problems(proposer_id, contest_id, problem, difficulty)
VALUES
	-- Mathematics problems
	(40000, 10000, 'Teorema lui Chauchy si Hadamard', 7),
	(40001, 10000, 'Teorema lui Cauchy-Kovalevskayar', 8),
	(40002, 10004, 'Teorema celor trei perpendiculare', 2),
	(40003, 10005, 'Teorema impulsului', 6),
	(40004, 10006, 'Teorema lui Borel-Lebesgue', 9),
	(40000, 10006, 'Teorema lui Desargues', 10),
	(40002, 10007, 'Teorema lui Heine', 9),
	(40004, 10007, 'Teorema lui Pompeiu', 8),
	(40001, 10008, 'Teorema lui Menelaus', 3),
	(40003, 10008, 'Teorema lui Ceva', 3),
	(40000, 10009, 'Teorema lui Schwarz', 8),
	(40003, 10009, 'Teorema lui Stewart', 5),
	(40002, 10018, 'Teorema lui Pitagora', 1),
	(40001, 10019, 'Teorema lui Stokes', 10),
	(40003, 10019, 'Teorema lui Rouche', 9),
	(40002, 10022, 'Teorema lui Liouville', 10),
	-- Computer Science problems
	(40005, 10001, 'Algoritmul lui Kadane', 8),
	(40006, 10001, 'Algoritmul lui Floyd', 7),
	(40007, 10005, 'Algoritmul Quick Select', 6),
	(40008, 10010, 'Algoritmul lui Kruskal', 5),
	(40009, 10010, 'Heap Sort', 6),
	(40005, 10011, 'Insertion Sort', 2),
	(40007, 10011, 'Linear Search', 1),
	(40009, 10012, 'Quick Sort', 7),
	(40006, 10012, 'Breadth First Search', 4),
	(40008, 10013, 'Depth First Search', 3),
	(40005, 10013, 'Algoritmul lui Euclid', 1),
	(40008, 10018, 'Algoritmul Bellman-Ford', 7),
	(40006, 10020, 'Algoritmul lui Lee', 8),
	(40009, 10020, 'Sortare topologica', 8),
	(40007, 10021, 'Algoritmul KMP', 10),
	(40005, 10021, 'Algoritmul Boyer-More', 10),
	(40009, 10022, 'Algoritmul lui Dijkstra', 6),
	-- Physics problems
	(40010, 10002, 'Masa moleculara a unui amestec de gaze', 8),
	(40011, 10002, 'Energia interna a gazului ideal', 6),
	(40012, 10003, 'Miscarea armonica', 7),
	(40013, 10003, 'Teorema asupra miscarii centrului de masa', 9),
	(40014, 10004, 'A doua lege a lui Newton', 4),
	(40010, 10014, 'Echilibrul instabil, echilibrul stabil, echilibrul indiferent', 8),
	(40012, 10014, 'Forta presiunii hidrostatice', 9),
	(40014, 10015, 'Ecuatia Mendeleev-Clapeyron', 10),
	(40011, 10015, 'Legea lui Dalton', 9),
	(40013, 10016, 'Puterea si potentialul campului electric', 8),
	(40012, 10016, 'Legea lui Coulomb', 7),
	(40010, 10017, 'Energia potentiala a unui sistem de sarcini electrice', 8),
	(40011, 10017, 'Legea lui Faraday pentru electroliza', 10);

INSERT INTO Coordinators(name)
VALUES
--  Cluj-Napoca       Bucuresti           Iasi
	('Danut Cernat'), ('Sergiu Serban'), ('Martin Zaituc'), -- mathematics coordinators
	('Claudiu Dragan'), ('Apostol Argetoianu'), ('Iuliana Cosovei'), -- computer science coordinators
	('Florica Groza'), ('Catalin Vladu'), ('Denisa Cozma'); -- physics coordinators

INSERT INTO Students(name, school, coordinator_id)
VALUES
	--mathematics students
	('Catalin Vianu', 'Colegiul National "Emil Racovita" Cluj-Napoca', 70000),
	('Daniel Voiculet', 'Colegiul National "Gheorghe Sincai" Cluj-Napoca', 70000),
	('Laura Lazar', 'Liceul Teoretic "Avram Iancu" Cluj-Napoca', 70000),

	('Sebastian Cernat', 'Colegiul National "Tudor Vianu" Bucuresti', 70001),
	('Ioana Puiu', 'Liceul Teoretic International de Informatica Bucuresti', 70001),
	('Cezar Hila', 'Colegiul National "Sfantul Sava" Bucuresti', 70001),

	('Andreea Dobrescu', 'Colegiul National "Costache Negruzi" Iasi', 70002),
	('Emil Toma','Colegiul National "Emil Racovita" Iasi', 70002),
	('Darius Alexandrescu', 'Colegiul National Iasi', 70002),
	--computer science students
	('Filip Rotaru', 'Colegiul National "Emil Racovita" Cluj-Napoca', 70003),
	('Isabela Muresan', 'Colegiul National "Gheorghe Sincai" Cluj-Napoca', 70003),
	('Adam Stancu', 'Liceul Teoretic "Avram Iancu" Cluj-Napoca', 70003),

	('Mihaela Rusu', 'Colegiul National "Tudor Vianu" Bucuresti', 70004),
	('Stelian Ripnu', 'Liceul Teoretic International de Informatica Bucuresti', 70004),
	('Dorin Niculescu', 'Colegiul National "Sfantul Sava" Bucuresti', 70004),

	('Calin Pirvu', 'Colegiul National "Costache Negruzi" Iasi', 70005),
	('Cristian Zaituc','Colegiul National "Emil Racovita" Iasi', 70005),
	('Paula Breban', 'Colegiul National Iasi', 70005),
	--physics students
	('Tatiana Otvos', 'Colegiul National "Emil Racovita" Cluj-Napoca', 70006),
	('Robert Popa', 'Colegiul National "Gheorghe Sincai" Cluj-Napoca', 70006),
	('Nicolas Pop', 'Liceul Teoretic "Avram Iancu" Cluj-Napoca', 70006),

	('Robert Lucescu', 'Colegiul National "Tudor Vianu" Bucuresti', 70007),
	('Bodgan Enache', 'Liceul Teoretic International de Informatica Bucuresti', 70007),
	('Iulia Radacanu', 'Colegiul National "Sfantul Sava" Bucuresti', 70007),

	('Teodor Rebreanu', 'Colegiul National "Costache Negruzi" Iasi', 70008),
	('Loredana Roman','Colegiul National "Emil Racovita" Iasi', 70008),
	('Robert Chivu', 'Colegiul National Iasi', 70008);

SELECT * FROM Students;
SELECT * FROM Contests WHERE subject LIKE 'mult%';

INSERT INTO Results(student_id, contest_id)
VALUES
	--mathematics
	(20000, 10000), (20001, 10000), (20002, 10000),
	(20003, 10000), (20004, 10000), (20005, 10000),
	(20006, 10000), (20007, 10000), (20008, 10000),

	(20000, 10006), (20001, 10006), (20002, 10006),
	(20003, 10006), (20004, 10006), (20005, 10006),
	(20006, 10006), (20007, 10006), (20008, 10006),

	(20000, 10007), (20001, 10007), (20002, 10007),
	(20003, 10007), (20004, 10007), (20005, 10007),
	(20006, 10007), (20007, 10007), (20008, 10007),

	(20000, 10008), (20001, 10008), (20002, 10008),
	(20003, 10008), (20004, 10008), (20005, 10008),
	(20006, 10008), (20007, 10008), (20008, 10008),

	(20000, 10009), (20001, 10009), (20002, 10009),
	(20003, 10009), (20004, 10009), (20005, 10009),
	(20006, 10009), (20007, 10009), (20008, 10009),

	(20000, 10019), (20001, 10019), (20002, 10019),
	(20003, 10019), (20004, 10019), (20005, 10019),
	(20006, 10019), (20007, 10019), (20008, 10019),
	--computer science
	(20009, 10001), (20010, 10001), (20011, 10001),
	(20012, 10001), (20013, 10001), (20014, 10001),
	(20015, 10001), (20016, 10001), (20017, 10001),

	(20009, 10010), (20010, 10010), (20011, 10010),
	(20012, 10010), (20013, 10010), (20014, 10010),
	(20015, 10010), (20016, 10010), (20017, 10010),

	(20009, 10011), (20010, 10011), (20011, 10011),
	(20012, 10011), (20013, 10011), (20014, 10011),
	(20015, 10011), (20016, 10011), (20017, 10011),

	(20009, 10012), (20010, 10012), (20011, 10012),
	(20012, 10012), (20013, 10012), (20014, 10012),
	(20015, 10012), (20016, 10012), (20017, 10012),

	(20009, 10013), (20010, 10013), (20011, 10013),
	(20012, 10013), (20013, 10013), (20014, 10013),
	(20015, 10013), (20016, 10013), (20017, 10013),

	(20009, 10020), (20010, 10020), (20011, 10020),
	(20012, 10020), (20013, 10020), (20014, 10020),
	(20015, 10020), (20016, 10020), (20017, 10020),

	(20009, 10021), (20010, 10021), (20011, 10021),
	(20012, 10021), (20013, 10021), (20014, 10021),
	(20015, 10021), (20016, 10021), (20017, 10021),
	--physics
	(20018, 10002), (20019, 10002), (20020, 10002),
	(20021, 10002), (20022, 10002), (20023, 10002),
	(20024, 10002), (20025, 10002), (20026, 10002),

	(20018, 10003), (20019, 10003), (20020, 10003),
	(20021, 10003), (20022, 10003), (20023, 10003),
	(20024, 10003), (20025, 10003), (20026, 10003),

	(20018, 10014), (20019, 10014), (20020, 10014),
	(20021, 10014), (20022, 10014), (20023, 10014),
	(20024, 10014), (20025, 10014), (20026, 10014),

	(20018, 10015), (20019, 10015), (20020, 10015),
	(20021, 10015), (20022, 10015), (20023, 10015),
	(20024, 10015), (20025, 10015), (20026, 10015),

	(20018, 10016), (20019, 10016), (20020, 10016),
	(20021, 10016), (20022, 10016), (20023, 10016),
	(20024, 10016), (20025, 10016), (20026, 10016),

	(20018, 10017), (20019, 10017), (20020, 10017),
	(20021, 10017), (20022, 10017), (20023, 10017),
	(20024, 10017), (20025, 10017), (20026, 10017),
	--multidisciplinary
	(20000, 10004), (20003, 10004), (20006, 10004),
	(20009, 10004), (20012, 10004), (20015, 10004),
	(20018, 10004), (20021, 10004), (20024, 10004),

	(20000, 10005), (20003, 10005), (20006, 10005),
	(20009, 10005), (20012, 10005), (20015, 10005),
	(20018, 10005), (20021, 10005), (20024, 10005),

	(20000, 10018), (20003, 10018), (20006, 10018),
	(20009, 10018), (20012, 10018), (20015, 10018),
	(20018, 10018), (20021, 10018), (20024, 10018),

	(20000, 10022), (20003, 10022), (20006, 10022),
	(20009, 10022), (20012, 10022), (20015, 10022),
	(20018, 10022), (20021, 10022), (20024, 10022);

SELECT * FROM Results WHERE score = 17;
DELETE FROM Results;

UPDATE Results
SET score = 10 + CHECKSUM(NewId()) % (20 - 10 + 1);

SELECT FLOOR(RAND() * (20 - 10 + 1)) + 10;

SELECT * FROM Students;

SELECT C.contest_id, C.name, C.type, C.subject, R.location, R.date
FROM Contests C
INNER JOIN Reservations R
ON C.reservation_id = R.reservation_id
WHERE C.type = 'international';

SELECT S.name AS 'Student Name', C.name AS 'Contest', C.subject AS 'Subject', R.score AS 'Score'
FROM Students S
INNER JOIN Results R
ON S.student_id = R.student_id
INNER JOIN Contests C
ON C.contest_id = R.contest_id
INNER JOIN Organisers O
ON C.organiser_id = O.organiser_id
WHERE C.subject LIKE 'math%' AND O.name LIKE 'Societatea%'
ORDER BY C.name ASC, R.SCORE DESC;