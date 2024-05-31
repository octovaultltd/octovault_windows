import QtQuick 2.12
import QtLocation 5.12
import QtPositioning 5.12

MapQuickItem
{
    id: marker
    anchorPoint.x: marker.width / 4
    anchorPoint.y: marker.height
    sourceItem: Image{
        id: icon
        source: "qrc:/img/images/icon_marker.png"
        sourceSize.width: 50
        sourceSize.height: 50
    }
}
