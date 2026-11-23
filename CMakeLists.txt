cmake_minimum_required(VERSION 3.21)
project(CorelCraft VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Widgets Svg SvgWidgets)
qt_add_executable(CorelCraft
 src/main.cpp src/core/Document.cpp src/core/Document.h
 src/ui/MainWindow.cpp src/ui/MainWindow.h src/ui/CanvasView.cpp src/ui/CanvasView.h
 src/io/SvgIO.cpp src/io/SvgIO.h src/io/PdfIO.cpp src/io/PdfIO.h src/io/CdrIO.cpp src/io/CdrIO.h)
target_include_directories(CorelCraft PRIVATE src)
target_link_libraries(CorelCraft PRIVATE Qt6::Widgets Qt6::Svg Qt6::SvgWidgets)
