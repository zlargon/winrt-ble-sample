@echo off
setlocal
cd %~dp0
set ROOT_DIR=%CD%

:: MSVC env
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

:: create build folder
rmdir /s /q build
mkdir build
cd build

:: cmake build
call cmake .. -Ax64 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0
call cmake --build . --config Release

:: test
echo ===============================================================================
cd Release
set PATH=%PATH%;%ROOT_DIR%\bin
call win_ble.exe
echo  ===============================================================================
