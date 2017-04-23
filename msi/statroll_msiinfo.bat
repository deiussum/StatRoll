@echo off
PATH=%PATH%;"C:\Program Files\Microsoft SDK\Bin"

Msiinfo.exe statroll.msi -T "Installation Database" -J Subject -A "Lycanth Softwere" -K "Installer, MSI, Database" -O "This installer database contains the logic and data required to install GreyWolf's Stat Roller." -P ;1033 -V {507FD332-2340-4233-A651-BDECAB1D65CE} -G 100 -W 2 -N Orca -U 0
pause