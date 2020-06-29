/**
@file eegDiagram.qml

@brief Класс диаграммы электродов ээг

@author Грозов Р.А.
**/

import QtQuick 2.0
Rectangle{
    id:root

    Rectangle {
        id: nose

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {

            anchors.top: parent.top
            height: 100
            width: 2

            border.color: "black"
            border.width: 1

            transform: Rotation{ angle: 45 }
        }
        Rectangle {
            height: 100
            width: 2

            border.color: "black"
            border.width: 1

            transform: Rotation{ angle: - 45 }
        }
    }

    Rectangle{
        id: left_ear

        border.color: "black"
        border.width: 2

        width: 100
        height: 100
        radius: 100

        anchors.left: parent.left
        anchors.verticalCenter: eegDiagram.verticalCenter


    }
    Rectangle  {
        id: right_ear

        border.color: "black"
        border.width: 2

        width: 100
        height: 100
        radius: 100

        anchors.right: parent.right
        anchors.verticalCenter: eegDiagram.verticalCenter

    }


    Rectangle {
        id: eegDiagram

        y: 20
        height: (parent.height - 40)
        width: (parent.width - 60)

        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30

        border.color: "black"
        border.width: 2
        radius: width * 0.5

        function addElectode(text, id)
        {
            var component = Qt.createComponent("electrode.qml");
            var electrode = component.createObject(eegDiagram);

            if(electrode !== null)
            {
                electrode.setText(text);
                electrode.setPosition(id);
            }
        }

        function setElectrodeState(id, resist, replaced)
        {
            var electrode = children[id];
            electrode.setState(resist, replaced);
        }
    }

    function addElectode(text, id) {
        eegDiagram.addElectode(text,id);
    }

    function setElectrodeState(id, resist, replaced){
        eegDiagram.setElectrodeState(id, resist, replaced);
    }
}


