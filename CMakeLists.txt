#此文件由AI生成後由程序員修改

# CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 專案名稱
project(CLS C)
project(CLS VERSION 1.0.0)

# 強制使用 C99 標準
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 標頭檔路徑
include_directories(include)

# 搜尋 src 資料夾下的原始碼
file(GLOB_RECURSE SOURCES "src/*.c")

# -------------------------------------------------------------------
# 1. 生成靜態函式庫 (Static Library)
# -------------------------------------------------------------------
add_library(cls_static STATIC ${SOURCES})
# 設定輸出的檔案名稱為 cls (編譯後會產生 libcls.a 或 cls.lib)
set_target_properties(cls_static PROPERTIES OUTPUT_NAME "cls")
# 設定輸出目錄
set_target_properties(cls_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/static")

# -------------------------------------------------------------------
# 2. 生成動態函式庫 (Shared Library)
# -------------------------------------------------------------------
add_library(cls_shared SHARED ${SOURCES})
set_target_properties(cls_shared PROPERTIES
    OUTPUT_NAME "cls"
    VERSION ${PROJECT_VERSION}
    SOVERSION 1 # 主要版本號，當有重大更新時增加
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/shared"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/shared"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/shared"
)

# -------------------------------------------------------------------
# 3. 測試程式 (連結靜態庫做測試)
# -------------------------------------------------------------------
if(EXISTS "${CMAKE_SOURCE_DIR}/test/test.c")
    add_executable(test_app test/test.c)
    # 確保連結到新的靜態庫目標名稱
    target_link_libraries(test_app cls_static)
endif()