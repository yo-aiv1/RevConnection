@echo off
setlocal

set "CC=gcc"
set "CCX64=x86_64-w64-mingw32-g++"
set "INCLUDE_DIR=-Iinclude"
set "CFLAGS=-Os -fno-asynchronous-unwind-tables -nostdlib -fno-ident -fpack-struct=8 -falign-functions=1 -s -ffunction-sections -falign-jumps=1 -w -falign-labels=1 -fPIC -masm=intel -fpermissive -mrdrnd -Wl,-s,--no-seh,--enable-stdcall-fixup"
set "SRC=src\main.c src\loaders.c src\utils.c"
set "OBJ=main.o loaders.o utils.o"
set "TARGET=bin\main.exe"

if "%~2"=="" (
    echo port and ip are required
    exit /b 1
)


<nul set /p =PARSING... 
%CC% utils\tobytes.c -o utils\convert.exe -lws2_32
python utils\edit.py %1 %2
if %errorlevel% neq 0 (
    del /q utils\convert.exe
    exit /b 1
)
echo DONE


<nul set /p =COMPILING... 
for %%i in (%SRC%) do (
    %CCX64% %CFLAGS% %INCLUDE_DIR% -c %%i -o %%~ni.o
)
%CCX64% %OBJ% %CFLAGS% -o %TARGET%
echo DONE


<nul set /p =CLEANING... 
del /q utils\convert.exe
del /q %OBJ%
python utils\edit.py back
echo DONE

echo.
echo THE EXECUTABLE IS LOCATED AT: %TARGET%

