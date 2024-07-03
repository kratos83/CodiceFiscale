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
    property alias comboFontEditor: comboFontEditor
    property alias spin: spin
    property alias mcomboFontEditor: mcomboFontEditor
    property alias mspin: mspin
    property alias combo_lng: combo_lng
    signal loadApply
    color: "white"
    
    GridLayout{
         anchors.fill: parent
         rows: 5
         flow: GridLayout.TopToBottom
         GroupBox{
             title: "<font color='black'>"+qsTr("Impostazioni generali")+"</font>"
             anchors.top: parent.top
             Layout.fillHeight: true
             Layout.fillWidth: true
             GridLayout{
                 anchors.fill: parent
                 flow: GridLayout.TopToBottom
                 rows: 4
                 GroupBox{
                    title: "<font color='black'>"+qsTr("Font editor")+"</font>"
                    anchors.top: parent.top
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                        GridLayout{
                            anchors.fill: parent
                            rows: 2
                            columns: 4
                                Label{
                                    id:lab_font
                                    Layout.fillWidth: true
                                    text: "<font color='black'>"+qsTr("Font Name")+"</font>"
                                }
                                Item{
                                    id: spacing
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                Label{
                                    id: fontSize
                                    Layout.fillWidth: true
                                    text: "<font color='black'>"+qsTr("Font size")+"</font>"
                                }
                                Item{
                                    id: spacing1
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                ComboBox{
                                    id: comboFontEditor
                                    Layout.fillWidth: true
                                    editable: true
                                    model: Qt.fontFamilies()
                                }
                                Item{
                                    id: spacing2
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                SpinBox{
                                    id: spin
                                    Layout.fillWidth: true
                                    value: 12
                                }
                                Item{
                                    id: spacing3
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                            }
                        }
                        GroupBox{
                            title: "<font color='black'>"+qsTr("Font application")+"</font>"
                            anchors.horizontalCenter: parent.horizontalCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            GridLayout{
                                anchors.fill: parent
                                rows: 2
                                columns: 4
                                Label{
                                    id:mlab_font
                                    Layout.fillWidth: true
                                    text: "<font color='black'>"+qsTr("Font Name")+"</font>"
                                }
                                Item{
                                    id: spacing5
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                Label{
                                    id: mfontSize
                                    Layout.fillWidth: true
                                    text: "<font color='black'>"+qsTr("Font size")+"</font>"
                                }
                                Item{
                                    id: spacing6
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                ComboBox{
                                    id: mcomboFontEditor
                                    Layout.fillWidth: true
                                    editable: true
                                    model: Qt.fontFamilies()
                                }
                                Item{
                                    id: spacing7
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                SpinBox{
                                    id: mspin
                                    Layout.fillWidth: true
                                    value: 12
                                }
                            }
                        }
                        GroupBox{
                            title: "<font color='black'>"+qsTr("Selezione della lingua")+"</font>"
                            anchors.bottom: parent.bottom
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            GridLayout{
                                anchors.fill: parent
                                rows: 2
                                columns: 4
                                Label{
                                    id:mlab_lng
                                    Layout.fillWidth: true
                                    text: "<font color='black'>"+qsTr("Seleziona la lingua")+"</font>"
                                }
                                Item{
                                    id: spacing10
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                ComboBox{
                                    id: combo_lng
                                    model: ["Italian","English"]
                                    Layout.fillWidth: true
                                }
                                Item{
                                    id: spacing11
                                    Layout.fillWidth: true
                                    Layout.preferredWidth: 14
                                }
                                Label{
                                    id: label_reb
                                    Layout.fillWidth: true
                                    text: "<font color='black'>"+qsTr("La selezione della lingua richiede il riavvio...")+"</font>"
                                    verticalAlignment: Text.AlignVCenter
                                }
                                Item{
                                    id: spacing12
                                    Layout.fillHeight: true
                                    Layout.preferredHeight: 14
                                }
                            }
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
                    text: "<font color='black'>"+qsTr("Torna indietro")+"</font>"
                    iconSource: "qrc:/images/return.svg"
                    onClicked: pageImpo.pop(pageMain1)
                }
                Bottone{
                    id: bt_app
                    text: "<font color='black'>"+qsTr("Applica")+"</font>"
                    iconSource: "qrc:/images/dialog-ok-apply.svg"
                    onClicked: applica()
                }
            }
         }
             
    SettingsManager{
        id: setting
    }
    
    Component.onCompleted:{
        readSettings();
    }
    
    function readSettings(){
        comboFontEditor.currentIndex=setting.generalValue("Application/applicationFont");
        mcomboFontEditor.currentIndex=setting.generalValue("Application/font");
        spin.value=setting.generalValue("Application/sizeAppFont");
        mspin.value=setting.generalValue("Application/sizeFont");
        combo_lng.currentIndex=setting.generalValue("Language/language");
    }
    
    function applica(){
        var index = comboFontEditor.find(comboFontEditor.currentText,Qt.MatchStartsWith);
        if (index >= 0 && index !== comboFontEditor.currentIndex) {
                comboFontEditor.currentIndex = index;
                comboFontEditor.activated(comboFontEditor.currentIndex);
        }
        
        var index1 =mcomboFontEditor.find(mcomboFontEditor.currentText,Qt.MatchStartsWith);
        if (index1 >= 0 && index1 !== mcomboFontEditor.currentIndex) {
                mcomboFontEditor.currentIndex = index1;
                mcomboFontEditor.activated(mcomboFontEditor.currentIndex);
        }
        setting.setGeneralValue("Application/applicationFont",comboFontEditor.currentIndex);
        setting.setGeneralValue("Application/applicationFontMain",comboFontEditor.currentText);
        setting.setGeneralValue("Application/font",mcomboFontEditor.currentIndex);
        setting.setGeneralValue("Application/fontMain",mcomboFontEditor.currentText);
        setting.setGeneralValue("Application/sizeAppFont",spin.value);
        setting.setGeneralValue("Application/sizeFont",mspin.value);
        setting.setGeneralValue("Language/language",combo_lng.currentIndex);
        readSettings();
        loadApply();
    }
}
