set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(PROJECT_SOURCES
        utils/Document.cpp
        utils/Document.h
        main.cpp
        settings.h
        settings.cpp
        window/MainWindow.h
        window/MainWindow.cpp
        utils/mdtransform.hpp)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets #[[WebChannel WebEngineWidgets]])
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets #[[WebChannel WebEngineWidgets]])
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets #[[Qt6::WebEngineWidgets Qt6::WebChannel]])
target_link_libraries(${PROJECT_NAME} PRIVATE FramelessHelper::Widgets qmarkdowntextedit)

set(markdowneditor_resource_files
        "res/3rdparty/markdown.css"
        "res/3rdparty/marked.js"
        "res/3rdparty/markdown-it.min.js"
        "res/3rdparty/default.min.css"
        "res/3rdparty/highlight.min.js"
#        "res/default.md"
        "res/index.html"
        )

qt_add_resources(${PROJECT_NAME} "markdowneditor"
        PREFIX
        "/"
        BASE
        "res"
        FILES
        ${markdowneditor_resource_files}
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )