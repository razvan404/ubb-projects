USE Contests;
GO

-- Cream tabela cu versiunea curenta a bazei de date
CREATE TABLE Versions (
	version INT PRIMARY KEY,
	last_change DATETIME DEFAULT GETDATE()
);

INSERT INTO Versions(version)
VALUES (0);

GO
-- do_proc_1, modifica tipul unei coloane
ALTER PROCEDURE do_proc_1 AS
BEGIN
	ALTER TABLE Sponsors
	ALTER COLUMN name NVARCHAR(100)
	PRINT N'Sponsors table: name column type was updated to nvarchar(100)' 
	UPDATE Versions SET version = 1, last_change = GETDATE()
END
GO

GO
-- undo_proc_1, anuleaza modificarea tipului de coloane
ALTER PROCEDURE undo_proc_1 AS
BEGIN
	ALTER TABLE Sponsors
	ALTER COLUMN name VARCHAR(100)
	PRINT N'Sponsors table: name column type was updated to varchar(100)'
	UPDATE Versions SET version = 0, last_change = GETDATE()
END
GO

GO
-- do_proc_2, adauga o costrangere de "valoare implicita" pentru un camp
ALTER PROCEDURE do_proc_2 AS
BEGIN
	ALTER TABLE Sponsors
	ADD CONSTRAINT df_name DEFAULT (N'Anonymous Sponsor') FOR name
	PRINT N'Sponsors table: name column have a default value'
	UPDATE Versions SET version = 2, last_change = GETDATE()
END
GO

GO
-- undo_proc_2, sterge constrangerea de "valoare implicita" pentru un camp
ALTER PROCEDURE undo_proc_2 AS
BEGIN
	ALTER TABLE Sponsors
	DROP CONSTRAINT df_name;
	PRINT N'Sponsors table: name column does not have a default value anymore'
	UPDATE Versions SET version = 1, last_change = GETDATE()
END
GO

GO
-- do_proc_3, creeaza o tabela noua
ALTER PROCEDURE do_proc_3 AS
BEGIN
	CREATE TABLE StudentCards (
		student_id INT PRIMARY KEY,
		phone INT CHECK (phone >= 100000000 AND phone < 999999999),
		address VARCHAR(100)
	)
	PRINT N'StudentCards table: the table was created'
	UPDATE Versions SET version = 3, last_change = GETDATE()
END
GO

GO
-- undo_proc_3, sterge o tabela
ALTER PROCEDURE undo_proc_3 AS
BEGIN
	DROP TABLE StudentCards
	PRINT N'StudentCards table: the table was dropped'
	UPDATE Versions SET version = 2, last_change = GETDATE()
END
GO

GO
-- do_proc_4, adauga un camp nou
ALTER PROCEDURE do_proc_4 AS
BEGIN
	ALTER TABLE StudentCards
	ADD current_year SMALLINT
	PRINT N'StudentCards table: current_year column added'
	UPDATE Versions SET version = 4, last_change = GETDATE()
END
GO

GO
-- undo_proc_4, eliminare camp existent
ALTER PROCEDURE undo_proc_4 AS
BEGIN
	ALTER TABLE StudentCards
	DROP COLUMN current_year
	PRINT N'StudentCards table: current_year column removed'
	UPDATE Versions SET version = 3, last_change = GETDATE()
END
GO

GO
-- do_proc_5, creeaza o constrangere de "cheie straina" pentru un camp
ALTER PROCEDURE do_proc_5 AS
BEGIN
	ALTER TABLE StudentCards
	ADD CONSTRAINT fk_student_id FOREIGN KEY(student_id) REFERENCES Students(student_id)
	PRINT N'StudentCards table: student_id column now references student_id column from Students table'
	UPDATE Versions SET version = 5, last_change = GETDATE()
END
GO

GO
-- undo_proc_2, sterge constrangerea de "cheie straina" pentru un camp
ALTER PROCEDURE undo_proc_5 AS
BEGIN
	ALTER TABLE StudentCards
	DROP CONSTRAINT fk_student_id;
	PRINT N'StudentCards table: student_id column no longer references student_id column from Students table'
	UPDATE Versions SET version = 4, last_change = GETDATE()
END
GO

GO
-- updates the database to a certain version
ALTER PROCEDURE update_to_version @new_version INT AS
BEGIN
	SET NOCOUNT ON

	DECLARE @old_version INT
	DECLARE @current_version INT
	DECLARE @procedure VARCHAR(30)
	
	SELECT @current_version = version FROM Versions
	SET @old_version = @current_version 

	IF @new_version > 5 OR @new_version < 0
		RAISERROR(N'Invalid version, must be between 0 and 5!', 16, 1)
	ELSE IF @current_version < @new_version
		BEGIN
			WHILE @current_version < @new_version
			BEGIN
				SET @current_version = @current_version + 1
				SET @procedure = 'do_proc_' + CONVERT(VARCHAR, @current_version)
				EXEC @procedure
			END
			PRINT CHAR(10) + 'Successfully updated from version ' + CONVERT(VARCHAR, @old_version)
				+ ' to version ' + CONVERT(VARCHAR, @new_version) + '!'
		END
	ELSE IF @current_version > @new_version
		BEGIN
			WHILE @current_version > @new_version
			BEGIN
				SET @procedure = 'undo_proc_' + CONVERT(VARCHAR, @current_version)
				EXEC @procedure
				SET @current_version = @current_version - 1
			END
			PRINT CHAR(10) + 'Successfully updated from version ' + CONVERT(VARCHAR, @old_version)
				+ ' to version ' + CONVERT(VARCHAR, @new_version) + '!'
		END
	ELSE
		RAISERROR(N'Cannot update to the specified version because it is already in use!', 16, 1)
END
GO

EXEC update_to_version 12
SELECT * FROM Versions