@echo off

chcp 65001 >nul

mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

if %errorlevel% equ 0 (
    echo.
    echo 執行測試程式...
    echo.--------------------
    test_app.exe
    cd ..
) else (
    echo.
    echo 編譯失敗，請檢查程式碼！
    cd ..
    pause
)