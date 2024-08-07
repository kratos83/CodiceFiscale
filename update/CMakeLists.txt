project(update)
cmake_minimum_required(VERSION 2.8)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules )

if(WIN32)
SET( CMAKE_CXX_FLAGS  "-std=c++11 -mwindows" )
ELSE()
SET( CMAKE_CXX_FLAGS  "-std=c++11" )
ENDIF()

find_package(Qt5Core  REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui   REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Qml   REQUIRED)
find_package(Qt5Quick REQUIRED)

set(update "update")

set(update_includes
${CMAKE_BINARY_DIR}/update
)

include_directories(${update_includes})

set(update_moc_hdrs 
	update.h 
        settingsmanager.h
)

qt5_wrap_cpp(update_mocs ${update_moc_hdrs})

set(update_srcs 
	main.cpp
        update.cpp 
        settingsmanager.cpp
)

qt5_add_resources(RESOURCE_FILES update.qrc lang.qrc) 

IF(WIN32)
    LINK_LIBRARIES(-lws2_32 -lwtsapi32 -lnetapi32 -luserenv -ladvapi32 ${QT_LIBRARIES})
    SET(CMAKE_MODULE_LINKER_FLAGS -Wl,-export-all-symbols)
endif(WIN32)

IF(WIN64)
ADD_DEFINITIONS(-D_X64)
ENDIF(WIN64)

IF(WIN32)
	SET(WINRC "${CMAKE_CURRENT_BINARY_DIR}/update.obj")
	ADD_DEFINITIONS(-D__USE_MINGW_ANSI_STDIO=1)
	ADD_CUSTOM_COMMAND(OUTPUT ${WINRC}
						COMMAND ${WINDRES}
							-I${CMAKE_CURRENT_SOURCE_DIR}
							-o${WINRC}
							-i${CMAKE_CURRENT_BINARY_DIR}/winicon.rc
						DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/winicon.rc)

ENDIF(WIN32)

LINK_LIBRARIES(-lpthread)
if(APPLE)
set(SOURCE_FILES ${SOURCE_FILES} images/upgrade.icns)
set_source_files_properties(images/upgrade.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
ADD_EXECUTABLE(update MACOSX_BUNDLE ${update_srcs} ${update_mocs} ${RESOURCE_FILES} ${WINRC})
ELSE()
ADD_EXECUTABLE(update ${update_srcs} ${update_mocs} ${RESOURCE_FILES} ${WINRC})
ENDIF()

target_link_libraries( update
  Qt5::Widgets Qt5::Xml
  Qt5::Network Qt5::Gui 
  Qt5::Sql Qt5::Core 
  Qt5::Svg Qt5::Qml 
  Qt5::Quick 
)

IF(WIN32)
    INSTALL( TARGETS update RUNTIME DESTINATION .)
elseif(APPLE)
    INSTALL( TARGETS update BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/codicefiscale)
else()
     INSTALL( TARGETS update RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/codicefiscale)
endif()

# set up apple vars before traversing into data/scripts
SET(MACOSX_BUNDLE_ICON_FILE "upgrade.icns")
SET(MACOSX_BUNDLE_GUI_IDENTIFIER "UPDATE")
SET(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION}")
SET(MACOSX_BUNDLE_BUNDLE_NAME "Upgrade software")
SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}")
SET(MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION}")
SET(MACOSX_BUNDLE_COPYRIGHT "Codelinsoft, 2011-2015")
SET(MACOSX_BUNDLE_MIMETYPE "application/x-fabariagest-project")
SET(MACOSX_BUNDLE_MIMETYPE_ICON "logo4.icns")
SET(MACOSX_BUNDLE_MIMETYPE_ID "http://www.codelinsoft.it")
SET(MACOSX_BUNDLE_PROJECT_URL "http://www.codelinsoft.it")
