@echo off
:имя файла для записи информации
set fname=PModel.txt
:имя компьютера
SETLOCAL ENABLEDELAYEDEXPANSION
for /f "skip=1 delims=" %%i in ('wmic cpu get name') do (
for /f "tokens=1-2 delims=" %%A in ("%%i") do (
set CPULbl=%%A
echo !CPULbl! >>%fname%
))