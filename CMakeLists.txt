cmake_minimum_required(VERSION 3.1)
project(TowerDefense)

set(TowerDefense_VERSION_MAJOR 0)
set(TowerDefense_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(warnings "-Wall -Wextra -Werror")

set(SOURCE_FILES
    src/gameobjects/BaseObject.cpp
    src/gameobjects/BaseObject.h
    src/gameobjects/BasicEnemy.cpp
    src/gameobjects/BasicEnemy.h
    src/gameobjects/MovingObject.cpp
    src/gameobjects/MovingObject.h
    src/gameobjects/ObjectManager.cpp
    src/gameobjects/ObjectManager.h
    src/gameobjects/Shot.cpp
    src/gameobjects/Shot.h
    src/gameobjects/Team.h
    src/gameobjects/Tower.cpp
    src/gameobjects/Tower.h
    src/gameobjects/Type.h
    src/gui/components/Button.cpp
    src/gui/components/Button.h
    src/gui/components/GuiObject.h
    src/gui/GraphicsManager.cpp
    src/gui/GraphicsManager.h
    src/gui/RenderingThread.cpp
    src/gui/RenderingThread.h
    src/gui/UserInterface.cpp
    src/gui/UserInterface.h
    src/path/Path.cpp
    src/path/Path.h
    src/util/dlb.cpp
    src/util/dlb.h
    src/util/DlbException.cpp
    src/util/DlbException.h
    src/util/Log.cpp
    src/util/Log.h
    src/util/Logger.cpp
    src/util/Logger.h
    src/Game.cpp
    src/Game.h
    src/LevelLoader.cpp
    src/LevelLoader.h
    src/main.cpp)

set(EXECUTABLE_NAME "TowerDefense")
add_executable(TowerDefense ${SOURCE_FILES})

set(SFML_ROOT "E:/Programming/TowerDefense/SFML")
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

if (WIN32)
    add_custom_command(TARGET TowerDefense POST_BUILD COMMAND debug WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

set_target_properties(TowerDefense PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION /bin)