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

import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import Codelinsoft.Sql 1.0
import Codelinsoft.Utils 1.0
import "script.js" as Visualizza

Rectangle {
    id: main1 
    property alias cognome: cognome
    property alias nome: nome
    property alias maschio: maschio
    property alias femmina: femmina
    property alias combo: combo
    property alias combo_cm_st: combo_cm_st
    property alias calendario: calendario
    property alias calcolo: calcolo
    signal applica;
    
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        GroupBox{
            id: box 
            anchors.top: parent.top
            Layout.fillHeight: true
            Layout.fillWidth: true
            GridLayout{
                anchors.fill: parent
                flow: GridLayout.TopToBottom
                RowLayout{
                    Label{
                        id: cog
                        text: qsTr("Cognome")
                    }
                    TextField{
                        id: cognome
                        Layout.fillWidth: true
                        focus: true
                        placeholderText: qsTr("Cognome")
                        onTextChanged: {text=text.toUpperCase();pageMain2.mSurname.text=cognome.text; }
                    }
                }
                RowLayout{
                    Label{
                        id: nom
                        text: qsTr("Nome")
                    }
                    TextField{
                        id: nome
                        Layout.fillWidth: true
                        focus: true
                        placeholderText: qsTr("Nome")
                        onTextChanged: {text=text.toUpperCase();pageMain2.mName.text=nome.text; }
                    }
                }
                RowLayout{
                    Label{
                        id: sex
                        text: qsTr("Sesso")
                    }
                    RadioButton{
                        id: maschio
                        text: qsTr("M")
                        onClicked:{ pageMain2.mSesso.text=maschio.text; femmina.checked=false}
                    }
                    RadioButton{
                        id: femmina
                        text: qsTr("F")
                        onClicked:{ pageMain2.mSesso.text=femmina.text; maschio.checked=false}
                    }
                    Item{
                        id: spacing
                        Layout.fillWidth: true
                        Layout.preferredWidth: 14
                    }
                }
                RowLayout{
                    Label{
                        id: select
                        text: qsTr("Seleziona")
                    }
                    ComboBox{
                        id: combo
                        editable: true
                        Layout.fillWidth: true
                        model: [qsTr("Comuni"),qsTr("Stati")]
                        onCurrentIndexChanged:{
                            if(combo.currentIndex==0){
                                combo_cm_st.model=m_model;
                            }
                            else if(combo.currentIndex==1){
                                combo_cm_st.model=m_model1;
                            }
                        }
                    }
                }
                RowLayout{
                    Label{
                        id: lab_cm_st
                        text: qsTr("Comuni o Stato")
                    }
                    ComboBox{
                        id: combo_cm_st
                        model: m_model
                        editable: true
                        Layout.fillWidth: true
                        currentIndex: 0
                    }
                }
                RowLayout{
                    Label{
                        id: date 
                        text: qsTr("Data di nascita")
                    }
                    Calendario{
                        id: calendario
                        Layout.fillWidth: true
                    }
                    Item{
                        id: spacing1
                        Layout.fillWidth: true
                        Layout.preferredWidth: 14
                    }
                }
                RowLayout{
                    Label{
                        id: codice
                        text: qsTr("Codice Fiscale")
                    }
                    TextField{
                        id: calcolo
                        readOnly: true
                        selectByMouse: true
                        Layout.fillWidth: true
                        font.pixelSize: 20
                        font.bold:true
                        placeholderText: qsTr("Calcolo codice fiscale")
                        onTextChanged: {pageMain2.mCodice.text=calcolo.text; }
                    }
                }
            }
        }
    }
    
    SettingsManager{
        id: settings 
    }
}
