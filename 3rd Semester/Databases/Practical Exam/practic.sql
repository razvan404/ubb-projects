CREATE DATABASE ConstructiiManagement;
GO

USE ConstructiiManagement;
GO


-- CREAREA TABELELOR --

CREATE TABLE TipuriMagazine (
	tip NVARCHAR(50) PRIMARY KEY,
	descriere NVARCHAR(250)
);

CREATE TABLE Magazine (
	id_magazin INT IDENTITY PRIMARY KEY,
	denumire NVARCHAR(50),
	strada NVARCHAR(100),
	numar INT,
	localitate NVARCHAR(75),
	tip NVARCHAR(50) FOREIGN KEY REFERENCES TipuriMagazine(tip)
);

CREATE TABLE Furnizori (
	id_furnizor INT IDENTITY PRIMARY KEY,
	nume NVARCHAR(50),
	prenume NVARCHAR(50),
	gen NVARCHAR(20),
	vechime INT
);

CREATE TABLE Materiale (
	id_material INT IDENTITY PRIMARY KEY,
	denumire NVARCHAR(50),
	pret INT CHECK (pret >= 0),
	cantitate INT CHECK (cantitate >= 0),
	id_furnizor INT FOREIGN KEY REFERENCES Furnizori(id_furnizor)
);

CREATE TABLE Livrari (
	id_magazin INT NOT NULL FOREIGN KEY REFERENCES Magazine(id_magazin),
	id_furnizor INT NOT NULL FOREIGN KEY REFERENCES Furnizori(id_furnizor),
	data_livrarii DATE,
	cantitate INT CHECK (cantitate >= 0),
);

ALTER TABLE Livrari
ADD PRIMARY KEY (id_magazin, id_furnizor);

-- INSERAREA DATELOR --
INSERT INTO TipuriMagazine(tip, descriere)
VALUES	('tip 1', 'descrierea tipului 1'),
		('tip 2', 'descrierea tipului 2'),
		('tip 3', 'descrierea tipului 3');

INSERT INTO Magazine(denumire, strada, numar, localitate, tip)
VALUES	('magazin 1', 'strada 1', 1, 'localitate 1', 'tip 1'),
		('magazin 2', 'strada 2', 2, 'localitate 2', 'tip 2'),
		('magazin 3', 'strada 3', 3, 'localitate 3', 'tip 3'),
		('magazin 4', 'strada 4', 4, 'localitate 1', 'tip 1'),
		('magazin 5', 'strada 5', 5, 'localitate 2', 'tip 2'),
		('magazin 6', 'strada 6', 6, 'localitate 3', 'tip 3'),
		('magazin 7', 'strada 7', 7, 'localitate 1', 'tip 1'),
		('magazin 8', 'strada 8', 8, 'localitate 2', 'tip 2'),
		('magazin 9', 'strada 9', 9, 'localitate 3', 'tip 3');

INSERT INTO Furnizori(nume, prenume, gen, vechime)
VALUES	('nume 1', 'prenume 1', 'masculin', 1),
		('nume 2', 'prenume 2', 'masculin', 2),
		('nume 3', 'prenume 3', 'masculin', 3),
		('nume 4', 'prenume 4', 'non-binar', 4),
		('nume 5', 'prenume 5', 'non-binar', 5),
		('nume 6', 'prenume 6', 'feminin', 6);

INSERT INTO Materiale(denumire, pret, cantitate, id_furnizor)
VALUES	('material 1.1', 110, 11, 1), ('material 1.2', 120, 12, 1),
		('material 2.1', 210, 21, 2), ('material 2.2', 220, 22, 2),
		('material 3.1', 310, 31, 3), ('material 3.2', 320, 32, 3),
		('material 4.1', 410, 41, 4), ('material 4.2', 420, 42, 4),
		('material 5.1', 510, 51, 5), ('material 5.2', 520, 52, 5),
		('material 6.1', 610, 61, 6), ('material 6.2', 620, 62, 6);

INSERT INTO Livrari(id_magazin, id_furnizor, data_livrarii, cantitate)
VALUES	(1, 1, '2023-01-01', 11), (1, 2, '2023-01-02', 12), (1, 3, '2023-01-03', 13),
		(2, 2, '2023-01-02', 12), (2, 3, '2023-01-03', 13), (2, 4, '2023-01-04', 14),
		(3, 3, '2023-01-03', 13), (3, 4, '2023-01-04', 14), (3, 5, '2023-01-05', 15),
		(4, 4, '2023-01-04', 14), (4, 5, '2023-01-05', 15), (4, 6, '2023-01-06', 16),
		(5, 1, '2023-01-01', 11), (5, 3, '2023-01-03', 13), (5, 5, '2023-01-05', 15),
		(6, 2, '2023-01-02', 12), (6, 3, '2023-01-03', 13), (6, 4, '2023-01-04', 14);

-- PROCEDURA STOCATA --

GO
CREATE OR ALTER PROCEDURE upsert_livrare
	@id_magazin INT,
	@id_furnizor INT,
	@data_livrare DATE,
	@cantitate INT
AS BEGIN
	DECLARE @numar_furnizori INT;
	DECLARE @numar_magazine INT;
	DECLARE @numar_livrari INT;

	SELECT @numar_furnizori = COUNT(*) FROM Furnizori WHERE id_furnizor = @id_furnizor;
	SELECT @numar_magazine = COUNT(*) FROM Magazine WHERE id_magazin = @id_magazin;
	SELECT @numar_livrari = COUNT(*) FROM Livrari WHERE id_furnizor = @id_furnizor AND id_magazin = @id_magazin;

	IF @numar_furnizori = 0
	BEGIN
		RAISERROR(N'ID furnizor invalid!', 16, 1);
		RETURN;
	END

	IF @numar_magazine = 0
	BEGIN
		RAISERROR(N'ID magazin invalid!', 16, 1);
		RETURN;
	END

	IF @numar_livrari = 0
		INSERT INTO Livrari(id_magazin, id_furnizor, data_livrarii, cantitate) 
		VALUES (@id_magazin, @id_furnizor, @data_livrare, @cantitate);
	ELSE
		UPDATE Livrari
		SET data_livrarii = @data_livrare, cantitate = @cantitate
		WHERE id_magazin = @id_magazin AND id_furnizor = @id_furnizor
END;
GO

SELECT * FROM Livrari;
EXEC upsert_livrare 100, 4, '2023-01-04', 15;
EXEC upsert_livrare 6, 4, '2023-01-04', 100;
EXEC upsert_livrare 7, 3, '2023-01-03', 13;
DELETE FROM Livrari WHERE id_magazin = 7 AND id_furnizor = 3;

-- FUNCTIA --
GO
CREATE OR ALTER FUNCTION dbo.furnizor_la_n_magazine(@n INT)
RETURNS TABLE AS
	RETURN SELECT nume + ' ' + prenume AS furnizor, COUNT(id_magazin) AS numar_magazine
	FROM Furnizori F
	INNER JOIN Livrari L ON F.id_furnizor = L.id_furnizor
	GROUP BY nume, prenume
	HAVING COUNT(id_magazin) >= @n
GO

SELECT * FROM dbo.furnizor_la_n_magazine(3);