import QtQuick 2.3
import QtQuick.Layouts 1.1
import com.crawl 1.0

Rectangle{
    id: root
    width: 900
    height: 700
    radius: 4
    opacity: 0.9
    color: "darkgrey"

    CrawlSingleHtml{
        id:crawl
    }

    Text{
        id: text
        anchors.fill: parent
        font.pixelSize: 20
        font.family: "黑体"
        text: "123"
    }

}
