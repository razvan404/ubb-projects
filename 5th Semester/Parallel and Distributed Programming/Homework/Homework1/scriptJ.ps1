
$param1 = $args[0] # Nume fisier java
#Write-Host $param1

$param2 = $args[1] # No of threads
#Write-Host $param2

$param3 = $args[2] # No of runs
#Write-Host $param2

<#
$param4 = $args[3] # ?
Write-Host $param2
#>

# Executare class Java

$suma = 0

for ($i = 0; $i -lt $param3; $i++){
    Write-Host "Rulare" ($i+1)
    $a = java $args[0] $args[1] # rulare class java
    Write-Host $a[$a.length-1]
    $suma += $a[$a.length-1]
    Write-Host ""
}
$media = $suma / $i
#Write-Host $suma
Write-Host "Timp de executie mediu:" $media

# Creare fisier .csv
if (!(Test-Path outJ.csv)){
    New-Item outJ.csv -ItemType File
    #Scrie date in csv
    Set-Content outJ.csv 'Tip Matrice,Nr threads,Timp executie'
}

# Append
Add-Content outJ.csv ",$($args[1]),$($media)"