# ------------------------------ Macros/Functions ------------------------------
include(${PROJECT_SCRIPTS_DIR}/Basic.cmake)
include(${PROJECT_SCRIPTS_DIR}/FindQt.cmake)
include(${PROJECT_SCRIPTS_DIR}/ListUtil.cmake)
include(${PROJECT_SCRIPTS_DIR}/Translate.cmake)

# Use to conveniently add files in this CMakeLists
macro(add_current_files List)
    list_append_with_prefix(${List} ${CMAKE_CURRENT_SOURCE_DIR}/ ${ARGN})
endmacro()

# ------------------------------ Basic information ------------------------------

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Variables
set(QT_LIBS)
set(QT_RESOURCES)
set(RC_FILES)
set(MAC_RES)

set(PROJECT_SOURCES)
set(PROJECT_HEADERS)
set(INCLUDE_PATHS)

# ------------------------------ Include/Import/Link ------------------------------
add_qt_module(QT_LIBS Widgets)
include_qt_private(Widgets)

# Add fixed files
list_add_recursively(PROJECT_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cc")
list_add_recursively(PROJECT_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.h")
#list_add_recursively(PROJECT_SOURCES
#        "${CMAKE_CURRENT_SOURCE_DIR}/Meta/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Meta/*.cc")
#list_add_recursively(PROJECT_HEADERS
#        "${CMAKE_CURRENT_SOURCE_DIR}/Meta/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/Meta/*.h")
#list_add_recursively(PROJECT_SOURCES
#        "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/*.cc")
#list_add_recursively(PROJECT_HEADERS
#        "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/Vendor/*.h")
#list_add_recursively(PROJECT_SOURCES
#        "${CMAKE_CURRENT_SOURCE_DIR}/Staging/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Staging/*.cc")
#list_add_recursively(PROJECT_HEADERS
#        "${CMAKE_CURRENT_SOURCE_DIR}/Staging/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/Staging/*.h")

# Add specific files
add_current_files(PROJECT_SOURCES
        main.cpp
        settings.cpp
        settings.h
        )

add_current_files(PROJECT_HEADERS
        )

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${QT_RESOURCES} ${RC_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_VERSION 1.0.0.0
        MACOSX_BUNDLE_SHORT_VERSION_STRING 1.0
        )

target_link_libraries(${PROJECT_NAME} PRIVATE FramelessHelper::Widgets)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${QT_LIBS})

# Write location to logs
add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND}
        -D filename=${PROJECT_ARCHIVE_DIR}/main_target_lst_file
        -D content=$<TARGET_FILE:${PROJECT_NAME}>
        -P ${PROJECT_SCRIPTS_DIR}/Execute/Log.cmake
        )

# ------------------------------ Promote code experience ------------------------------

# Include directories
add_current_files(INCLUDE_PATHS
        ui
        )

foreach(Path ${INCLUDE_PATHS})
    include_directories(${Path})
endforeach()