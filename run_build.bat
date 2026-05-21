@echo off
chcp 65001 >nul

if not exist build mkdir build
pushd build
cmake -G "MinGW Makefiles" ..
cmake --build .

if errorlevel 1 (
    echo.
    echo 編譯失敗，請檢查程式碼！
    popd
    pause
    exit /b 1
)

popd

echo.
echo 執行測試程式(靜態庫)...
echo.--------------------
"bin\cls_test_static.exe"

echo.
echo 執行測試程式(動態庫)...
echo.--------------------
"lib\cls_test_shared.exe"