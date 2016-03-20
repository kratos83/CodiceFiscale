project(codicefiscale)

cmake_minimum_required(VERSION 2.6)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/modules )

if(WIN32)
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11 -mwindows" )
ELSE()
SET( CMAKE_CXX_FLAGS  "-fexceptions -std=c++11" )
ENDIF()

if(QT5)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} 
		    ${Qt5Core_INCLUDE_DIRS} ${Qt5Sql_INCLUDE_DIRS} 
		    ${Qt5Xml_INCLUDE_DIRS} ${Qt5PrintSupport_INCLUDE_DIRS}
		    ${Qt5Network_INCLUDE_DIRS} ${Qt5Svg_INCLUDE_DIRS})
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Xml REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)
FIND_PACKAGE(Qt5Sql REQUIRED)
FIND_PACKAGE(Qt5Svg REQUIRED)
FIND_PACKAGE(Qt5PrintSupport REQUIRED)
else()
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtNetwork QtSql QtSvg Qt3Support REQUIRED)
include(${QT_USE_FILE})
endif()
set(codicefiscale "codicefiscale")

set(codicefiscale_includes
${CMAKE_BINARY_DIR}/cod_fisc
)

include_directories(${codicefiscale_includes})

set(codicefiscale_moc_hdrs 
	about.h
	cod_fisc.h
	find_cap_italian.h
	pref.h
	print.h
	settingsmanager.h
	verify_codicefiscale.h
	verify_piva.h
)

if(QT5)
qt5_wrap_cpp(codicefiscale_mocs ${codicefiscale_moc_hdrs})
else()
qt4_wrap_cpp(codicefiscale_mocs ${codicefiscale_moc_hdrs})
endif()

set(codicefiscale_uis 
	ui/about.ui
	ui/cod_fisc.ui
	ui/find_cap_italian.ui
	ui/pref.ui
	ui/verify_codicefiscale.ui
	ui/verify_piva.ui
)

if(QT5)
qt5_wrap_ui(codicefiscale_ui_hdrs ${codicefiscale_uis})
else()
qt4_wrap_ui(codicefiscale_ui_hdrs ${codicefiscale_uis})
endif()

set(codicefiscale_srcs 
	about.cpp
	cod_fisc.cpp
	find_cap_italian.cpp
	pref.cpp
	print.cpp
	settingsmanager.cpp
	verify_codicefiscale.cpp
	verify_piva.cpp
	main.cpp
)

if(QT5)
qt5_add_resources(RESOURCE_FILES cod_fisc.qrc lang.qrc) 
else()
qt4_add_resources(RESOURCE_FILES cod_fisc.qrc lang.qrc) 
endif()

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
    ADD_EXECUTABLE(codicefiscale MACOSX_BUNDLE ${codicefiscale_srcs} ${codicefiscale_mocs} ${codicefiscale_ui_hdrs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})
else()
ADD_EXECUTABLE(codicefiscale ${codicefiscale_srcs} ${codicefiscale_mocs} ${codicefiscale_ui_hdrs} ${RESOURCE_FILES} ${WINRC} ${SOURCE_FILES})
endif()

if(QT5)
target_link_libraries( codicefiscale
  Qt5::Widgets Qt5::Xml
  Qt5::Network Qt5::Gui 
  Qt5::Sql Qt5::Core 
  Qt5::Svg Qt5::PrintSupport 
)
else()
target_link_libraries( codicefiscale
  ${QT_LIBRARIES}
)
endif()


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
