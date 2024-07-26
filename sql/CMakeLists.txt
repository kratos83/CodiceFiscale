CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
cmake_policy(SET CMP0043 OLD)
set(CMAKE_MACOSX_RPATH 1)
project(sqldatabase)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h" "qmldir")
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")

find_package(Qt5Core  REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Qml   REQUIRED)
find_package(Qt5Quick REQUIRED)


set(sqldatabase_includes
${CMAKE_BINARY_DIR}
)

include_directories(${sqldatabase_includes})


qt5_wrap_cpp(MOC_SOURCES ${HEADERS})


IF(WIN32)
    LINK_LIBRARIES(-lws2_32 -lwtsapi32 -lnetapi32 -luserenv -ladvapi32 )
    SET(CMAKE_MODULE_LINKER_FLAGS -Wl,-export-all-symbols)
endif(WIN32)

IF(WIN64)
ADD_DEFINITIONS(-D_X64)
ENDIF(WIN64)

LINK_LIBRARIES(Qt5::Widgets Qt5::Core Qt5::Sql  Qt5::Qml Qt5::Quick)

if(WIN32)
    ADD_LIBRARY( sqldatabase SHARED ${SOURCES} ${MOC_SOURCES})
    set_target_properties(sqldatabase PROPERTIES OUTPUT_NAME "sqldatabase" PREFIX "")
    file(WRITE qmldir "module Codelinsoft.Sql\n plugin sqldatabase")
    qt5_use_modules(sqldatabase Core Widgets Sql Qml Quick)
elseif (ANDROID)
  add_library(sqldatabase SHARED ${SOURCES} ${MOC_SOURCES})
  file(WRITE qmldir "module Codelinsoft.Sql\n plugin sqldatabase")
  qt5_use_modules(sqldatabase Core Widgets Sql Qml Quick)
else()
ADD_LIBRARY( sqldatabase SHARED ${SOURCES} ${MOC_SOURCES})
file(WRITE qmldir "module Codelinsoft.Sql\n plugin sqldatabase")
target_link_libraries(sqldatabase Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Qml Qt5::Quick)
endif(WIN32)
