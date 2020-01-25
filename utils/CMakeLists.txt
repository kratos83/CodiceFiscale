CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
cmake_policy(SET CMP0043 OLD)

project(utils)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h" "qmldir")
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")

include_directories(${Qt5Core_PRIVATE_INCLUDE_DIRS}
                    ${Qt5Quick_PRIVATE_INCLUDE_DIRS}
                    ${Qt5Qml_PRIVATE_INCLUDE_DIRS}
                    ${Qt5Templates2_PRIVATE_INCLUDE_DIRS})
                    
find_package(Qt5Core  REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Qml   REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)

set(utils_includes
${CMAKE_BINARY_DIR}
)

include_directories(${utils_includes})


qt5_wrap_cpp(MOC_SOURCES ${HEADERS})


IF(WIN32)
    LINK_LIBRARIES(-lws2_32 -lwtsapi32 -lnetapi32 -luserenv -ladvapi32 )
    SET(CMAKE_MODULE_LINKER_FLAGS -Wl,-export-all-symbols)
endif(WIN32)

IF(WIN64)
ADD_DEFINITIONS(-D_X64)
ENDIF(WIN64)

LINK_LIBRARIES(-lpthread)


if(WIN32)
ADD_LIBRARY( utils SHARED ${SOURCES} ${MOC_SOURCES})
set_target_properties(utils PROPERTIES OUTPUT_NAME "utils" PREFIX "")
file(WRITE qmldir "module Codelinsoft.Utils\n plugin utils")
else()
ADD_LIBRARY( utils SHARED ${SOURCES} ${MOC_SOURCES})
file(WRITE qmldir "module Codelinsoft.Utils\n plugin utils")
endif(WIN32)

target_include_directories(utils SYSTEM PRIVATE ${Qt5Quick_PRIVATE_INCLUDE_DIRS})

target_link_libraries(utils PUBLIC Qt5::Widgets Qt5::Core Qt5::Sql 
                Qt5::Qml Qt5::Quick Qt5::PrintSupport
                Qt5::Xml Qt5::Network Qt5::Quick Qt5::Qml)
                
qt5_use_modules(utils Core Widgets Sql Qml Quick QuickControls2)
