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
import "script.js" as Verifica

Item {
    id: pIva
    
    ColumnLayout{
       id: mainLayout
       anchors.fill: parent
       spacing: 4
       
        GroupBox{
            id: box 
            anchors.top: parent.top
            Layout.fillHeight: true
            Layout.fillWidth: true
            
            GridLayout{
                anchors.fill: parent
                rows: 4
                flow: GridLayout.TopToBottom
                
                Image{
                    id: img_about
                    fillMode: Image.Stretch
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/images/p_iva_large.png";
                }
                
                RowLayout{
                    
                    Label{
                        text: qsTr("Inserisci la partita iva")
                    }
        
                    TextField{
                        id: txt
                        Layout.fillWidth: true
                        font.pixelSize: 14; font.bold: true
                        focus: true
                        placeholderText: qsTr("Inserisci la partita iva")
                    }
                    Image{
                        id: img_iva
                    }
                }
                
                Label{
                    id: label_iva
                }
        
                RowLayout{
                    
                    Item{
                        id: spacing
                        Layout.fillWidth: true
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 30
                    }
                    Bottone{
                        id: bt_ver
                        text: qsTr("Verifica")
                        iconSource: "qrc:/images/dialog-ok-apply.svg"
                        onClicked: Verifica.controllaPIVA(txt.text)
                    }
        
                    Bottone{
                        id: bt_ex
                        text: qsTr("Torna indietro")
                        iconSource: "qrc:/images/return.svg"
                        onClicked: pageImpo.pop(pageMain1)
                    }
                }
            }
        }
    }
    
}
