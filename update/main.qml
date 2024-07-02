/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
**
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

import QtQuick 2.8
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.0
import Codelinsoft 1.0

ApplicationWindow {
    id: root
    visible: true
    x: Screen.width / 2 - width / 2
    y: Screen.height / 2 - height / 2
    title: qsTr("Gestore aggiornamento")
    property alias testoUrl: agg.testoUrl
    property alias testoPkg: agg.testoPkg
    
   ColumnLayout{
       id: mainLayout
       anchors.fill: parent
       spacing: 4
    GroupBox{
        id:box 
        anchors.top: parent.top
        Layout.fillHeight: true
        Layout.fillWidth: true
        
      GridLayout{
          anchors.fill: parent
          rows: 5
          flow: GridLayout.TopToBottom
          
        Image{
            id:lab_image
            Layout.fillHeight: true
            Layout.fillWidth: true
            source: "qrc:/images/codice_fiscale_logo.png";
        }
        
        RowLayout{
        //Inizializzo la progressBar aggiornamento
            Label{
                id:txt_agg
                text: qsTr("Download aggiornamento")
            }
            Item{
                id: spacing
                Layout.fillWidth: true
                Layout.preferredHeight: 14
                Layout.preferredWidth: 14
            }
            //Inizializzo la progressBar Installazione
            Label{
                id:unzip_file
                text: qsTr("Installazione")
            }
            Item{
                id: spacing1
                Layout.fillWidth: true
                Layout.preferredHeight: 14
                Layout.preferredWidth: 20
            }
        }
        RowLayout{
            ProgressBar{
                id:pr_agg
                Layout.fillWidth: true
            }
            ProgressBar{
                id: pr_unzip_file
                value: agg.getInstallPackage
                Layout.fillWidth: true
            }
        
        //Button pause
        Button{
            id:bt_pause
            iconSource: "qrc:/images/pause.png"
            Layout.fillWidth: true
            Layout.maximumWidth: 25
            Layout.maximumHeight: 25
            enabled: false
            onClicked: {agg.pause()}
        }
        }
        Label{
            id:label_pacchetti
            Layout.fillHeight: true
        }
        Label{
            id:label_velocita
            Layout.fillHeight: true
        }
      }
    }
    
    GroupBox{
        id:gr_button
        anchors.bottom: parent.bottom
        Layout.fillHeight: true
        Layout.fillWidth: true
        
      GridLayout{
        anchors.fill: parent
        rows: 1
        flow: GridLayout.TopToBottom
        
        Item{
            id:spacing2
            Layout.fillWidth: true
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }
        Button{
            id:bt_install
            iconSource: "qrc:/images/install.png"
            text: "<font color='black'>"+qsTr("Installa aggiornamento")+"</font>"
            onClicked: {agg.install_package()}
        }
        
        Button{
            id: bt_download
            iconSource: "qrc:/images/upgrade.png"
            text: "<font color='black'>"+qsTr("Download aggiornamento")+"</font>"
            onClicked:{bt_pause.enabled=true,agg.download()}
        }
        }
    }
    
    Update{
        id:agg
        onChangeText:{
            label_pacchetti.text= agg.fileDown,
            label_velocita.text=agg.speedDown,
            pr_agg.maximumValue=agg.getByteTotali,
            pr_agg.value=agg.getByteRicevuti,
            pr_unzip_file.maximumValue= agg.getInstallPackage
        }
    }
   }
}
