USE Contests
GO

-- Update Transactions --
DELETE FROM Sponsors
WHERE sponsor_id > 30007;

-- Dirty Reads --
BEGIN TRAN;
UPDATE Sponsors
SET name = 'Dirty' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
WAITFOR DELAY '00:00:05';
ROLLBACK TRAN;

-- Unrepeatable Reads --
BEGIN TRAN;
WAITFOR DELAY '00:00:05';
UPDATE Sponsors
SET name = 'Unrepeatable' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
COMMIT TRAN;

-- Phantom Reads --
DELETE FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
SELECT * FROM Sponsors;

BEGIN TRAN;
WAITFOR DELAY '00:00:05';
INSERT INTO Sponsors(name) VALUES ('Phantom404');
COMMIT TRAN;

-- Deadlock --
GO
CREATE OR ALTER PROC deadlock_transaction1 AS
BEGIN
	BEGIN TRAN;
	-- locking Sponsors
	UPDATE Sponsors
	SET name = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
	WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
	WAITFOR DELAY '00:00:05';
	-- trying to access resource from Organisers
	UPDATE Organisers
	SET name = 'Deadlock' + CONVERT(VARCHAR(3), ABS(CHECKSUM(NEWID()) % 300) + 1)
	WHERE organiser_id = (SELECT MAX(organiser_id) FROM Organisers);
	COMMIT TRAN;
END;
GO

EXEC deadlock_transaction1;
