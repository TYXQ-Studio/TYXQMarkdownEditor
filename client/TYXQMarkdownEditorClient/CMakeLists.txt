# ------------------------------ Basic information ------------------------------

cmake_minimum_required(VERSION 3.20)

project(TYXQMarkdownEditorClient VERSION 0.1 LANGUAGES CXX)

# CPP Version
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(FramelessHelper)
add_subdirectory(qmarkdowntextedit)
add_subdirectory(TYXQMarkdownEditorClient)

# Set Directories
#set(INSTALL_EXAMPLEDIR "example")

#install(TARGETS ${PROJECT_NAME}
#        RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
#        BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
#        LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
#        )