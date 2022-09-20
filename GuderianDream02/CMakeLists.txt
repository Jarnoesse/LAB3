cmake_minimum_required(VERSION 3.5)

project(GuderianDream02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GuderianDream02 main.cpp GameManager.cpp Bf109.cpp GermanFactory.cpp GermanInfantry.cpp PanzerIV.cpp RussianFactory.cpp RussianInfantry.cpp T34.cpp Turn.cpp Turn2.cpp Territory.cpp Yak3.cpp)
