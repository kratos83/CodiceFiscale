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
import QtQuick.Layouts 1.2
import QtQuick.Window 2.0

Item {
    property alias mCodice: mCodice
    property alias mSurname: mSurname
    property alias mName: mName
    property alias mLuogoDiNascita: mLuogoDiNascita
    property alias mProvincia: mProvincia
    property alias mData: mData
    property alias mSesso: mSesso
    property alias imgageUpdate: imgageUpdate
    
    GridLayout{
        anchors.fill: parent
        flow: GridLayout.TopToBottom
        GroupBox{
            id: boxPage2
            anchors.top: parent.top
            Layout.fillHeight: true
            Layout.fillWidth: true
            GridLayout{
                anchors.fill: parent
                rows: 4
                flow: GridLayout.TopToBottom
                Image {
                    id: imgageUpdate
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/images/codicefiscale.png";
                    
                    //Codice
                    Label{id: mCodice;font.pixelSize: 14;font.bold:true;x: 80;y: 110 }
                    //Cognome
                    Label{id: mSurname;font.pixelSize: 14;font.bold:true;x: 80;y: 137}
                    //Nome
                    Label{id: mName;font.pixelSize: 14;font.bold:true;x: 80;y: 159}
                    //Luogo di nascita
                    Label{id: mLuogoDiNascita;font.pixelSize: 14;font.bold:true;x: 80;y: 185}
                    //Luogo di nascita
                    Label{id: mProvincia;font.pixelSize: 14;font.bold:true;x: 80;y: 210}
                    //Data di nascita
                    Label{id: mData;font.pixelSize: 14;font.bold:true;x: 80;y: 240}
                    //Sesso
                    Label{id:mSesso;font.pixelSize: 14;font.bold:true;x: 375;y: 158}
                    //Fac simile
                    Label{id: facsimile; text: qsTr("FACSIMILE");font.pixelSize: 22;font.bold:true;x: 260;y: 225}
                }
                RowLayout{
                    Item{
                        id: spacing3
                        Layout.fillWidth: true
                        Layout.preferredHeight: 25
                        Layout.preferredWidth: 30
                    }

                    Bottone{
                        id: chiudi
                        text: qsTr("Torna indietro")
                        iconSource: "qrc:/images/return.svg"
                        onClicked: pageImpo.pop(pageMain1)
                    }
                }
            }
        }
    }
}
