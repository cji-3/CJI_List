@echo off
setlocal enabledelayedexpansion

:::::::::::::::::::: user set ::::::::::::::::::::::
::此檔案須放在專案根目錄
::此批次檔會編譯出靜態庫和動態庫以及測試程式，測試程式是連結lib中的靜態庫。

set srcPath=src
set includePath=include
set binPath=bin
set libPath=lib
set libAndBinFileName=CLS
set testPath=test
set gccParam=-Wall -std=c99 -O2
set externPath=

::外部庫文件結構需符合以下格式：
::extern
::├─lib0
::│  ├─include
::|  |  └─lib0.h
::│  └─lib
::|     └─liblib0.a
::└─lib1
::    ├─include
::    |  └─lib1.h
::    └─lib
::       └─liblib1.a
::::::::::::::::::::::::::::::::::::::::::::::::::::

if not exist "compilertmp" md compilertmp
if not exist "!libPath!" md "!libPath!"
if not exist "!binPath!" md "!binPath!"

set hfile=-I"!includePath!"
echo [搜尋到的include路徑] !includePath!

if exist "!externPath!" (
    for /D %%d in (!externPath!\*) do (
        if exist "%%d\include" (
            set hfile=!hfile! -I"%%d\include"
            echo [搜尋到的include路徑] %%d\include
        )
    )
)

set afile=
if exist "!externPath!" (
    for /D %%d in (!externPath!\*) do (
        for %%f in ("%%d\lib\*.a") do (
            set afile=!afile! "%%f"
            echo [搜尋到的.a文件] %%f
        )
    )
)

set cfile=
for %%f in (!srcPath!\*.c) do (
    set cfile=!cfile! "%%f"
    echo [編譯中] %%f
    gcc -c !gccParam! !hfile! "%%f" -o "compilertmp\%%~nf.o"
    if !errorlevel! neq 0 (
        echo [失敗] 編譯%%f的過程出錯，請檢查 GCC 輸出。
        rmdir /s /q compilertmp
        exit /b 1
    )
)

echo [正在打包靜態庫 .a]
ar rcs "!libPath!\lib!libAndBinFileName!.a" compilertmp\*.o

echo [正在編譯動態庫 .dll]
gcc -shared !gccParam! !hfile! -o "!binPath!\!libAndBinFileName!.dll" compilertmp\*.o !afile! -Wl,--out-implib,"!libPath!\lib!libAndBinFileName!.dll.a"

rmdir /s /q compilertmp

echo.
if !errorlevel! equ 0 (
    echo [成功] 建置完成！
    echo  - 靜態庫: !libPath!\lib!libAndBinFileName!.a
    echo  - 動態庫: !binPath!\!libAndBinFileName!.dll
    echo  - 匯入庫: !binPath!\lib!libAndBinFileName!.dll.a

    echo.
    echo [正在編譯測試程式]
    gcc !testPath!\*.c -o "!testPath!\test.exe" !gccParam! !hfile! -L"!libPath!" -l!libAndBinFileName! !afile!
    if !errorlevel! equ 0 (
        echo [成功] 測試程式編譯完成！
        echo  - 測試程式: !testPath!\test.exe
    ) else (
        echo [失敗] 測試程式編譯過程出錯，請檢查 GCC 輸出。
    )
) else (
    echo [失敗] 建置過程出錯，請檢查 GCC 輸出。
)

echo %CMDCMDLINE% | find /i "/c" >nul
if !errorlevel! equ 0 (
    echo.
    echo [提示] 偵測到雙擊執行，按任意鍵結束...
    pause >nul
)