CREATE DATABASE ContestsTest
GO

USE ContestsTest
GO


-- Tables:
--	Sponsors: o tabela avand un camp ca si cheie primara si nici o cheie straina
--	Contests: o tabela avand un camp ca si cheie primara si cel putin o cheie straina
--	Donations: o tabela avand doua campuri ca si cheie primara

-- CREATE TABLES FOR TEST DATABASE, FOR THE BIG DATABASE WE DON'T NEED TO CREATE THESE TABLES
CREATE TABLE Sponsors (
	sponsor_id INT PRIMARY KEY IDENTITY(30000, 1),
	name VARCHAR(100) NOT NULL
);

CREATE TABLE Organisers (
	organiser_id INT PRIMARY KEY IDENTITY(80000, 1),
	name VARCHAR(100) NOT NULL,
);

CREATE TABLE Contests (
	contest_id INT PRIMARY KEY IDENTITY(10000, 1),
	name VARCHAR(100) NOT NULL,
	type VARCHAR(100) NOT NULL,
	subject VARCHAR(100) NOT NULL,
	organiser_id INT FOREIGN KEY REFERENCES Organisers(organiser_id)
);

CREATE TABLE Donations (
	sponsor_id INT FOREIGN KEY REFERENCES Sponsors(sponsor_id),
	contest_id INT FOREIGN KEY REFERENCES Contests(contest_id),
	amount INT CHECK (amount > 0),
	CONSTRAINT pk_sponsor_contest PRIMARY KEY(sponsor_id, contest_id)
);


-- The organiser for the test database
INSERT INTO Organisers VALUES ('GENERAL ORGANISER')
SELECT * FROM Organisers

-- Views:
--	ViewSponsors: un view ce contine o comanda SELECT pe o tabela
--	ViewOrganisersContests: un view ce contine o comanda SELECT aplicata pe cel putin doua tabele
--	ViewSponsorsNumberOfContests: un view ce contine o comanda SELECT aplicata pe cel putin doua tabele si avand o clauza GROUP BY.
GO
CREATE OR ALTER VIEW ViewSponsors
AS
	SELECT S.name AS 'Sponsor'
	FROM Sponsors S
GO
CREATE OR ALTER VIEW ViewOrganisersContests
AS
	SELECT O.name AS 'Organiser', C.name AS 'Contest'
	FROM Organisers O
	INNER JOIN Contests C
	ON O.organiser_id = C.organiser_id
GO
CREATE OR ALTER VIEW ViewSponsorsNumberOfContests
AS
	SELECT S.name AS 'Sponsor', COUNT(D.contest_id) AS 'Number of contests'
	FROM Sponsors S
	INNER JOIN Donations D
	ON S.sponsor_id = D.sponsor_id
	GROUP BY S.name
GO

SET IDENTITY_INSERT Tables ON;
DELETE FROM Tables;
INSERT INTO Tables(TableID, Name)
VALUES (1, 'Sponsors'), (2, 'Contests'), (3, 'Donations');
SET IDENTITY_INSERT Tables OFF;

SET IDENTITY_INSERT Views ON;
DELETE FROM Views;
INSERT INTO Views(ViewID, Name)
VALUES (1, 'ViewSponsors'), (2, 'ViewOrganisersContests'), (3, 'ViewSponsorsNumberOfContests');
SET IDENTITY_INSERT Views OFF;


SET IDENTITY_INSERT Tests ON;
DELETE FROM Tests;
INSERT INTO Tests(TestID, Name)
VALUES (1, 'selectView'),
		(2, 'insertSponsors'), (3, 'deleteSponsors'),
		(4, 'insertContests'), (5, 'removeContests'),
		(6, 'insertDonations'), (7, 'deleteDonations');
SET IDENTITY_INSERT Tests OFF;


SELECT * FROM Tables;
SELECT * FROM Views;
SELECT * FROM Tests;

DELETE FROM TestViews;
INSERT INTO TestViews(TestID, ViewID)
VALUES (1, 1), (1, 2), (1, 3);

DELETE FROM TestTables;
INSERT INTO TestTables(TestID, TableID, NoOfRows, Position)
VALUES (2, 1, 10000, 1), (4, 2, 10000, 2), (6, 3, 10000, 3)



-- Procedures:
GO
CREATE OR ALTER PROC insertSponsors AS
BEGIN
	DECLARE @rows INT = (SELECT TOP 1 TT.NoOfRows
	FROM TestTables TT INNER JOIN Tests T ON TT.TestID = T.TestID
	WHERE T.Name = 'insertSponsors');

	DECLARE @current INT = 1;

	WHILE @current <= @rows
	BEGIN
		INSERT INTO Sponsors(name) VALUES ('testDataBasePerformance')
		SET @current = @current + 1
	END
END
GO
CREATE OR ALTER PROC deleteSponsors AS
BEGIN
	DELETE FROM Sponsors
	WHERE name = 'testDataBasePerformance';
END

GO
CREATE OR ALTER PROC insertContests AS
BEGIN
	DECLARE @rows INT = (SELECT TOP 1 TT.NoOfRows
	FROM TestTables TT INNER JOIN Tests T ON TT.TestID = T.TestID
	WHERE T.Name = 'insertContests');
	DECLARE @current INT = 1; 
	DECLARE @organiser INT = (SELECT TOP 1 organiser_id FROM Organisers);
	
	WHILE @current <= @rows
	BEGIN
		INSERT INTO Contests(name, type, subject, organiser_id)
		VALUES ('testDataBasePerformance', 'testDataBasePerformance', 'testDataBasePerformance', @organiser);
		SET @current = @current + 1
	END
END

GO
CREATE OR ALTER PROC deleteContests AS
BEGIN
	DELETE FROM Contests
	WHERE name = 'testDataBasePerformance';
END

GO
CREATE OR ALTER PROC insertDonations AS
BEGIN
	DECLARE @rows INT = (SELECT TOP 1 TT.NoOfRows
	FROM TestTables TT INNER JOIN Tests T ON TT.TestID = T.TestID
	WHERE T.Name = 'insertDonations');

	DECLARE @current INT = 1; 
	DECLARE @first_sponsor INT = (SELECT TOP 1 sponsor_id FROM Sponsors WHERE name = 'testDataBasePerformance');
	DECLARE @first_contest INT = (SELECT TOP 1 contest_id FROM Contests WHERE name = 'testDataBasePerformance');
	DECLARE @int_max INT = (SELECT POWER(2., 31) - 1);
	
	WHILE @current <= @rows
	BEGIN
		DECLARE @current_sponsor INT = (SELECT @first_sponsor + @current - 1);
		DECLARE @current_contest INT = (SELECT @first_contest + @current - 1);
		INSERT INTO Donations(sponsor_id, contest_id, amount)
		VALUES (@current_sponsor, @current_contest, @int_max);
		SET @current = @current + 1
	END
END

GO
CREATE OR ALTER PROCEDURE deleteDonations AS
BEGIN
	DECLARE @int_max INT = (SELECT POWER(2., 31) - 1);
	DELETE FROM Donations
	WHERE amount = @int_max;
END

GO
CREATE OR ALTER PROCEDURE testRunViewsProc AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @start DATETIME;
	DECLARE @end DATETIME;
	DECLARE @view INT;

	SELECT @view = ViewID FROM Views WHERE Name = 'ViewSponsors';
	SET @start = SYSDATETIME();
	SELECT * FROM ViewSponsors;
	SET @end = SYSDATETIME(); 
	PRINT ('ViewSponsors test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('ViewSponsors Test', @start, @end)
    INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@@IDENTITY, @view, @start, @end);

	SELECT @view = ViewID FROM Views WHERE Name = 'ViewOrganisersContests';
	SET @start = SYSDATETIME();
	SELECT * FROM ViewOrganisersContests;
	SET @end = SYSDATETIME();
	PRINT ('ViewOrganisersContests test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('ViewOrganisersContests Test', @start, @end)
    INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@@IDENTITY, @view, @start, @end);

	SELECT @view = ViewID FROM Views WHERE Name = 'ViewSponsorsNumberOfContests';
	SET @start = SYSDATETIME();
	SELECT * FROM ViewSponsorsNumberOfContests;
	SET @end = SYSDATETIME();
	PRINT ('ViewSponsorsNumberOfContests test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('ViewSponsorsNumberOfContests Test', @start, @end)
    INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@@IDENTITY, @view, @start, @end);
END

GO
CREATE OR ALTER PROCEDURE testRunDeletesProc AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @start DATETIME;
	DECLARE @end DATETIME;
	DECLARE @table INT;

	SELECT @table = TableID FROM Tables WHERE Name = 'Donations';
	SET @start = SYSDATETIME();
	EXEC deleteDonations;
	SET @end = SYSDATETIME(); 
	PRINT ('deleteDonations test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('deleteDonations Test', @start, @end)
    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@@IDENTITY, @table, @start, @end);

	SELECT @table = TableID FROM Tables WHERE Name = 'Contests';
	SET @start = SYSDATETIME();
	EXEC deleteContests;
	SET @end = SYSDATETIME(); 
	PRINT ('deleteContests test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('deleteContests Test', @start, @end)
    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@@IDENTITY, @table, @start, @end);

	SELECT @table = TableID FROM Tables WHERE Name = 'Sponsors';
	SET @start = SYSDATETIME();
	EXEC deleteSponsors;
	SET @end = SYSDATETIME(); 
	PRINT ('deleteSponsors test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('deleteSponsors Test', @start, @end)
    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@@IDENTITY, @table, @start, @end);
END

GO
CREATE OR ALTER PROCEDURE testRunInsertsProc AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @start DATETIME;
	DECLARE @end DATETIME;
	DECLARE @table INT;

	SELECT @table = TableID FROM Tables WHERE Name = 'Sponsors';
	SET @start = SYSDATETIME();
	EXEC insertSponsors;
	SET @end = SYSDATETIME(); 
	PRINT ('insertSponsors test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('insertSponsors Test', @start, @end)
    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@@IDENTITY, @table, @start, @end);

	SELECT @table = TableID FROM Tables WHERE Name = 'Contests';
	SET @start = SYSDATETIME();
	EXEC insertContests;
	SET @end = SYSDATETIME(); 
	PRINT ('insertContests test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('insertContests Test', @start, @end)
    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@@IDENTITY, @table, @start, @end);

	SELECT @table = TableID FROM Tables WHERE Name = 'Donations';
	SET @start = SYSDATETIME();
	EXEC insertDonations;
	SET @end = SYSDATETIME(); 
	PRINT ('insertDonations test time: ' + CAST(DATEDIFF(ms, @start, @end) AS VARCHAR) + ' ms')
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES ('insertDonations Test', @start, @end)
    INSERT INTO TestRunTables(TestRunID, TableID, StartAt, EndAt) VALUES (@@IDENTITY, @table, @start, @end);
END
GO

EXEC testRunViewsProc;
EXEC testRunDeletesProc;
EXEC testRunInsertsProc;

SELECT * FROM TestRuns;