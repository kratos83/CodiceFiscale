#-------------------------------------------------
#
# Project created by QtCreator 2011-02-27T17:21:20
#
#-------------------------------------------------

greaterThan(QT_MINOR_VERSION, 4){
 QT += core gui qt3support xml network
}

greaterThan(QT_MAJOR_VERSION, 4){
 QT += core gui widgets printsupport xml network
}

TARGET = codicefiscale
TEMPLATE = app
CONFIG += release




OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build

SOURCES +=  main.cpp\
            cod_fisc.cpp \
            print.cpp \
            about.cpp \
            verify_piva.cpp \
    	    verify_codicefiscale.cpp \
            find_cap_italian.cpp \
            pref.cpp \
            settingsmanager.cpp

HEADERS  += cod_fisc.h \
            print.h \
            about.h \
            verify_piva.h \
	    verify_codicefiscale.h \
            find_cap_italian.h \
            pref.h \
            settingsmanager.h


FORMS    += ui/cod_fisc.ui \ 
            ui/about.ui \
            ui/verify_piva.ui \
            ui/verify_codicefiscale.ui \
            ui/find_cap_italian.ui \
            ui/pref.ui


unix{

codicefiscale_desktop_file.path = /usr/share/applications
codicefiscale_desktop_file.files = desktop/*

codicefiscale_logo.path=/opt/codicefiscale
codicefiscale_logo.files= images/codicefisc.png

target.path = /opt/codicefiscale/

INSTALLS += codicefiscale_desktop_file codicefiscale_logo target
macx:ICON = images/codicefiscale.icns
}

RESOURCES = cod_fisc.qrc \
            lang.qrc
RC_FILE = winicon.rc

TRANSLATIONS = language/English.ts \
               language/Italian.ts
