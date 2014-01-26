/****************************************************************************
**
** Copyright (C) 2014 Pier Luigi Fiorini.
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
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
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "app:///components" as Components
import "app:///code/fontawesome.js" as FontAwesome

Item {
    Rectangle {
        color: "#212126"
        anchors.fill: parent
    }

    FontLoader {
        source: "app:///fonts/fontawesome-webfont.ttf"
    }

    // Implements back key navigation
    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            if (stackView.depth > 1) {
                stackView.pop();
                event.accepted = true;
            } else { Qt.quit(); }
        }
    }

    property Item toolBar: BorderImage {
        border.bottom: 8
        source: "images/toolbar.png"
        width: parent.width
        height: 100

        RowLayout {
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter

            Rectangle {
                id: menuButton
                width: 60
                height: 60
                radius: 4
                antialiasing: true
                color: menumouse.pressed ? "#222" : "transparent"
                Behavior on opacity { NumberAnimation{} }
                Text {
                    anchors.centerIn: parent
                    text: FontAwesome.Icon.List
                    font.family: "FontAwesome"
                    font.pointSize: 32
                    color: "white"
                    smooth: true
                }
                MouseArea {
                    id: menumouse
                    anchors.fill: parent
                    onClicked: panel.toggle()
                }
            }

            Rectangle {
                id: homeButton
                width: 60
                height: 60
                radius: 4
                antialiasing: true
                color: homemouse.pressed ? "#222" : "transparent"
                Behavior on opacity { NumberAnimation{} }
                Text {
                    anchors.centerIn: parent
                    text: FontAwesome.Icon.Home
                    font.family: "FontAwesome"
                    font.pointSize: 32
                    color: "white"
                    smooth: true
                }
                MouseArea {
                    id: homemouse
                    anchors.fill: parent
                    onClicked: stackView.pop(null)
                }
            }

            Rectangle {
                id: backButton
                width: 60
                opacity: stackView.depth > 1 ? 1.0 : 0.0
                antialiasing: true
                height: 60
                radius: 4
                color: backmouse.pressed ? "#222" : "transparent"
                Behavior on opacity {
                    SequentialAnimation {
                        NumberAnimation {}
                        ScriptAction {
                            script: backButton.visible = opacity == 1.0
                        }
                    }
                }
                Text {
                    anchors.centerIn: parent
                    text: FontAwesome.Icon.ChevronLeft
                    font.family: "FontAwesome"
                    font.pointSize: 32
                    color: "white"
                    smooth: true
                }
                MouseArea {
                    id: backmouse
                    anchors.fill: parent
                    onClicked: stackView.pop()
                }
            }

            Text {
                font.pixelSize: 42
                color: "white"
                text: "Widget Gallery"
            }
        }
    }

    Components.PageModel {
        id: pageModel
    }

    Rectangle {
        id: panel
        x: -width
        y: 0
        z: 100
        width: 350
        height: parent.height
        color: "#212126"

        Behavior on x {
            NumberAnimation {
                easing.type: Easing.OutExpo
                duration: 250
            }
        }

        RowLayout {
            anchors.fill: parent

            ListView {
                id: panelView
                model: pageModel
                delegate: AndroidDelegate {
                    text: title
                    onClicked: {
                        stackView.push(Qt.resolvedUrl(page));
                        panel.disappear();
                    }
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Rectangle {
                color: "#11ffffff"
                width: 1

                Layout.fillHeight: true
            }
        }

        function appear() {
            x = 0;
        }

        function disappear() {
            x = -width;
        }

        function toggle() {
            if (x == 0)
                disappear();
            else
                appear();
        }
    }

    Components.SwipeArea {
        anchors.fill: parent
        onSwipe: {
            switch (direction) {
            case "left":
                panel.disappear();
                break;
            case "right":
                panel.appear();
                break;
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Item {
            width: parent.width
            height: parent.height

            Label {
                text: "TEST"
                font.pixelSize: 32
            }
        }
    }
}
