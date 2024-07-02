/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
 *
 *
** This file is part of the project CodiceFiscale
**
** LGPLv3 License
**
**  You may use this file under the terms of the LGPLv3 license as follows:
*
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Codelinsoft and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.2
import QtQuick.Window 2.0
import Codelinsoft.Utils 1.0
import Codelinsoft.Sql 1.0
import "script.js" as Script

ApplicationWindow {
    id: window
    visible: true
    width: 470
    height: 470
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("CodiceFiscale")+" "+manager.generalValue("Version/version") 
    property alias dat: dat 
    property alias pageImpo: pageImpo
    property alias m_model: m_model
    property alias m_model1: m_model1
    property alias pageMain2: pageMain2
    property alias pageMain1: pageMain1
    property alias saveimage: saveimage
    property alias defaultFontPixelSize: hiddenText.font.pixelSize
    property alias defaultFontHeight: hiddenText.implicitHeight
    property real menuProgressOpening
    property int widthOfSeizure: 15*window.dp
    property bool menuIsShown: Math.abs(menuBar.x) < (menuWidth*0.5) ? true : false
    property alias dp: mobile.dpi
    property int menuWidth: window.orientation == window.orientationLandscape ? 300*window.dp : window.width*0.85
    property int orientationPortrait: 1
    property int orientationLandscape: 2
    property int orientation: 0
    onWidthChanged: {
        if( width > height ) {
            window.orientation = window.orientationLandscape
        } else {
            window.orientation = window.orientationPortrait
        }
    }
    Text {
        id: hiddenText
    }
    
    Mobile{ id: mobile}
    SqlDatabase{
        id: dat
        driverDatabase: "QSQLITE"
        nomeDatabase: "codicefiscale.db"
    }

    SqlDataModel{
        id: m_model
    }

    SqlDataModel{
        id: m_model1
    }
    
    SettingsManager{
        id: manager 
    }
    
    Preferences{
        id: impo 
    }
    
    Image{
        id: imgPrintPdf
        source: "qrc:/images/codicefiscale_800x600.png"
        visible: false
    }
        
    //Imposto il menu
    header: RowLayout{
        Bottone{
            id: men
            iconSource: "qrc:/images/icon_menu_gray.svg"
            toolTip: qsTr("Menu")
            onClicked: onMenu()
        }
        Item{ 
            id: spacing7
            Layout.fillWidth: true
            Layout.preferredWidth: 14
        }
    }
    Rectangle{
        id: menuBar
        z: 3
        x: -menuWidth
        antialiasing: true
        
        Behavior on x { NumberAnimation { duration: 500; easing.type: Easing.OutQuad } }
        onXChanged: {
            menuProgressOpening = (1-Math.abs(menuBar.x/menuWidth))
        }

        MouseArea {
            anchors.right: parent.right
            anchors.rightMargin: window.menuIsShown ? (menuWidth - window.width) : -widthOfSeizure
            anchors.top: parent.top
            width: window.menuIsShown ? (window.width - menuWidth) : widthOfSeizure
            height: parent.height
            drag {
                target: menuBar
                axis: Drag.XAxis
                minimumX: -menuBar.width
                maximumX: 0
            }
            onClicked: {
                if(window.menuIsShown) window.onMenu()
            }
            onReleased: {
                if( Math.abs(menuBar.x) > 0.5*menuWidth ) {
                    menuBar.x = -menuWidth //close the menu
                } else {
                    menuBar.x = 0 //fully opened
                }
            }
        }
        ToolBar{
            ColumnLayout{
                BarButton{
                    testo: qsTr("Esci")
                    iconSource: "qrc:/images/exit.svg"
                    onClicked: Qt.quit()
                }
                BarButton{
                    testo: qsTr("Stampa")
                    iconSource: "qrc:/images/document-print.svg"
                    onClicked: {onMenu();saveimage.stampaCodice();}
                }
                BarButton{
                    testo: qsTr("Visualizza anteprima");
                    iconSource: "qrc:/images/document-preview.svg"
                    onClicked: {
                        onMenu();
                        pageMain2.visible=true
                        pageImpo.push(pageMain2)
                    }
                }
                BarButton{
                    testo: qsTr("Esporta in pdf")
                    iconSource: "qrc:/images/pdf.svg"
                    onClicked: {onMenu();saveimage.exportPdf()}
                }
                BarButton{
                    testo: qsTr("Esporta in immagine")
                    onClicked: {onMenu();saveimage.saveImages(pageMain2.imgageUpdate);}
                }
                BarButton{
                    testo: qsTr("Verifica codice fiscale")
                    iconSource: "qrc:/images/codicefisc.png"
                    onClicked: {onMenu();pageImpo.push(Qt.resolvedUrl("VerifyCodicefiscale.qml"))}
                }
                BarButton{
                    testo: qsTr("Verifica partita iva")
                    iconSource: "qrc:/images/iva.png"
                    onClicked: {onMenu();pageImpo.push(Qt.resolvedUrl("VerifyPiva.qml"))}
                }
                BarButton{
                    testo: qsTr("Cerca CAP(Codici avviamenti postali)")
                    iconSource: "qrc:/images/cap.svg"
                    onClicked: {onMenu();pageImpo.push(Qt.resolvedUrl("FindCapItalian.qml"))}
                }
                BarButton{
                    testo: qsTr("Impostazioni")
                    iconSource: "qrc:/images/preferences-system.svg"
                    onClicked: {onMenu();pageImpo.push(Qt.resolvedUrl("Page1.qml"))}
                }
                BarButton{
                    testo: qsTr("Aggiornamento")
                    iconSource: "qrc:/images/system-software-update.svg"
                    onClicked: {onMenu();pageImpo.push(Qt.resolvedUrl("Page2.qml"))}
                }
                BarButton{
                    testo: qsTr("About")
                    iconSource: "qrc:/images/info.svg"
                    onClicked: {onMenu();pageImpo.push(Qt.resolvedUrl("About.qml"))}
                }
                Item{ 
                    id: spacing5 
                    Layout.fillHeight: true
                    Layout.preferredWidth: 14
                }
            }
        }
    }
    
    RectMenu {
        id: mainMenu
        z: 1
        anchors.fill: parent
        color: "grey"
        opacity: window.menuProgressOpening*0.5
    }
    
    RectMessage{
        id: msg
        z:2
        anchors.bottom: parent.bottom
        visible: false
        width: window.width
        height: 100
        text: qsTr("Impostare il carattere per\nuna corretta visualizzazione\n"+
                   "Se usi Linux imposta il carattere Noto Sans,\n" +
                   "se usi windows imposta il carattere Tahoma,\n"+
                   "se usi MacOsX imposta il carattere Fira Sans.")
    }
       GridLayout{
            anchors.fill: parent
            StackView{
                id: pageImpo
                anchors.top: parent.top
                Layout.fillHeight: true
                Layout.fillWidth: true
                initialItem:pageMain1
            }
            Item{
                id: spacing3
                Layout.fillHeight: true
                Layout.preferredHeight: 14
            }
       }
      footer:RowLayout{
                Item{
                    id: spacing4
                    Layout.fillWidth: true
                    Layout.preferredWidth: 14
                }
                Bottone{
                    id: calcola
                    text: qsTr("Calcola")
                    toolTip: qsTr("Calcola")
                    iconSource: "qrc:/images/codicefisc.png"
                    onClicked:{
                        if(pageMain1.cognome.text=="" || pageMain1.nome.text == "" 
                           && pageMain1.maschio.checked==false && pageMain1.femmina.checked==false){
                                messageDialog.visible = true;
                        }
                        else
                            pageMain1.calcolo.text=Script.calcolaCodiceFiscale(pageMain2.mName.text,pageMain2.mSurname.text,pageMain2.mSesso.text,pageMain2.mData.text,pageMain2.mData.text,pageMain2.mData.text,pageMain2.mLuogoDiNascita.text)
                    }
                }
                Bottone{
                    id: cancella
                    text: qsTr("Cancella")
                    toolTip: qsTr("Cancella")
                    iconSource: "qrc:/images/edit-delete.svg"
                    onClicked: Script.cancella()
                }
                Bottone{
                    id: esci
                    text: qsTr("Esci")
                    toolTip: qsTr("Esci")
                    iconSource: "qrc:/images/dialog-close.svg"
                    onClicked: Qt.quit();
                }
            }
    
    PageMain1{id: pageMain1}
    PageMain2{id: pageMain2;visible: false}
    
    
    SaveImage{
        id: saveimage
        getSurname: pageMain2.mSurname.text
        getName: pageMain2.mName.text
        getSesso: pageMain2.mSesso.text
        getComuneStato: pageMain2.mLuogoDiNascita.text
        getProvincia: pageMain2.mProvincia.text
        getData: pageMain2.mData.text
        getCodice: pageMain2.mCodice.text
    }
    
    Message {
        id: messageDialog
        titolo: qsTr("CodiceFiscale")
        informativeText: qsTr("Inserisci i dati correttamente.\n\n"+
                   "Controlla il cognome\n"+
                   "Controlla il nome\n"+
                   "Controlla il sesso")
        icon: "qrc:/images/dialog-warning.svg"
        visible: false
    }
    
    function onMenu() {
        menuBar.x = window.menuIsShown ? -menuWidth : 0
    }
    
    function visRectMessage()
    {
        if(Qt.platform.os == "linux")
        {
            if(manager.generalValue("Application/applicationFontMain") != "Noto Sans" ||
               manager.generalValue("Application/fontMain") != "Noto Sans")
                msg.visible=true
        }
        else if(Qt.platform.os == "windows")
        {
            if(manager.generalValue("Application/applicationFontMain") != "Tahoma" ||
               manager.generalValue("Application/fontMain") != "Tahoma")
                msg.visible=true
        }
        else if(Qt.platform.os == "darwin")
        {
            if(manager.generalValue("Application/applicationFontMain") != "Fira Sans" ||
               manager.generalValue("Application/fontMain") != "Fira Sans")
                msg.visible=true
        }
    }
    
    Component.onCompleted:{
        dat.openDatabase();
        visRectMessage()
        m_model.setExcecuteQuery("select paese from paesi");
        m_model1.setExcecuteQuery("select stato from stati")
    }
}

