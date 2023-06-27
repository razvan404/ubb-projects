USE Contests;
GO

-- Jurnalizare
CREATE TABLE Logs (
	log_id INT IDENTITY,
	method VARCHAR(50),
	type VARCHAR(16),
	message VARCHAR(256),
	date DATETIME DEFAULT GETDATE()
);
GO
CREATE OR ALTER PROC InsertLog
	@method VARCHAR(50),
	@type VARCHAR(16),
	@message VARCHAR(256) AS
BEGIN
	INSERT INTO Logs(method, type, message)
	VALUES (@method, @type, @message);
END
GO

-- Varianta in care se anuleaza toata tranzactia in cazul unei erori
CREATE OR ALTER PROC InsertContestSponsorDonationFull
	@contest_name VARCHAR(100), -- should not be NULL
	@contest_type VARCHAR(100), -- should not be NULL
	@contest_subject VARCHAR(100), -- should not be NULL
	@contest_reservation_id INT, -- foreign key, referecing the Reservations table, could be null
	@contest_organiser_id INT, -- foreign key, referencing the Organisers table, should not be NULL
	@sponsor_name VARCHAR(100), -- should not be NULL
	@donation_amount INT AS -- should be positive
BEGIN
	SET NOCOUNT ON;
	EXEC InsertLog 'InsertContestSponsorDonationFull', 'Information', 'Transaction began';
	PRINT('Transaction began');
	DECLARE @validation_status INT;
	BEGIN TRAN;
	BEGIN TRY
		-- Validare Concurs
		SELECT @validation_status = [dbo].[Validate_Contest](@contest_name,
			@contest_type, @contest_subject, @contest_reservation_id, @contest_organiser_id);
		IF (@validation_status = 0)
			RAISERROR(N'Invalid contest data', 16, 1);
		ELSE
			INSERT INTO Contests(name, type, subject, reservation_id, organiser_id)
			VALUES (@contest_name, @contest_type, @contest_subject, @contest_reservation_id, @contest_organiser_id);

		-- Validare Sponsor
		SELECT @validation_status = [dbo].[Validate_Sponsor](@sponsor_name)
		IF (@validation_status = 0)
			RAISERROR(N'Invalid sponsor data', 16, 1);
		ELSE
			INSERT INTO Sponsors(name) VALUES (@sponsor_name);
		
		DECLARE @contest_id INT;
		SELECT @contest_id = MAX(contest_id) FROM Contests;
		DECLARE @sponsor_id INT;
		SELECT @sponsor_id = MAX(sponsor_id) FROM Sponsors;

		-- Validare Donatie
		SELECT @validation_status = [dbo].[Validate_Donation](@sponsor_id, @contest_id, @donation_amount);
		IF (@validation_status = 0)
			RAISERROR(N'Invalid donation data', 16, 1);
		ELSE
			INSERT INTO Donations(sponsor_id, contest_id, amount)
			VALUES (@sponsor_id, @contest_id, @donation_amount);

		-- Tranzactia s-a efectuat cu succes
		COMMIT TRAN;
		EXEC InsertLog 'InsertContestSponsorDonationFull', 'Success', 'Transaction commited successfully';
		PRINT('Transaction commited successfully');
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN;
		DECLARE @message VARCHAR(256);
		SELECT @message = 'Transaction rollbacked: ' + ERROR_MESSAGE();
		EXEC InsertLog 'InsertContestSponsorDonationFull', 'Failed', @message;
		PRINT(@message);
	END CATCH
END
GO

SELECT * FROM Organisers;

-- Exemple pentru InsertContestSponsorDonationFull
EXEC InsertContestSponsorDonationFull 'Nume valid', 'Tip valid', 'Subiect valid', NULL, 80000, 
									  'Sponsor valid', 404
EXEC InsertContestSponsorDonationFull 'Nume valid', NULL, 'Subiect valid', NULL, 80000, 
									  'Sponsor valid', 404
EXEC InsertContestSponsorDonationFull 'Nume valid', 'Tip valid', 'Subiect valid', NULL, 80000, 
									  NULL, 404
EXEC InsertContestSponsorDonationFull 'Nume valid', 'Tip valid', 'Subiect valid', NULL, 80000, 
									  'Sponsor valid', -404
SELECT * FROM Contests WHERE contest_id = (SELECT MAX(contest_id) FROM Contests);
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
SELECT * FROM Donations WHERE contest_id = (SELECT MAX(contest_id) FROM Contests)
						OR sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
	
GO
-- Varianta in care se anuleaza partial tranzactia in cazul unei erori,
-- in functie de locul unde s-a produs eroarea, tranzactia poate continua
CREATE OR ALTER PROC InsertContestSponsorDonationPartial
	@contest_name VARCHAR(100), -- should not be NULL
	@contest_type VARCHAR(100), -- should not be NULL
	@contest_subject VARCHAR(100), -- should not be NULL
	@contest_reservation_id INT, -- foreign key, referecing the Reservations table, could be null
	@contest_organiser_id INT, -- foreign key, referencing the Organisers table, should not be NULL
	@sponsor_name VARCHAR(100), -- should not be NULL
	@donation_amount INT AS -- should be positive
BEGIN
	SET NOCOUNT ON;
	DECLARE @validation_status INT;
	DECLARE @message VARCHAR(256);
	BEGIN TRAN;
	EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Information', 'Contest transaction began.';
	PRINT('Contest transaction began.');
	BEGIN TRY
		-- Validare Concurs
		SELECT @validation_status = [dbo].[Validate_Contest](@contest_name,
			@contest_type, @contest_subject, @contest_reservation_id, @contest_organiser_id);
		IF (@validation_status = 0)
			RAISERROR(N'Invalid contest data', 16, 1);
		ELSE
			INSERT INTO Contests(name, type, subject, reservation_id, organiser_id)
			VALUES (@contest_name, @contest_type, @contest_subject, @contest_reservation_id, @contest_organiser_id);

		-- Tranzactia s-a efectuat cu succes
		COMMIT TRAN;
		EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Success', 'Contest transaction commited successfully.';
		PRINT('Contest transaction commited successfully.');
	END TRY
	BEGIN CATCH
		-- Tranzactia a esuat
		ROLLBACK TRAN;
		SELECT @message = 'Contest transaction rollbacked. Error message: ' + ERROR_MESSAGE();
		EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Failed', @message;
		PRINT(@message);
	END CATCH
	
	-- Validare Sponsor
	BEGIN TRAN;
	EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Information', 'Sponsor transaction began.';
	PRINT('Sponsor transaction began.');
	BEGIN TRY
		SELECT @validation_status = [dbo].[Validate_Sponsor](@sponsor_name)
		IF (@validation_status = 0)
			RAISERROR(N'Invalid sponsor data', 16, 1);
		ELSE
			INSERT INTO Sponsors(name) VALUES (@sponsor_name);

		-- Tranzactia s-a efectuat cu succes
		COMMIT TRAN;
		EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Success', 'Sponsor transaction commited successfully.';
		PRINT('Sponsor transaction commited successfully.');
	END TRY
	BEGIN CATCH
		-- Tranzactia a esuat
		ROLLBACK TRAN;
		SELECT @message = 'Sponsor transaction rollbacked. Error message: ' + ERROR_MESSAGE();
		EXEC InsertLog 'InsertContestSponsorDonationFull', 'Failed', @message;
		PRINT(@message);
	END CATCH

	BEGIN TRAN;
	EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Information', 'Donation transaction began.';
	PRINT('Donation transaction began.');
	BEGIN TRY
		DECLARE @contest_id INT;
		SELECT @contest_id = MAX(contest_id) FROM Contests;
		DECLARE @sponsor_id INT;
		SELECT @sponsor_id = MAX(sponsor_id) FROM Sponsors;

		-- Validare Donatie
		SELECT @validation_status = [dbo].[Validate_Donation](@sponsor_id, @contest_id, @donation_amount);
		IF (@validation_status = 0)
			RAISERROR(N'Invalid donation data', 16, 1);
		ELSE
			INSERT INTO Donations(sponsor_id, contest_id, amount)
			VALUES (@sponsor_id, @contest_id, @donation_amount);

		-- Tranzactia s-a efectuat cu succes
		COMMIT TRAN;
		EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Success', 'Donation transaction commited successfully.';
		PRINT('Donation transaction commited successfully.');
	END TRY
	BEGIN CATCH
		-- Tranzactia a esuat
		ROLLBACK TRAN;
		SELECT @message = 'Donation transaction rollbacked. Error message: ' + ERROR_MESSAGE();
		EXEC InsertLog 'InsertContestSponsorDonationPartial', 'Failed', @message;
		PRINT(@message);
	END CATCH
END
GO

-- Exemple pentru InsertContestSponsorDonationPartial
EXEC InsertContestSponsorDonationPartial 'Nume valid', 'Tip valid', 'Subiect valid', NULL, 80000, 
									  'Sponsor valid', 404
EXEC InsertContestSponsorDonationPartial 'Nume valid', NULL, 'Subiect valid', NULL, 80000, 
									  'Sponsor valid', 404
EXEC InsertContestSponsorDonationPartial 'Nume valid', 'Tip valid', 'Subiect valid', NULL, 80000, 
									  NULL, 404
EXEC InsertContestSponsorDonationPartial 'Nume valid', 'Tip valid', 'Subiect valid', NULL, 80000, 
									  'Sponsor valid', -404
EXEC InsertContestSponsorDonationPartial 'Nume valid', NULL, 'Subiect Valid', NULL, 80000,
									  NULL, -404
SELECT * FROM Contests WHERE contest_id = (SELECT MAX(contest_id) FROM Contests);
SELECT * FROM Sponsors WHERE sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);
SELECT * FROM Donations WHERE contest_id = (SELECT MAX(contest_id) FROM Contests)
						OR sponsor_id = (SELECT MAX(sponsor_id) FROM Sponsors);

-- Clean data
DELETE FROM Donations WHERE contest_id IN (SELECT contest_id FROM Contests WHERE subject = 'Subiect valid')
					  OR sponsor_id IN (SELECT sponsor_id FROM Sponsors where name = 'Sponsor valid');
DELETE FROM Sponsors WHERE name = 'Sponsor valid';
DELETE FROM Contests WHERE subject = 'Subiect valid';
