@ECHO OFF
SETLOCAL
SET _OUT=vc9
IF NOT EXIST %_OUT%\. MKDIR %_OUT%
PUSHD %_OUT%
cmake -G"Visual Studio 9 2008" ..\..\ 
POPD 
ENDLOCAL