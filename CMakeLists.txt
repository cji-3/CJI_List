cmake_minimum_required(VERSION 3.10)

# 專案名稱
project(CJI_List C)

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
add_library(cji_list_static STATIC ${SOURCES})
# 設定輸出的檔案名稱為 cji_list (避免檔名變成 cji_list_static)
set_target_properties(cji_list_static PROPERTIES OUTPUT_NAME "cji_list")
# 設定輸出目錄
set_target_properties(cji_list_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/static")

# -------------------------------------------------------------------
# 2. 生成動態函式庫 (Shared Library)
# -------------------------------------------------------------------
add_library(cji_list_shared SHARED ${SOURCES})
# 設定輸出的檔案名稱為 cji_list
set_target_properties(cji_list_shared PROPERTIES OUTPUT_NAME "cji_list")
# 設定輸出目錄 (Windows 下 .dll 是 RUNTIME, .lib 導入庫是 LIBRARY/ARCHIVE)
set_target_properties(cji_list_shared PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/shared"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/shared"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib/shared"
)

# -------------------------------------------------------------------
# 3. 測試程式 (連結靜態庫做測試)
# -------------------------------------------------------------------
if(EXISTS "${CMAKE_SOURCE_DIR}/test/test.c")
    add_executable(test_app test/test.c)
    target_link_libraries(test_app cji_list_static)
endif()