IF NOT EXIST DONETS.IT6\DNO1\KOLYA.txt GOTO File1NotExist
IF NOT EXIST DONETS.IT6\DNO2\AYLOK.txt GOTO File2NotExist
IF -%1 NEQ - GOTO Defined
set /p flag="First name - 1, Second name - 2: "
IF %flag%==1 (SET name=KOLYA) ELSE (SET name=AYLOK)
GOTO Merge
:Defined
SET name=%1
:Merge
set EXT=doc
copy DONETS.IT6\DNO1\KOLYA.txt + DONETS.IT6\DNO2\AYLOK.txt DONETS.IT6\%name%.%EXT%
type DONETS.IT6\%name%.%EXT%
GOTO :EOF
:File1NotExist
ECHO File 1 not exist!
GOTO :EOF
:File2NotExist
ECHO File 2 not exist!