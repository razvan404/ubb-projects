#!/bin/awk

BEGIN {
    print "Nume Prenume Data nasterii Telefon Salariu"
}

{
    print $0
}

END {
    print "Numar total de angajati", NR
}
