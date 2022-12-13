cmake_minimum_required(VERSION 3.5)

project(game-inventory LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Sql Multimedia)

set(PROJECT_SOURCES
    src/mainwindow.h
    src/inventoryslot.h
    src/database.h
    src/item.h
    src/itemgenerator.h
    src/gamemenu.h
    src/playingfield.h
    src/inventory.h

    src/mainwindow.cpp
    src/inventoryslot.cpp
    src/database.cpp
    src/item.cpp
    src/itemgenerator.cpp
    src/gamemenu.cpp
    src/playingfield.cpp
    src/inventory.cpp
    src/main.cpp

    src/mainwindow.ui

    src/resources.qrc
)

add_executable(game-inventory
    ${PROJECT_SOURCES}
)

target_include_directories(game-inventory PRIVATE
    src
)

target_link_libraries(game-inventory PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::Multimedia
)

set_target_properties(game-inventory PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
