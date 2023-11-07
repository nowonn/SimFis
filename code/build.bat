@echo off
setlocal enabledelayedexpansion
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsx86_amd64.bat"

set "audioDirectory=audio"
set "audioFile=audio_files"

for %%F in ("%audioDirectory%\*.mp3") do (
    set "filename=%%~nF"
    echo INCLUDE_AUDIO(!filename!, mp3^^^) >> "%audioFile%.h"
    echo !filename!_mp3 RCDATA "%audioDirectory%\!filename!.mp3" >> "%audioFile%.rc"
)

if not exist ..\build mkdir ..\build
pushd ..\build
del *.pbd > NUL 2> NUL
echo WAITING FOR PBD > lock.tmp

rc /fo audio_files.res ..\code\%audioFile%.rc
cl -nologo -Zi -FC ..\code\win32_plat.c audio_files.res /link user32.lib gdi32.lib -incremental:no -opt:ref /OUT:SimFis.exe

del "%audioFile%.res" > NUL 2> NUL
del lock.tmp > NUL 2> NUL
del *.obj > NUL 2> NUL

popd
del "%audioFile%.h" > NUL 2> NUL
del "%audioFile%.rc" > NUL 2> NUL
endlocal enabledelayedexpansion
