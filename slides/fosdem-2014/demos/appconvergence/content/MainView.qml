/****************************************************************************
**
** Copyright (C) 2014 Pier Luigi Fiorini.
**
** $BEGIN_LICENSE:BSD$
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
** $END_LICENSE$
**
****************************************************************************/

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "app:///components" as Components

Item {
    property Item toolBar: ToolBar {
        RowLayout {
            ToolButton {
                iconName: "go-previous"
                enabled: stackView.depth > 1
                onClicked: stackView.pop()
            }
        }
    }

    Components.PageModel {
        id: pageModel
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Item {
            width: parent.width
            height: parent.height

            GroupBox {
                anchors.fill: parent
                title: "Choose a page"

                Flow {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 50

                    Repeater {
                        model: pageModel

                        Button {
                            text: title
                            onClicked: stackView.push(Qt.resolvedUrl(page))
                        }
                    }
                }
            }
        }
    }
}
