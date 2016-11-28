CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)
cmake_policy(SET CMP0043 OLD)

project(utils)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h" "qmldir")
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")

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

include_directories(${utils_includes} 
                    ${Qt5PrintSupport_INCLUDE_DIRS})


qt5_wrap_cpp(MOC_SOURCES ${HEADERS})


IF(WIN32)
    LINK_LIBRARIES(-lws2_32 -lwtsapi32 -lnetapi32 -luserenv -ladvapi32 )
    SET(CMAKE_MODULE_LINKER_FLAGS -Wl,-export-all-symbols)
endif(WIN32)

IF(WIN64)
ADD_DEFINITIONS(-D_X64)
ENDIF(WIN64)

LINK_LIBRARIES(-lpthread Qt5::Widgets Qt5::Core Qt5::Sql 
                Qt5::Qml Qt5::Quick Qt5::PrintSupport
                Qt5::Xml Qt5::Network)


ADD_LIBRARY( utils SHARED ${SOURCES} ${MOC_SOURCES})

set_target_properties(utils PROPERTIES OUTPUT_NAME "utils" PREFIX "")

qt5_use_modules(utils Core Widgets Sql Qml Quick)
