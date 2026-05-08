sudo

mkdir -p build
cd build

cmake ..

cmake --build .

if [ $? -eq 0 ]; then
    echo ""
    echo "執行測試程式..."
    echo "--------------------"

    if [ -f "./test_app" ]; then
        ./test_app
    else
        echo "找不到執行檔 test_app"
    fi

    cd ..
else
    echo ""
    echo "編譯失敗，請檢查程式碼！"
    cd ..
    read -p "按 Enter 鍵繼續..."
fi