@ECHO OFF
SETLOCAL
SET _OUT=mingw
IF NOT EXIST %_OUT%\. MKDIR %_OUT%
PUSHD %_OUT%
cmake -G"MinGW Makefiles" ..\..\ 
POPD 
ENDLOCAL