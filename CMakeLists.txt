cmake_minimum_required(VERSION 3.6)
project(QCodeEditor)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXAMPLE "Example building required" Off)

if (${BUILD_EXAMPLE})
    message(STATUS "QCodeEditor example will be built.")
    add_subdirectory(example)
endif()

if(Qt5Core_VERSION_STRING)
  qt5_add_resources(QRCS "${CMAKE_CURRENT_SOURCE_DIR}/resources/qcodeeditor_resources.qrc")
else()
  qt_add_resources(QRCS "${CMAKE_CURRENT_SOURCE_DIR}/resources/qcodeeditor_resources.qrc")
endif()

set(INCLUDE_FILES
    include/QHighlightRule
    include/QHighlightBlockRule
    include/QCodeEditor
    include/QCXXHighlighter
    include/QLineNumberArea
    include/QStyleSyntaxHighlighter
    include/QSyntaxStyle
    include/QGLSLCompleter
    include/QGLSLHighlighter
    include/QJavaHighlighter
    include/QJSHighlighter
    include/QLanguage
    include/QXMLHighlighter
    include/QJSONHighlighter
    include/QLuaCompleter
    include/QLuaHighlighter
    include/QPythonHighlighter
    include/QFaustCompleter
    include/QFaustHighlighter
    include/internal/QHighlightRule.hpp
    include/internal/QHighlightBlockRule.hpp
    include/internal/QCodeEditor.hpp
    include/internal/QCXXHighlighter.hpp
    include/internal/QJavaHighlighter.hpp
    include/internal/QJSHighlighter.hpp
    include/internal/QLineNumberArea.hpp
    include/internal/QStyleSyntaxHighlighter.hpp
    include/internal/QSyntaxStyle.hpp
    include/internal/QGLSLCompleter.hpp
    include/internal/QGLSLHighlighter.hpp
    include/internal/QLanguage.hpp
    include/internal/QXMLHighlighter.hpp
    include/internal/QJSONHighlighter.hpp
    include/internal/QLuaCompleter.hpp
    include/internal/QLuaHighlighter.hpp
    include/internal/QPythonCompleter.hpp
    include/internal/QPythonHighlighter.hpp
    include/internal/QFaustCompleter.hpp
    include/internal/QFaustHighlighter.hpp
)

set(SOURCE_FILES
    src/internal/QCodeEditor.cpp
    src/internal/QLineNumberArea.cpp
    src/internal/QCXXHighlighter.cpp
    src/internal/QSyntaxStyle.cpp
    src/internal/QStyleSyntaxHighlighter.cpp
    src/internal/QGLSLCompleter.cpp
    src/internal/QGLSLHighlighter.cpp
    src/internal/QJavaHighlighter.cpp
    src/internal/QJSHighlighter.cpp
    src/internal/QLanguage.cpp
    src/internal/QXMLHighlighter.cpp
    src/internal/QJSONHighlighter.cpp
    src/internal/QLuaCompleter.cpp
    src/internal/QLuaHighlighter.cpp
    src/internal/QPythonCompleter.cpp
    src/internal/QPythonHighlighter.cpp
    src/internal/QFaustCompleter.cpp
    src/internal/QFaustHighlighter.cpp
)

# Create code for QObjects
set(CMAKE_AUTOMOC OFF)

# Create code from resource files
set(CMAKE_AUTORCC ON)

# Generate compile_commands.json in build/ for analyzers like clang-tidy.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find includes in corresponding build directories
if(NOT QT_VERSION)
  set(QT_VERSION Qt5)
endif()
find_package(${QT_VERSION} REQUIRED COMPONENTS Core Gui Widgets)

add_library(QCodeEditor STATIC
    ${QRCS}
    ${SOURCE_FILES}
    ${INCLUDE_FILES}
)

target_include_directories(QCodeEditor PUBLIC
    include
    "${OSSIA_3RDPARTY_FOLDER}/verdigris/src"
)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(QCodeEditor
        PRIVATE
        -pedantic
        -Wall
        -Wextra
        -Woverloaded-virtual
        -Winit-self
        -Wunreachable-code
    )
endif(CMAKE_COMPILER_IS_GNUCXX)

target_link_libraries(QCodeEditor
    ${QT_PREFIX}::Core
    ${QT_PREFIX}::Widgets
    ${QT_PREFIX}::Gui
)
