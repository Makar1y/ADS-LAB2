if %USERDOMAIN% == DESKTOPF goto :HomePC


@REM MIF pc
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :run


:HomePC
make