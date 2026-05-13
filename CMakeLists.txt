#此文件由AI生成後由程序員修改

cmake_minimum_required(VERSION 3.10)

# 1. 專案宣告與版本
project(CLS VERSION 1.0.0 LANGUAGES C)

# 強制使用 C99 標準
set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 2. 跨平台相容性設定
# 在 Windows 上自動匯出所有符號，否則 .dll 會沒有對應的 .lib 導致無法連結
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# 在 Linux 上產生位置無關程式碼
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 標頭檔路徑
include_directories(include)

# 搜尋 src 資料夾下的原始碼
file(GLOB_RECURSE SOURCES "src/*.c")

# -------------------------------------------------------------------
# 1. 生成靜態函式庫 (Static Library)
# -------------------------------------------------------------------
add_library(cls_static STATIC ${SOURCES})
set_target_properties(cls_static PROPERTIES
    OUTPUT_NAME "cls"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# -------------------------------------------------------------------
# 2. 生成動態函式庫 (Shared Library)
# -------------------------------------------------------------------
add_library(cls_shared SHARED ${SOURCES})
set_target_properties(cls_shared PROPERTIES
    OUTPUT_NAME "cls"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    # 這裡使用通用的輸出設定
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" # Windows 的 .dll 會放這
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" # Linux 的 .so 會放這
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" # Windows 的 .lib 會放這
)

# -------------------------------------------------------------------
# 3. 測試程式
# -------------------------------------------------------------------
if(EXISTS "${CMAKE_SOURCE_DIR}/test/test.c")
    add_executable(test_app test/test.c)
    target_link_libraries(test_app cls_static)

    # 讓測試程式的輸出位址與 DLL 同層，方便 Windows 執行
    set_target_properties(test_app PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()