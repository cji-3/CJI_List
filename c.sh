#!/bin/bash

#################### user set ######################
# 此檔案須放在專案根目錄

srcPath="src"
includePath="include"
binPath="bin"
libPath="lib"
libAndBinFileName="CLS"
testPath="test"
gccParam="-Wall -std=c99 -O0"
externPath=

# 外部庫文件結構需符合以下格式：
# extern
# ├─lib0
# │  ├─include
# │  │  └─lib0.h
# │  └─lib
# │     └─liblib0.a
# └─lib1
#    ├─include
#    │  └─lib1.h
#    └─lib
#       └─liblib1.a
####################################################

# 建立輸出與暫存目錄
mkdir -p compilertmp "$libPath" "$binPath"

# 1. 搜尋 Include 路徑 (-I)
hfile="-I${includePath}"
echo "[搜尋到的include路徑] ${includePath}"

if [ -d "$externPath" ]; then
    for d in "$externPath"/*; do
        if [ -d "$d/include" ]; then
            hfile="${hfile} -I${d}/include"
            echo "[搜尋到的include路徑] ${d}/include"
        fi
    done
fi

# 2. 搜尋外部 .a 靜態庫
afile=""
if [ -d "$externPath" ]; then
    for d in "$externPath"/*; do
        if [ -d "$d/lib" ]; then
            for f in "$d"/lib/*.a; do
                if [ -f "$f" ]; then
                    afile="${afile} $f"
                    echo "[搜尋到的.a文件] $f"
                fi
            done
        fi
    done
fi

# 3. 編譯 src 下的 .c 檔案為 .o
for f in "$srcPath"/*.c; do
    if [ -f "$f" ]; then
        filename=$(basename "$f" .c)
        echo "[編譯中] $f"

        # 執行編譯
        gcc -c $gccParam $hfile "$f" -o "compilertmp/${filename}.o"

        if [ $? -ne 0 ]; then
            echo "[失敗] 編譯 $f 過程出錯，請檢查 GCC 輸出。"
            rm -rf compilertmp
            exit 1
        fi
    fi
done

# 4. 打包靜態庫 (.a) 與動態庫 (.so / .dll)
echo "[正在打包靜態庫 .a]"
ar rcs "${libPath}/lib${libAndBinFileName}.a" compilertmp/*.o

echo "[正在編譯動態庫]"
# 判斷作業系統（Windows/MinGW 產出 .dll，Linux 產出 .so）
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
    dllOut="${binPath}/${libAndBinFileName}.dll"
    implibOut="${libPath}/lib${libAndBinFileName}.dll.a"
    gcc -shared $gccParam $hfile -o "$dllOut" compilertmp/*.o $afile -Wl,--out-implib,"$implibOut"
else
    # Linux 環境下生成 .so (加 -fPIC 參數)
    soOut="${binPath}/lib${libAndBinFileName}.so"
    gcc -shared $gccParam $hfile -fPIC -o "$soOut" compilertmp/*.o $afile
fi

# 清理暫存檔
rm -rf compilertmp

echo ""
echo "[成功] 建置完成！"
echo "  - 靜態庫: ${libPath}/lib${libAndBinFileName}.a"

echo ""
echo "[正在編譯測試程式]"
gcc $testPath/*.c -o "${testPath}/test" $gccParam $hfile -L"${libPath}" -l${libAndBinFileName} $afile

if [ $? -eq 0 ]; then
    echo "[成功] 測試程式編譯完成！"
    echo "  - 測試程式: ${testPath}/test.exe"
else
    echo "[失敗] 測試程式編譯過程出錯，請檢查 GCC 輸出。"
    exit 1
fi