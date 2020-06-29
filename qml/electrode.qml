/**
@file electrode.qml

@brief Класс электрода для отображения сопротивления

@author Грозов Р.А.
**/

import QtQuick 2.0

Rectangle{
    id: electrode
    width: parent.width/11
    height: parent.width/11
    radius: parent.width/11
    color: "red"

    border.width: 1
    border.color: "black"

    // Таблица для отображения значений
    Rectangle{

        id:electr_info
        x: -(width - parent.width) / 2
        width: resistance.width + 4
        height: 15
        radius: 5
        anchors.top: parent.bottom
        color:"#AAAAAAAA"

        Text {
            x: 2
            id: resistance
            anchors.top: parent.top
            text: "255 kOm"
        }
    }

    // Название электрода
    Text {
        id: electrodeLabel
        anchors.centerIn: parent
        font.pixelSize: parent.height/3
        text: "electrode label"
    }

    // Состояние контактов
    states: [
        State {
            name: "bad_calibration"
            PropertyChanges {
                target: electrode;
                color: "orange";
            }
        },
        State {
            name: "normal_calibration"
            PropertyChanges {
                target: electrode;
                color: "yellow";
            }
        },
        State {
            name: "good_calibration"
            PropertyChanges {
                target: electrode;
                color: "green";
            }
        },
        State {
            name: "very_bad_calibration"
            PropertyChanges {
                target: electrode;
                color: "red"
            }
        },
        State {
            name: "replaced"
            PropertyChanges {
                target: electrode;
                color: "gray";
            }
        }
    ]

    // Установить название электрода
    function setText(text){
        electrodeLabel.text = text;
    }

    // Установить значения сопротивлений, изменить состояние
    function setState(resist, replaced)
    {
        resistance.text = resist + " kOm";

        //console.log("resist = ", resist);

        if (replaced)
            electrode.state = "replaced";
        else if(resist <= 10.0){
            electrode.state = "good_calibration";
        }
        else if (resist > 10.0 && resist <= 20.0) {
            electrode.state = "normal_calibration";
        }
        else if (resist > 20.0 && resist <= 30.0) {
            electrode.state = "bad_calibration";
        }
        else if (resist > 30.0) {
            electrode.state = "very_bad_calibration";
        }
    }


    // Установка позиции электрода по порядковому номеру
    function setPosition(positionId) {

        if(positionId == 3){ //"P3"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.horizontalCenterOffset = Qt.binding(function() {return - (Math.sqrt(3) * parent.width/12)});
            anchors.verticalCenter = parent.verticalCenter;
            anchors.verticalCenterOffset = Qt.binding(function() {return parent.height/12});
        }
        else if(positionId == 0){ //"Po7"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.horizontalCenterOffset = Qt.binding(function() {return - (Math.sqrt(3) * parent.width/5)});
            anchors.verticalCenter = parent.verticalCenter;
            anchors.verticalCenterOffset = Qt.binding(function() {return (parent.height/5)});
        }
        else if(positionId == 1){ //"O1"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.horizontalCenterOffset = Qt.binding(function() {return - parent.width/5});
            anchors.verticalCenter = parent.verticalCenter;
            anchors.verticalCenterOffset = Qt.binding(function() {return (Math.sqrt(3) * parent.height/5)});
        }
        else if(positionId == 4){ //"Pz"
            anchors.centerIn = parent;
        }
        else if(positionId == 2){ //"Oz"
            anchors.horizontalCenter = parent.horizontalCenter
            anchors.bottom = parent.bottom;
            anchors.bottomMargin = Qt.binding(function() {return parent.height/20});
        }
        else if(positionId == 6){ //"O2"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.horizontalCenterOffset = Qt.binding(function() {return parent.width/5});
            anchors.verticalCenter = parent.verticalCenter;
            anchors.verticalCenterOffset = Qt.binding(function() {return (Math.sqrt(3) * parent.height/5)});
        }
        else if(positionId == 7){ //"Po8"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.horizontalCenterOffset = Qt.binding(function() {return (Math.sqrt(3) * parent.width/5)});
            anchors.verticalCenter = parent.verticalCenter;
            anchors.verticalCenterOffset = Qt.binding(function() {return (parent.height/5)});
        }
        else if(positionId == 5){ //"P4"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.horizontalCenterOffset = Qt.binding(function() {return (Math.sqrt(3) * parent.width/12)});
            anchors.verticalCenter = parent.verticalCenter;
            anchors.verticalCenterOffset = Qt.binding(function() {return parent.height/12});
        }
        else if(positionId == 8){ //"REF"
            anchors.verticalCenter = parent.verticalCenter;
            anchors.right = parent.right;
            anchors.rightMargin = Qt.binding(function() {return - parent.width/30});
        }
        else if(positionId == 9){ //"GND"
            anchors.horizontalCenter = parent.horizontalCenter;
            anchors.top = parent.top;
            anchors.topMargin = Qt.binding(function() {return parent.height/20});
        }
    }
}
