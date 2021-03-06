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
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.2

Rectangle {
    id: barButton

    property bool checked: false
    property bool checkable: false
    property string iconSource: ""
    property alias testo : buttonText.text
    property string toolTip: ""
    Accessible.name: testo
    Accessible.role: Accessible.Button
    Accessible.checked: checked
    Accessible.checkable: checkable
    Accessible.onPressAction: {
        barButton.clicked()
    }
        
    signal clicked

    width: {
        if(iconSource==""){
            buttonText.anchors.centerIn=barButton;
            (buttonText.width+20)
        }
        else{
            buttonText.x= 30;
            buttonText.y= 6;
            (buttonText.width+20) + (images.width)
        }
    }
    height: 30
    
    Gradient {
        id: lightGradient
        GradientStop { position: 0.0; color: "transparent" }
        GradientStop { position: 1.0; color: "transparent" }
    }

    Gradient {
        id: darkGradient
        GradientStop { position: 0.0; color: Qt.darker(barButton.color,1.7) }
        GradientStop { position: 1.0; color: Qt.darker(barButton.color,1.7) }
    }
    
    gradient: mouseArea.pressed ? darkGradient : lightGradient
    
    
    radius: 2
    antialiasing: true
    
    Image{
        id: images
        source: iconSource
        anchors.margins: 5
        anchors.left: parent.left
        width: 22
        height: 22
        y:5.5
    }

    Text {
        id: buttonText
        color: "black"
    }
    
    TooltipButton{
        id: tool
        textToolTip: toolTip
        showToolTip: false
        opacita: 0.6
    }
    
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if(checkable){ 
                gradient = darkGradient
                checked = !checked
                if(!checked)
                    gradient = lightGradient
            }
            parent.clicked()
        }
        hoverEnabled: true
    }

    Keys.onSpacePressed: clicked()
}
