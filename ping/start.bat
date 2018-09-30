@echo off

for /L %%x in (1,1,254) do start "" /B ".\myping.bat" %%x

pause