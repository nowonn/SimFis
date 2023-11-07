@echo off
setlocal enabledelayedexpansion
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

if not exist ..\build mkdir ..\build
pushd ..\build
del *.pbd > NUL 2> NUL
echo WAITING FOR PBD > lock.tmp

cl -nologo -Zi -FC ..\code\win32_plat.c /link user32.lib gdi32.lib -incremental:no -opt:ref /OUT:SimFis.exe

del lock.tmp > NUL 2> NUL
del *.obj > NUL 2> NUL

popd
endlocal enabledelayedexpansion
