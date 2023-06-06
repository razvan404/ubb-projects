USE S11;
GO

IF EXISTS(SELECT name FROM sys.indexes WHERE name ='N_idx_tablou_pictor')
	DROP INDEX N_idx_tablou_pictor ON Tablouri;
CREATE NONCLUSTERED INDEX N_idx_tablou_pictor ON Tablouri(Pid);

SELECT T.Pid, COUNT(T.Tid) [Numar de aparitii]
FROM Tablouri T
INNER JOIN Pictori P ON T.Pid = P.pid
GROUP BY T.Pid;
