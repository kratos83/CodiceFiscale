project(codicefiscale)

cmake_minimum_required(VERSION 2.8.7)
cmake_policy(SET CMP0026 OLD)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules )

if(WIN32)
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11 -mwindows" )
ELSE()
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11" )
ENDIF()

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} 
		    ${Qt5Core_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS} 
		    ${Qt5Xml_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS}
		    ${Qt5Network_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS}
		    ${Qt5Qml_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS}
		    ${Qt5QuickControls2_INCLUDE_DIRS})
find_package(Qt5Core  REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui   REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Qt5Svg REQUIRED)
find_package(Qt5Qml   REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5QuickControls2 REQUIRED)

set(codicefiscale "codicefiscale")

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.cpp" "*.h")
file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
     "*.h")
     
set(codicefiscale_includes
${CMAKE_BINARY_DIR}/cod_fisc
)

include_directories(${codicefiscale_includes})

set(codicefiscale_moc_hdrs 
	settingsmanager.h
)

qt5_wrap_cpp(codicefiscale_mocs ${codicefiscale_moc_hdrs})

set(codicefiscale_srcs 
	settingsmanager.cpp
	main.cpp
)

qt5_add_resources(RESOURCE_FILES cod_fisc.qrc lang.qrc) 

IF(WIN32)
	SET(WINRC "${CMAKE_CURRENT_BINARY_DIR}/fabariagest.obj")
	ADD_DEFINITIONS(-D__USE_MINGW_ANSI_STDIO=1)
	ADD_CUSTOM_COMMAND(OUTPUT ${WINRC}
						COMMAND ${WINDRES}
							-I${CMAKE_CURRENT_SOURCE_DIR}
							-o${WINRC}
							-i${CMAKE_CURRENT_BINARY_DIR}/winicon.rc
						DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/winicon.rc)

ENDIF(WIN32)

LINK_LIBRARIES(-lpthread)

if (APPLE)
    set(SOURCE_FILES ${SOURCE_FILES} images/codicefiscale.icns)
    set_source_files_properties(images/codicefiscale.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    ADD_EXECUTABLE(codicefiscale MACOSX_BUNDLE ${codicefiscale_srcs} ${codicefiscale_mocs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})
else()
ADD_EXECUTABLE(codicefiscale ${codicefiscale_srcs} ${codicefiscale_mocs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})
endif()

target_link_libraries( codicefiscale
  Qt5::Widgets Qt5::Xml
  Qt5::Network Qt5::Gui 
  Qt5::Sql Qt5::Core 
  Qt5::Svg Qt5::PrintSupport 
  Qt5::Quick Qt5::Qml
)

IF(WIN32)
    INSTALL(TARGETS codicefiscale RUNTIME DESTINATION .)
	INSTALL(FILES
		"${MINGW_PREFIX}/bin/Qt5Core.dll"
		"${MINGW_PREFIX}/bin/Qt5Gui.dll"
		"${MINGW_PREFIX}/bin/Qt5Svg.dll"
		"${MINGW_PREFIX}/bin/Qt5Xml.dll"
		"${MINGW_PREFIX}/bin/Qt5Network.dll"
		"${MINGW_PREFIX}/bin/Qt5Sql.dll"
		"${MINGW_PREFIX}/bin/Qt5Widgets.dll"
		"${MINGW_PREFIX}/bin/Qt5Qml.dll"
        "${MINGW_PREFIX}/bin/Qt5Quick.dll"
		"${MINGW_PREFIX}/bin/Qt5PrintSupport.dll"
		"${MINGW_PREFIX}/bin/libexpat-1.dll"
		"${MINGW_PREFIX}/bin/libjpeg-62.dll"
		"${MINGW_PREFIX}/bin/libpng16-16.dll"
		"${MINGW_PREFIX}/bin/libstdc++-6.dll"
		"${MINGW_PREFIX}/bin/libtiff-5.dll"
		"${MINGW_PREFIX}/bin/libtiffxx-5.dll"
		"${MINGW_PREFIX}/bin/libturbojpeg.dll"
		"${MINGW_PREFIX}/bin/zlib1.dll"
		"${MINGW_PREFIX}/bin/libwinpthread-1.dll"
		"${MINGW_PREFIX}/bin/libgcc_s_sjlj-1.dll"
		"${MINGW_PREFIX}/bin/libsqlite3-0.dll"
		"${MINGW_PREFIX}/bin/iconv.dll"
		"${MINGW_PREFIX}/bin/libGLESv2.dll"
		"${MINGW_PREFIX}/bin/libfreetype-6.dll"
		"${MINGW_PREFIX}/bin/libglib-2.0-0.dll"
		"${MINGW_PREFIX}/bin/libharfbuzz-0.dll"
		"${MINGW_PREFIX}/bin/libpcre16-0.dll"
		"${MINGW_PREFIX}/bin/libintl-8.dll"
		"${MINGW_PREFIX}/bin/libbz2-1.dll"
		"${MINGW_PREFIX}/bin/libpcre-1.dll"
		"${MINGW_PREFIX}/bin/d3dcompiler_47.dll"
		"${MINGW_PREFIX}/bin/libEGL.dll"
		"codicefiscale.db"
		"../README.txt"
		DESTINATION .
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt5/plugins/sqldrivers/qsqlite.dll" DESTINATION ./sqldrivers
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt5/plugins/platforms/qminimal.dll" 
		"${MINGW_PREFIX}/lib/qt5/plugins/platforms/qwindows.dll"
		DESTINATION ./platforms
		)
	INSTALL(FILES 
		"${MINGW_PREFIX}/lib/qt5/plugins/printsupport/windowsprintersupport.dll" 
		DESTINATION ./printsupport
		)
    INSTALL(DIRECTORY
        "${MINGW_PREFIX}/lib/qt5/plugins/imageformats/"
        DESTINATION ./imageformats
    )
    INSTALL(DIRECTORY
        "${MINGW_PREFIX}/share/qt5/qml/QtQuick/"
        DESTINATION ./QtQuick)
    INSTALL(DIRECTORY
        "${MINGW_PREFIX}/share/qt5/qml/QtQuick.2/"
        DESTINATION ./QtQuick.2)
    INSTALL(DIRECTORY
        "Codelinsoft/"
        DESTINATION ./Codelinsoft)
	INSTALL(FILES
		"../windows/gunzip.exe"
		"../windows/gzip.exe"
		"../windows/unzip.exe" 
		DESTINATION ./windows )
ELSE()
    INSTALL( TARGETS codicefiscale RUNTIME DESTINATION /opt/codicefiscale)
    INSTALL( FILES "images/codicefiscale.png" DESTINATION /opt/codicefiscale)
    INSTALL( FILES "desktop/codicefiscale.desktop" DESTINATION /usr/share/applications )
endif()

get_target_property(CODFISC codicefiscale LOCATION)
get_filename_component(CODFISC ${CODFISC} PATH)
add_custom_target(codifiscplugindir ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CODFISC}/Codelinsoft/Sql"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sqldatabase> "${CODFISC}/Codelinsoft/Sql"
    COMMAND ${CMAKE_COMMAND} -E copy "../sql/qmldir" "${CODFISC}/Codelinsoft/Sql"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CODFISC}/Codelinsoft/Utils"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:utils> "${CODFISC}/Codelinsoft/Utils"
    COMMAND ${CMAKE_COMMAND} -E copy "../utils/qmldir" "${CODFISC}/Codelinsoft/Utils")
add_dependencies(codicefiscale codifiscplugindir)
