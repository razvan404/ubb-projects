USE master;
GO
DROP DATABASE Contests;
GO

CREATE DATABASE Contests;
GO
USE Contests;
GO

CREATE TABLE Coordinators (
	coordinator_id INT PRIMARY KEY IDENTITY(70000, 1),
	name VARCHAR(100) NOT NULL
);

CREATE TABLE Students (
	student_id INT PRIMARY KEY IDENTITY(20000, 1),
	name VARCHAR(100) NOT NULL,
	school VARCHAR(100),
	coordinator_id INT FOREIGN KEY REFERENCES coordinators(coordinator_id)
);

CREATE TABLE Sponsors (
	sponsor_id INT PRIMARY KEY IDENTITY(30000, 1),
	name VARCHAR(100) NOT NULL
);

CREATE TABLE Proposers (
	proposer_id INT PRIMARY KEY IDENTITY(40000, 1),
	name VARCHAR(100) NOT NULL
);

CREATE TABLE Reservations (
	reservation_id INT PRIMARY KEY IDENTITY (50000, 1),
	location VARCHAR(100) NOT NULL,
	date DATE NOT NULL,
	CONSTRAINT uq_location_date UNIQUE(location, date)
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
	reservation_id INT FOREIGN KEY REFERENCES Reservations(reservation_id),
	organiser_id INT FOREIGN KEY REFERENCES Organisers(organiser_id) NOT NULL
);


CREATE TABLE Results (
	student_id INT FOREIGN KEY REFERENCES Students(student_id),
	contest_id INT FOREIGN KEY REFERENCES Contests(contest_id),
	score INT DEFAULT 10 + CHECKSUM(newid()) % (20 - 10 + 1),
	CONSTRAINT pk_student_contest PRIMARY KEY(student_id, contest_id)
);

CREATE TABLE Donations (
	sponsor_id INT FOREIGN KEY REFERENCES Sponsors(sponsor_id),
	contest_id INT FOREIGN KEY REFERENCES Contests(contest_id),
	amount INT CHECK (amount > 0),
	CONSTRAINT pk_sponsor_contest PRIMARY KEY(sponsor_id, contest_id)
);

CREATE TABLE Problems (
	proposer_id INT FOREIGN KEY REFERENCES Proposers(proposer_id),
	contest_id INT FOREIGN KEY REFERENCES Contests(contest_id),
	problem NVARCHAR(1000) NOT NULL,
	difficulty INT CHECK(difficulty > 0 AND difficulty <= 10)
	CONSTRAINT pk_proposer_contest PRIMARY KEY(proposer_id, contest_id)
);