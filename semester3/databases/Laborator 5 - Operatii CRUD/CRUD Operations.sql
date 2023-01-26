/*
	CRUD Operations for at least 3 tables (at least one many-to-many relation)
Used tables:	- Contests (2 FG KEYS, not related to the other tables)
				- Sponsors (0 FG KEYS)
				- Donations (2 FG KEYS - connection table for Contests && Sponsors)
*/

USE Contests;
GO;

GO
/* Function for validating a contest based on the input data
  will return 1 if the contest is valid, 0 otherwise */
CREATE OR ALTER FUNCTION [dbo].[Validate_Contest](
	@name VARCHAR(100), --should not be NULL
	@type VARCHAR(100), --should not be NULL
	@subject VARCHAR(100), --should not be NULL
	@reservation_id INT, --foreign key, referencing the Reservations table
	@organiser_id INT --foreign key, referencing the Organisers table, should not be NULL
	) RETURNS INT AS BEGIN

	DECLARE @reservations_count INT;
	SELECT @reservations_count=COUNT(*) FROM Reservations WHERE reservation_id = @reservation_id;
	DECLARE @organisers_count INT;
	SELECT @organisers_count=COUNT(*) FROM Organisers WHERE organiser_id = @organiser_id;

	IF (@name is NULL OR @type IS NULL OR @subject IS NULL OR @organiser_id IS NULL 
		OR (@reservation_id IS NOT NULL AND @reservations_count = 0) OR (@organisers_count = 0))
		RETURN 0;
	RETURN 1;
END
GO

SELECT [dbo].[Validate_Contest](
	'asds', 'asfasf', 'asfgsag', NULL, 80000);

GO
CREATE OR ALTER PROCEDURE [dbo].[CRUD_Contests]
	@name VARCHAR(100),
	@type VARCHAR(100),
	@subject VARCHAR(100),
	@reservation_id INT,
	@organiser_id INT 
AS BEGIN
	--SET NOCOUNT ON;
	
	-- verify the parameters
	DECLARE @validation_status INT;
	SELECT @validation_status = [dbo].[Validate_Contest](@name, @type, @subject, @reservation_id, @organiser_id);

	IF (@validation_status = 0)
	BEGIN
		RAISERROR(N'Invalid parameters given to CRUD_Contests procedure', 16, 1);
		RETURN;
	END
	-- CREATE = INSERT
	INSERT INTO Contests(name, type, subject, reservation_id, organiser_id)
	VALUES (@name, @type, @subject, @reservation_id, @organiser_id);
	DECLARE @contest_id INT=@@IDENTITY;
	PRINT(N'Succesfully created the contest with the identifier ' + CAST(@contest_id AS VARCHAR(20)) + '!');

	-- READ = SELECT
	SELECT * FROM Contests
	WHERE contest_id = @contest_id;
	PRINT(N'Succesfully printed the contest with the identifier ' + CAST(@contest_id AS VARCHAR(20)) + '!');

	-- UPDATE
	UPDATE Contests
	SET name = 'Updated' + @name
	WHERE contest_id = @contest_id;
	PRINT(N'Succesfully updated the contest with the identifier ' + CAST(@contest_id AS VARCHAR(20)) + '!');

	-- DELETE
	DELETE FROM Contests
	WHERE contest_id = @contest_id;
	PRINT(N'Succesfully deleted the contest with the identifier ' + CAST(@contest_id AS VARCHAR(20)) + '!');
END
GO

EXEC [dbo].[CRUD_Contests] 'Contest Name', 'Contest Type', 'Contest Subject', NULL, 80000

GO
/* Function for validating a sponsor based on the input data
  will return 1 if the sponsor is valid, 0 otherwise */
CREATE OR ALTER FUNCTION [dbo].[Validate_Sponsor](
	@name VARCHAR(100) --should not be NULL
	) RETURNS INT AS
BEGIN
	IF (@name IS NULL)
		RETURN 0;
	RETURN 1;
END
GO

GO
CREATE OR ALTER PROCEDURE [dbo].[CRUD_Sponsors]
	@name VARCHAR(100)
AS BEGIN
	--SET NOCOUNT ON;
	
	-- verify the parameters
	DECLARE @validation_status INT;
	SELECT @validation_status = [dbo].[Validate_Sponsor](@name);

	IF (@validation_status = 0)
	BEGIN
		RAISERROR(N'Invalid parameters given to CRUD_Sponsors procedure', 16, 1);
		RETURN;
	END
	-- CREATE = INSERT
	INSERT INTO Sponsors(name)
	VALUES (@name);
	DECLARE @sponsor_id INT=@@IDENTITY;
	PRINT(N'Succesfully created the sponsor with the identifier ' + CAST(@sponsor_id AS VARCHAR(20)) + '!');

	-- READ = SELECT
	SELECT * FROM Sponsors
	WHERE sponsor_id = @sponsor_id;
	PRINT(N'Succesfully printed the sponsor with the identifier ' + CAST(@sponsor_id AS VARCHAR(20)) + '!');

	-- UPDATE
	UPDATE Sponsors
	SET name = 'Updated' + @name
	WHERE sponsor_id = @sponsor_id;
	PRINT(N'Succesfully updated the sponsor with the identifier ' + CAST(@sponsor_id AS VARCHAR(20)) + '!');

	-- DELETE
	DELETE FROM Sponsors
	WHERE sponsor_id = @sponsor_id;
	PRINT(N'Succesfully deleted the sponsor with the identifier ' + CAST(@sponsor_id AS VARCHAR(20)) + '!');
END
GO

EXEC [dbo].[CRUD_Sponsors] 'Marius'


GO
/* Function for validating a donation based on the input data
  will return 1 if the donation is valid, 0 otherwise */
CREATE OR ALTER FUNCTION [dbo].[Validate_Donation](
	@sponsor_id INT, --foreign key, referencing the Sponsors table
	@contest_id INT, --foreign key, referencing the Contests table
	@amount INT --should be positive
	) RETURNS INT AS
BEGIN
	DECLARE @sponsors_count INT;
	SELECT @sponsors_count=COUNT(*) FROM Sponsors WHERE sponsor_id = @sponsor_id;
	DECLARE @contests_count INT;
	SELECT @contests_count=COUNT(*) FROM Contests WHERE contest_id = @contest_id;
	DECLARE @donations_count INT;
	SELECT @donations_count=COUNT(*) FROM Donations WHERE sponsor_id = @sponsor_id AND contest_id = @contest_id;

	IF (@amount <= 0 OR @sponsors_count = 0 OR @contests_count = 0 OR @donations_count != 0)
		RETURN 0;
	RETURN 1;
END
GO

GO
CREATE OR ALTER PROCEDURE [dbo].[CRUD_Donations]
	@sponsor_id INT,
	@contest_id INT,
	@amount INT
AS BEGIN
	--SET NOCOUNT ON;
	
	-- verify the parameters
	DECLARE @validation_status INT;
	SELECT @validation_status = [dbo].[Validate_Donation](@sponsor_id, @contest_id, @amount);

	IF (@validation_status = 0)
	BEGIN
		RAISERROR(N'Invalid parameters given to CRUD_Donations procedure', 16, 1);
		RETURN;
	END
	-- CREATE = INSERT
	INSERT INTO Donations(sponsor_id, contest_id, amount)
	VALUES (@sponsor_id, @contest_id, @amount);
	PRINT(N'Succesfully created the donation (' + CAST(@sponsor_id AS VARCHAR(20)) + ', ' + CAST(@contest_id AS VARCHAR(20)) + ')!');

	-- READ = SELECT
	SELECT * FROM Donations
	WHERE sponsor_id = @sponsor_id AND contest_id = @contest_id;
	PRINT(N'Succesfully printed the donation (' + CAST(@sponsor_id AS VARCHAR(20)) + ', ' + CAST(@contest_id AS VARCHAR(20)) + ')!');

	-- UPDATE
	UPDATE Donations
	SET amount = amount / 2 + 1
	WHERE sponsor_id = @sponsor_id AND contest_id = @contest_id;
	PRINT(N'Succesfully updated the donation (' + CAST(@sponsor_id AS VARCHAR(20)) + ', ' + CAST(@contest_id AS VARCHAR(20)) + ')!');

	-- DELETE
	DELETE FROM Donations
	WHERE sponsor_id = @sponsor_id AND contest_id = @contest_id;
	PRINT(N'Succesfully deleted the donation (' + CAST(@sponsor_id AS VARCHAR(20)) + ', ' + CAST(@contest_id AS VARCHAR(20)) + ')!');
END
GO

INSERT INTO Sponsors(name)
VALUES ('Societatea tuturor matematicienilor');

EXEC [dbo].[CRUD_Donations] 30002, 10000, 120

GO
USE Contests
GO

-- VIEWS
GO
-- prints the name of each student and the average of their result
CREATE OR ALTER VIEW viewStudentAverageResult
AS SELECT S.name AS student, AVG(R.score) AS result 
FROM Students S
INNER JOIN Results R
ON R.student_id = S.student_id
GROUP BY S.name
GO

SELECT * FROM Problems;

GO
CREATE OR ALTER VIEW viewMathContests
AS SELECT C.name AS contest
FROM Contests C
WHERE C.subject = 'mathematics';
GO

SELECT * FROM Contests;

-- INDEXES
IF EXISTS(SELECT name FROM sys.indexes WHERE name ='N_idx_result_student_id')
	DROP INDEX N_idx_result_student_id ON Results;
CREATE NONCLUSTERED INDEX N_idx_result_student_id ON Results(student_id);

IF EXISTS(SELECT name FROM sys.indexes WHERE name ='N_idx_student_name')
	DROP INDEX N_idx_student_name ON Students;
CREATE NONCLUSTERED INDEX N_idx_student_name ON Students(name);

SELECT * FROM viewStudentAverageResult;



IF EXISTS(SELECT name FROM sys.indexes WHERE name = 'N_idx_contest_name_subject')
	DROP INDEX N_idx_contest_name_subject ON Contests;
CREATE NONCLUSTERED INDEX N_idx_contest_name_subject ON Contests(name, subject);

SELECT * FROM viewMathContests;