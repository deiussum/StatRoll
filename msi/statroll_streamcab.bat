@echo off
PATH=%PATH%;"C:\Program Files\Microsoft SDK\Bin"

msidb -d statroll.msi -k StatRoll.cab
msidb -d statroll.msi -a StatRoll.cab
pause