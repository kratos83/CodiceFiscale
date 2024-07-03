/****************************************************************************
**
** Copyright (C) 2006-2014 Angelo e Calogero Scarna
** Contact: Angelo Scarnà (angelo.scarna@codelinsoft.it)
**          Calogero Scarnà (calogero.scarna@codelinsoft.it)
**          Team Codelinsoft (info@codelinsoft.it)
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
import QtQuick.Layouts 1.2
import QtQuick.Window 2.0
import Codelinsoft.Utils 1.0

Rectangle {
    property alias radioUpAgg: radioUpAgg
    property alias radioDisAgg: radioDisAgg
    property alias btImpoAgg: btImpoAgg
    color: "white"
    signal loadApply
    
    GridLayout{
         anchors.fill: parent
         flow: GridLayout.TopToBottom
         GroupBox{
             title: "<font color='black'>"+qsTr("Aggiornamento")+"</font>"
             anchors.top: parent.top
             Layout.fillHeight: true
             Layout.fillWidth: true
             GridLayout{
                 anchors.fill: parent
                 flow: GridLayout.TopToBottom
                 rows: 6
                 RadioButton{
                    id: radioUpAgg
                    checked: false
                    Layout.fillWidth: true
                    text: "<font color='black'>"+qsTr("Abilita aggiornamenti")+"</font>"
                    onClicked: {
                            radioDisAgg.checked=false
                            btImpoAgg.visible=true
                    }
                }
                Item{
                    id: spacing14
                    Layout.fillHeight: true
                    Layout.preferredHeight: 14
                }
                RadioButton{
                    id: radioDisAgg
                    checked: false
                    Layout.fillWidth: true
                    text: "<font color='black'>"+qsTr("Disabilita aggiornamenti")+"</font>"
                    onClicked: {
                            radioUpAgg.checked=false
                            btImpoAgg.visible=false
                    }
                }
                Item{
                    id: spacing15
                    Layout.fillHeight: true
                    Layout.preferredHeight: 14
                }
                RowLayout{
                    Item{
                        id: spacing16
                        Layout.fillWidth: true
                        Layout.preferredWidth: 14
                    }
                    Bottone{
                        id: btImpoAgg
                        text: qsTr("Aggiorna")
                        iconSource: "qrc:/images/system-software-update.svg"
                        onClicked: impo.self_update()
                    }
                    Item{
                        id: spacing17
                        Layout.fillWidth: true
                        Layout.preferredWidth: 14
                    }
                }
                Item{
                    id: spacing18
                    Layout.fillHeight: true
                    Layout.preferredHeight: 14
                }
            }
         }
         RowLayout{
            Item{
                id: spacing19
                Layout.fillWidth: true
                Layout.preferredWidth: 14
            }
            Bottone{
                id: bt_ex
                text: qsTr("Torna indietro")
                iconSource: "qrc:/images/return.svg"
                onClicked: pageImpo.pop(pageMain1)
            }
            Bottone{
                id: bt_app
                text: qsTr("Applica")
                iconSource: "qrc:/images/dialog-ok-apply.svg"
                onClicked: applica()
            }
        }
    }
    Preferences{
        id: impo
        getVersione: setting.generalValue("Version/version")
    }
    
    SettingsManager{
        id: setting
    }
    
    Component.onCompleted:{
        readSettings();
    }
    
    function readSettings(){
        if(setting.generalValue("Update/agg_en").toString()==="true"){
            radioUpAgg.checked=true
            btImpoAgg.visible=true
        }
        else
            radioUpAgg.checked=false
        if(setting.generalValue("Update/agg_dis").toString()==="true"){
            radioDisAgg.checked=true
            btImpoAgg.visible=false
        }
        else
            radioDisAgg.checked=false
    }
    
    function applica(){
        setting.setGeneralValue("Update/agg_en",radioUpAgg.checked);
        setting.setGeneralValue("Update/agg_dis",radioDisAgg.checked);
        readSettings();
        loadApply();
    }
}
