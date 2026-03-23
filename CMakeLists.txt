# SPDX-License-Identifier: GPL-3.0-only
# CMake build system lists file for UltradiumTimer
cmake_minimum_required(VERSION 3.16)
project(UltradiumTimer)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Multimedia Qml Quick widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(${PROJECT_NAME}
    main.cpp
    TimerManager.cpp
    TimerManager.h
    QuotesManager.cpp
    QuotesManager.h
    quotes.csv
    qml.qrc
    quotes_generic.csv
    sound_resources.qrc
    ColorPicker.h
    ColorPicker.cpp
    EyeTimer.h
    EyeTimer.cpp
    SFXPlayer.h
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Multimedia
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
)

