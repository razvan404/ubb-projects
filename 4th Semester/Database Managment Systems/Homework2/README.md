# Problema 2

Transformaţi primul laborator astfel încât să permiteţi crearea unei ferestre (forme) master-detail generice. Titlul şi structura ferestrei (formei), controalele şi procedurile stocate/ interogările utilizate pentru  a accesa şi manipula detele vor fi stabilite într-un fişier de configurare.

Fereastra (forma) va fi suficient de generică astfel încât modificările ce vor trebui făcute pentru gestionarea altor date (ce în continuare trebuie să se afle într-o relaţie 1-n) să se realizeze exclusiv la nivelul fişierului de configurare şi nu în codul sursă. 

Pentru prezentarea laboratorului va trebui sa pregătiţi cel puţin două scenarii distincte ce să presupună accesare şi manipularea datelor din 2 tabele aflate într-o relaţie 1-n. Modul de definire şi de interpretare a conţinutului fişierului de configurare este la latitudinea fiecăruia dintre voi.

Este necesară utilizarea entităţilor din ADO.NET  (data  sets,  data  adapters,  data readers etc.; nu se acceptă soluţii folosindLINQ sauEntity Framework sauorice alt ORM).

Link-uri utile:

- ADO.NET: lucru cu data sets, data adapters, data tables, data binding:
    - seminarii - http://www.youtube.com/playlist?list=PL364D9F01461F5F87
    - http://www.codeproject.com/Articles/24656/A-Detailed-Data-Binding-Tutorial
    - http://www.codeproject.com/Articles/8477/Using-ADO-NET-for-beginners
    - http://csharp-station.com/Tutorial/AdoDotNet/Lesson01
- lucrul cu fişiereXML:
    - http://www.w3schools.com/schema/default.asp
    - http://www.drdobbs.com/windows/parsing-xml-files-in-net-using-c/184416669
    - http://support.microsoft.com/kb/311566
    - http://support.microsoft.com/kb/307548
- lucrul cu fişiere de configurare:
    - http://support.microsoft.com/kb/815786
    - http://msdn.microsoft.com/en-us/library/system.configuration.configuration.aspx
    - http://www.codeproject.com/Articles/6538/Configuration-Settings-File-for-providing-applicat