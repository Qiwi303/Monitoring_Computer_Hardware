cmake_minimum_required(VERSION 3.14)

project(ftxui-starter
  LANGUAGES CXX
  VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v5.0.0 
)

FetchContent_MakeAvailable(ftxui)

add_executable(ftxui-starter runMonitoring.cpp parser.cpp cpu.cpp ram.cpp)

add_executable(producer producer.cpp parser.cpp cpu.cpp ram.cpp dataCollector.cpp)


target_include_directories(ftxui-starter PRIVATE src)

target_link_libraries(ftxui-starter
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)
