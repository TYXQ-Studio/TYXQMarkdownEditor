# ------------------------------ Basic information ------------------------------

cmake_minimum_required(VERSION 3.5)

project(TYXQMarkdownEditorClient
        VERSION 0.1
        LANGUAGES CXX
        )

# CPP Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set Directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

if(NOT DEFINED PROJECT_SCRIPTS_DIR)
    set(PROJECT_SCRIPTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scripts/cmake) # Scripts
endif()

if(NOT DEFINED PROJECT_ARCHIVE_DIR)
    set(PROJECT_ARCHIVE_DIR ${PROJECT_BINARY_DIR}/etc) # Etc
endif()

if(NOT DEFINED PROJECT_DEPLOY_PATH)
    set(PROJECT_DEPLOY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/release) # Release
endif()
# ------------------------------ Sub Projects ------------------------------

# Libraries
add_subdirectory(FramelessHelper)

# Application
add_subdirectory(TYXQMarkdownEditorClient)

# ------------------------------ Deploy Targets ------------------------------

string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCH_NAME)
set(RELEASE_DIR_NAME tyxqmarkdowneditorclient-win-${ARCH_NAME}-${PROJECT_VERSION})

add_custom_target(app_deploy
        COMMAND ${CMAKE_COMMAND}
        -D ETC_DIR="${PROJECT_ARCHIVE_DIR}"
        -D RELEASE_DIR="${PROJECT_DEPLOY_PATH}/${RELEASE_DIR_NAME}"
        -P "${PROJECT_SCRIPTS_DIR}/Deploy/WinDeploy.cmake"
        DEPENDS lrelease_task base_lrelease_task QVogenClient RenderHost
        )
