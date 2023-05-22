USE Contests;
GO

-- Read Transactions --

-- Dirty Reads --
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED -- dirty reads
-- SET TRANSACTION ISOLATION LEVEL READ COMMITED -- dirty reads solution
BEGIN TRAN;
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
WAITFOR DELAY '00:00:05';
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
COMMIT TRAN;

-- Unrepeatable Reads--
SET TRANSACTION ISOLATION LEVEL READ COMMITTED -- unrepeatable reads
-- SET TRANSACTION ISOLATION LEVEL REPEATABLE READ -- unrepeatable reads solution
BEGIN TRAN;
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
WAITFOR DELAY '00:00:05';
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
COMMIT TRAN;

-- Phantom Reads --
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ -- phantom reads
-- SET TRANSACTION ISOLATION LEVEL SERIALIZABLE -- phantom reads solutions
BEGIN TRAN;
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
WAITFOR DELAY '00:00:05';
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
COMMIT TRAN;

-- Deadlock --
GO
CREATE OR ALTER PROC deadlock_transaction2 AS
BEGIN
	SET DEADLOCK_PRIORITY NORMAL; -- deadlock
	-- SET DEADLOCK_PRIORITY HIGH; -- solutie deadlock
	BEGIN TRAN;
	-- locking Organisers
	UPDATE Organisers
	SET name = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
	WHERE organiser_id = (SELECT MAX(organiser_id) FROM Organisers);
	WAITFOR DELAY '00:00:05';
	-- trying to access resource from Sponsors
	UPDATE Sponsors
	SET name = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
	WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
	COMMIT TRAN;
END;
GO

EXEC deadlock_transaction2;

SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
SELECT * FROM Organisers WHERE organiser_id = (SELECT MAX(organiser_id) FROM Organisers);
