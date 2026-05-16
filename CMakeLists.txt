# 此文件由 AI 生成後由程序員修改

cmake_minimum_required(VERSION 3.10)

# 1. 專案宣告與版本
project(CLS VERSION 1.0.0 LANGUAGES C)

# 強制使用 C99 標準
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 跨平台相容性設定
# 在 Windows 上自動匯出所有符號，否則 .dll 會沒有對應的 .lib 導致無法連結
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
# 在 Linux 上產生位置無關程式碼
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 自訂路徑
set(CLS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(CLS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(CLS_LIB_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../libraries/lib")
set(CLS_BIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/../libraries/bin")

# 搜尋 src 資料夾下的原始碼
file(GLOB_RECURSE CLS_SOURCES "${CLS_SOURCE_DIR}/*.c")

# 警告選項
if(MSVC)
    set(CLS_WARNING_OPTIONS /W4)
else()
    set(CLS_WARNING_OPTIONS -Wall -Wextra -Wpedantic)
endif()

# 1. 生成靜態函式庫 (Static Library)
add_library(cls_static STATIC ${CLS_SOURCES})
target_include_directories(cls_static PRIVATE "${CLS_INCLUDE_DIR}")
target_compile_options(cls_static PRIVATE ${CLS_WARNING_OPTIONS})
set_target_properties(cls_static PROPERTIES
    OUTPUT_NAME "cls"
    ARCHIVE_OUTPUT_DIRECTORY "${CLS_LIB_OUTPUT_DIR}"
)

# 2. 生成動態函式庫 (Shared Library)
add_library(cls_shared SHARED ${CLS_SOURCES})
target_include_directories(cls_shared PRIVATE "${CLS_INCLUDE_DIR}")
target_compile_options(cls_shared PRIVATE ${CLS_WARNING_OPTIONS})
set_target_properties(cls_shared PROPERTIES
    OUTPUT_NAME "cls"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    RUNTIME_OUTPUT_DIRECTORY "${CLS_BIN_OUTPUT_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CLS_LIB_OUTPUT_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CLS_LIB_OUTPUT_DIR}"
)

# 3. 測試程式
if(EXISTS "${CMAKE_SOURCE_DIR}/test/test.c")
    add_executable(test_app test/test.c)
    target_include_directories(test_app PRIVATE "${CLS_INCLUDE_DIR}")
    target_compile_options(test_app PRIVATE ${CLS_WARNING_OPTIONS})
    target_link_libraries(test_app PRIVATE cls_static)

    # 讓測試程式的輸出位址與 DLL 同層，方便 Windows 執行
    set_target_properties(test_app PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CLS_BIN_OUTPUT_DIR}"
    )
endif()