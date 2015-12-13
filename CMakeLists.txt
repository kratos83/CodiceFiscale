CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

PROJECT(codicefiscale)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0005 NEW)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

INCLUDE(AddFileDependencies)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckFunctionExists)
INCLUDE(FindPkgConfig)

SET(VERSION_MAJOR "3")
SET(VERSION_MINOR "0")

#SET(VERSION_SUFFIX "")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
IF(VERSION_SUFFIX)
	SET(VERSION "${VERSION}-${VERSION_SUFFIX}")
ENDIF(VERSION_SUFFIX)

INCLUDE(DetectMachine)

#Abilito la compilazione con le qt5
OPTION(WANT_QT5		"Build with Qt5" OFF)
OPTION(WANT_QT4		"Build with Qt4" OFF)


LIST(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

if(WANT_QT5)
	set(QT5 TRUE)
	
	FIND_PACKAGE(Qt5Widgets REQUIRED)
	FIND_PACKAGE(Qt5Gui REQUIRED)
	FIND_PACKAGE(Qt5Core REQUIRED)
	FIND_PACKAGE(Qt5Xml REQUIRED)
	FIND_PACKAGE(Qt5Network REQUIRED)
	FIND_PACKAGE(Qt5Sql REQUIRED)
	FIND_PACKAGE(Qt5Svg REQUIRED)
else()
	
	SET(QT5 FALSE)
	
	# check for Qt4
	FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtNetwork QtSql QtSvg Qt3Support REQUIRED)

	SET(QT_USE_QTXML 1)
	IF(WIN32)
		SET(QT_TRANSLATIONS_DIR "${MINGW_PREFIX}/share/qt4/translations/")
	ENDIF(WIN32)

	IF(EXISTS "${QT_TRANSLATIONS_DIR}")
		MESSAGE("-- Found Qt translations in ${QT_TRANSLATIONS_DIR}")
		ADD_DEFINITIONS(-D'QT_TRANSLATIONS_DIR="${QT_TRANSLATIONS_DIR}"')
	ENDIF()
	IF(NOT WIN32)
		STRING(REPLACE "-DQT_DLL" "" QT_DEFINITIONS "${QT_DEFINITIONS}")
	ENDIF()
	INCLUDE("${QT_USE_FILE}")
endif()

# set compiler flags
SET(WERROR_FLAGS "-Wall -Werror=unused-function -Wno-sign-compare -Wno-strict-overflow")
OPTION(USE_WERROR "Add -werror to the build flags. Stops the build on warnings" OFF)
IF(${USE_WERROR})
   SET(WERROR_FLAGS "${WERROR_FLAGS} -Werror")
ENDIF()

# Due to a regression in gcc-4.8.X, we need to disable array-bounds check
IF (CMAKE_COMPILER_IS_GNUCXX AND ((CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL "4.8.0") OR (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "4.8.0") OR FABARIAGEST_BUILD_WIN32))
   SET(WERROR_FLAGS "${WERROR_FLAGS} -Wno-array-bounds")
ENDIF()

IF(NOT CMAKE_BUILD_TYPE)
	message(STATUS "Setting build type to 'Release' as none was specified.")
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
	# Set the possible values of build type for cmake-gui
	SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
  		"MinSizeRel" "RelWithDebInfo")
ENDIF()

SET(CMAKE_C_FLAGS "${WERROR_FLAGS} ${CMAKE_C_FLAGS}")
SET(CMAKE_CXX_FLAGS "-fno-exceptions ${WERROR_FLAGS} ${CMAKE_CXX_FLAGS}")
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCODICEFISCALE_DEBUG")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCODICEFISCALE_DEBUG")

# set up apple vars before traversing into data/scripts
SET(MACOSX_BUNDLE_ICON_FILE "codicefiscale.icns")
SET(MACOSX_BUNDLE_GUI_IDENTIFIER "CODICEFISCALE")
SET(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION}")
SET(MACOSX_BUNDLE_BUNDLE_NAME "CODICEFISCALE")
SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}")
SET(MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION}")
SET(MACOSX_BUNDLE_COPYRIGHT "Codelinsoft, 2011-2015")
SET(MACOSX_BUNDLE_MIMETYPE "application/x-codicefiscale-project")
SET(MACOSX_BUNDLE_MIMETYPE_ICON "codicefiscale.icns")
SET(MACOSX_BUNDLE_MIMETYPE_ID "http://www.codelinsoft.it")
SET(MACOSX_BUNDLE_PROJECT_URL "http://www.codelinsoft.it")

IF(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-attributes")
ELSE(WIN32)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DPIC")
ENDIF(WIN32)

# make sub-directories
ADD_SUBDIRECTORY(cod_fisc)
ADD_SUBDIRECTORY(update)

#
# add distclean-target
#
ADD_CUSTOM_TARGET(distclean
			COMMAND make clean
			COMMAND rm -rf `find -name cmake_install.cmake` `find -name Makefile` `find -type d -name CMakeFiles` CMakeCache.txt)

#
# display configuration information
#

MESSAGE("\n"
"Installation Summary\n"
"--------------------\n"
"* Install Directory           : ${CMAKE_INSTALL_PREFIX}\n"
"* Build type                  : ${CMAKE_BUILD_TYPE}\n"
"* Platform                    : ${CMAKE_SYSTEM_PROCESSOR} (${Machine})\n"
)

MESSAGE(
"\n"
"-----------------------------------------------------------------\n"
"IMPORTANT:\n"
"after installing missing packages, remove CMakeCache.txt before\n"
"running cmake again!\n"
"-----------------------------------------------------------------\n"
"\n\n")

INCLUDE(InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "CODICEFISCALE - software aziendale!")
SET(CPACK_PACKAGE_VENDOR "Codelinfoft Developers")
IF(FABARIAGEST_BUILD_APPLE)
	CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/README" "${CMAKE_BINARY_DIR}/README.txt" COPYONLY)
	CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/COPYING" "${CMAKE_BINARY_DIR}/COPYING.txt" COPYONLY)
	SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_BINARY_DIR}/README.txt")
	SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_BINARY_DIR}/COPYING.txt")
ELSE(FABARIAGEST_BUILD_APPLE)
	SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README")
	SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
ENDIF(FABARIAGEST_BUILD_APPLE)

SET(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")

IF(VERSION_SUFFIX)
	SET(CPACK_PACKAGE_VERSION_PATCH "${VERSION_SUFFIX}")
ENDIF(VERSION_SUFFIX)
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CodiceFiscale")
IF(WIN32)
	SET(CPACK_GENERATOR NSIS)
	SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "
		!define MUI_ICON  \\\"${CMAKE_SOURCE_DIR}/cod_fisc/images/codice_fisc.ico\\\"
		!define MUI_UNIICON \\\"${CMAKE_SOURCE_DIR}/cod_fisc/images/codice_fisc.ico\\\" ")
	SET(CPACK_NSIS_INSTALLER_MUI_FINISHPAGE_RUN_CODE " !define MUI_FINISHPAGE_RUN \\\"$INSTDIR\\\\codicefiscale.exe\\\" 							           !define MUI_FINISHPAGE_SHOWREADME \\\"$INSTDIR\\\\README.txt\\\" ")
	SET(CPACK_NSIS_INSTALLED_ICON_NAME "codicefiscale.exe")
	SET(CPACK_NSIS_DISPLAY_NAME "CodiceFiscale ${VERSION}")
	SET(CPACK_NSIS_HELP_LINK "http://www.codelinsoft.it")
	SET(CPACK_NSIS_URL_INFO_ABOUT "http://www.codelinsoft.it")
	SET(CPACK_NSIS_CONTACT "info@codelinsoft.it")
	SET(CPACK_PACKAGE_EXECUTABLES "codicefiscale.exe;CodiceFiscale")
	SET(CPACK_NSIS_MENU_LINKS "codicefiscale.exe;CodiceFiscale")
	SET(CPACK_CREATE_DESKTOP_LINKS "codicefiscale.exe;CodiceFiscale")
	set(CPACK_NSIS_CREATE_ICONS_EXTRA "
    	CreateShortCut \\\"$DESKTOP\\\\CodiceFiscale.lnk\\\" \\\"$INSTDIR\\\\codicefiscale.exe\\\" ")
	set(CPACK_NSIS_DELETE_ICONS_EXTRA "
    		Delete \\\"$DESKTOP\\\\CodiceFiscale.lnk\\\"")
	SET(CPACK_NSIS_DEFINES "!include ${CMAKE_SOURCE_DIR}/cmake/nsis/FileAssociation.nsh")
	SET(CPACK_PACKAGE_FILE_NAME "CodiceFiscale-${VERSION}-win32")
ELSE(WIN32)
	SET(CPACK_PACKAGE_EXECUTABLES "codicefiscale" "CodiceFiscale binary")
ENDIF(WIN32)

IF(WIN64)
	SET(CPACK_PACKAGE_FILE_NAME "CodiceFiscale-${VERSION}-win64")
	SET(CPACK_NSIS_DEFINES "${CPACK_NSIS_DEFINES}
		InstallDir \\\"\\\$PROGRAMFILES64\\\\${CPACK_PACKAGE_INSTALL_DIRECTORY}\\\"")
ENDIF(WIN64)

SET(CPACK_SOURCE_GENERATOR "TBZ2")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "CodiceFiscale-${VERSION}")
INCLUDE(CPack)

