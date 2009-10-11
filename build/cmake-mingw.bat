@ECHO OFF
SETLOCAL
SET _OUT=mingw
IF NOT EXIST %_OUT%\. MKDIR %_OUT%
PUSHD %_OUT%

SET _CONFIG=Debug
ECHO Generating %_CONFIG% configuration
IF NOT EXIST %_CONFIG%\. MKDIR %_CONFIG%
PUSHD %_CONFIG%
cmake -G"MinGW Makefiles" ..\..\..\ -DCMAKE_BUILD_TYPE=%_CONFIG%
POPD

SET _CONFIG=Release 
ECHO Generating %_CONFIG% configuration
IF NOT EXIST %_CONFIG%\. MKDIR %_CONFIG%
PUSHD %_CONFIG%
cmake -G"MinGW Makefiles" ..\..\..\ -DCMAKE_BUILD_TYPE=%_CONFIG%
POPD


POPD 
ENDLOCAL
