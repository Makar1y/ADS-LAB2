if %USERDOMAIN% == DESKTOPF goto :HomePC


@REM MIF pc
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :run


:HomePC
call make

:run
queens.exe - < tests/test1.txt > tests/result1.txt
queens.exe tests/test2.txt > tests/result2.html
queens.exe tests/test3.txt > tests/result3.html