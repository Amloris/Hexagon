@echo off
pushd %~dp0\..\


:: Copy Premake files to submodules
call Scripts\Premake\Win-CpPremakeFiles.bat

IF "%~1"=="" GOTO endparse
IF "%~1"=="-vs2019" (
    echo Version Selected: vs2019 
    call vendor\bin\premake\premake5.exe vs2019
    GOTO end)
IF "%~1"=="-vs2022" (
    echo Version Selected: vs2022 
    call vendor\bin\premake\premake5.exe vs2022
    GOTO end)
IF "%~1"=="-?" (
    echo Available arguments:
    echo   -vs2019   Runs Premake for Visual Studio 2019
    echo   -vs2022   Runs Premake for Visual Studio 2022
    GOTO terminate)
echo "Unsupported argument: %~1" 
GOTO end


:endparse
:: Detect most recent VS version
echo Generating for latest available Visual Studio version
"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property catalog_productLineVersion > vsVersion.txt
set /p vsVersion=<vsVersion.txt
del vsVersion.txt
set vsVersionID=vs%vsVersion%
call vendor\bin\premake\premake5.exe %vsVersionID%

:end

popd
PAUSE

:terminate