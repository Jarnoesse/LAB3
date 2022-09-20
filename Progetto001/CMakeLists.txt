cmake_minimum_required(VERSION 3.5)

project(Progetto001 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Progetto001 main.cpp GameManager.cpp Territory.cpp Turn.cpp GermanFactory.cpp RussianFactory.cpp PanzerIV.cpp T34.cpp Yak3.cpp Bf109.cpp GermanInfantry.cpp RussianInfantry.cpp)
