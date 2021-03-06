import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import com.crawl 1.0

Rectangle{
    id: root
    anchors.fill: parent
    color: "lightsteelblue"
    border.width: 1
    border.color: "gray"

    property int textInputWidth: 202
    property string  lineColor: "black"

    HandleMessage{
        id: messageManager
    }

    Column{
            id: rootColumn
            spacing: 17
            anchors.top: parent.top
            anchors.topMargin: 30
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 30


            Row{
                Rectangle{
                    width: rootColumn.width
                    height: 50
                    color: "lightsteelblue"
                    RowLayout{
                        anchors.centerIn: parent
                        ExclusiveGroup { id: exclusive }
                        RadioButton {
                            id: rd1
                            text: qsTr("作品集导出")
                            checked: true
                            exclusiveGroup: exclusive

                        }
                        RadioButton {
                            id:rd2
                            text: qsTr("书籍导出")
                            exclusiveGroup: exclusive

                        }
                        RadioButton {
                            id:rd3
                            text: qsTr("文章导出")
                            exclusiveGroup: exclusive

                        }
                    }
                }
            }

            Row{
                Rectangle{
                    color: lineColor
                    width: rootColumn.width
                    height: 1
                }
            }

            Row{

                Column{
                    spacing: 30
                    Row{
                        Text{
                            text:qsTr("作品集导出")
                            height: 20
                            font.family: "黑体"
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Row{
                        spacing: 5

                        Text{
                            text:qsTr("作品集URL：")
                            height: 20
                            //font.family: "黑体"
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter                          
                        }

                        Rectangle{
                            width: textInputWidth
                            height:30
                            border.color: "lightsteelblue"
                            border.width: 2
                            color: "lightgray"
                            clip: true
                            TextInput{
                                id: booksUrl
                                anchors.fill:parent
                                horizontalAlignment: TextInput.AlignHCenter
                                verticalAlignment: TextInput.AlignVCenter


                            }
                        }

                        Text{
                            text:qsTr("    作品目录匹配：")
                            height: 20
                            //font.family: "黑体"
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        Rectangle{
                            width: textInputWidth
                            height:30
                            border.color: "lightsteelblue"
                            border.width: 2
                            color: "lightgray"
                            clip: true
                            TextInput{
                                id: booksRule
                                anchors.fill:parent
                                horizontalAlignment: TextInput.AlignHCenter
                                verticalAlignment: TextInput.AlignVCenter


                            }
                        }
                    }
                }
            }

            Row{
                Rectangle{
                    color: lineColor
                    width: rootColumn.width
                    height: 1
                }
            }

            Row{

                Column{
                    spacing: 30
                    Row{
                        Text{
                            text:qsTr("书籍导出")
                            height: 20
                            font.family: "黑体"
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Row{
                        spacing: 5

                        Text{
                            text:qsTr("书籍URL：  ")
                            height: 20
                            //font.family: "黑体"
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        Rectangle{
                            width: textInputWidth
                            height:30
                            border.color: "lightsteelblue"
                            border.width: 2
                            color: "lightgray"
                            clip: true
                            TextInput{
                                id: bookUrl
                                anchors.fill:parent
                                horizontalAlignment: TextInput.AlignHCenter
                                verticalAlignment: TextInput.AlignVCenter
                            }
                        }

                        Text{
                            text:qsTr("    书籍目录匹配：")
                            height: 20
                            //font.family: "黑体"
                            font.pixelSize: 15
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        Rectangle{
                            width: textInputWidth
                            height:30
                            border.color: "lightsteelblue"
                            border.width: 2
                            color: "lightgray"
                            clip: true
                            TextInput{
                                id: bookRule
                                anchors.fill:parent
                                horizontalAlignment: TextInput.AlignHCenter
                                verticalAlignment: TextInput.AlignVCenter
                            }
                        }
                    }
                }
            }

            Row{
                Rectangle{
                    color: lineColor
                    width: rootColumn.width
                    height: 1
                }
            }

            Row{
                Column{
                    spacing: 30

                    Row{
                        Text{
                            text:qsTr("文章导出")
                            height: 20
                            font.family: "黑体"
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Row{
                        Column{
                            spacing: 10
                            Row{
                                spacing: 5

                                Text{
                                    text:qsTr("文章URL：  ")
                                    height: 20
                                    //font.family: "黑体"
                                    font.pixelSize: 15
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Rectangle{
                                    width: textInputWidth
                                    height:30
                                    border.color: "lightsteelblue"
                                    border.width: 2
                                    color: "lightgray"
                                    clip: true
                                    TextInput{
                                        id: articleUrl
                                        anchors.fill:parent
                                        horizontalAlignment: TextInput.AlignHCenter
                                        verticalAlignment: TextInput.AlignVCenter


                                    }
                                }

                                Text{
                                    text:qsTr("    书籍名称匹配：")
                                    height: 20
                                    //font.family: "黑体"
                                    font.pixelSize: 15
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Rectangle{
                                    width: textInputWidth
                                    height:30
                                    border.color: "lightsteelblue"
                                    border.width: 2
                                    color: "lightgray"
                                    clip: true
                                    TextInput{
                                        id: bookNameRule
                                        anchors.fill:parent
                                        horizontalAlignment: TextInput.AlignHCenter
                                        verticalAlignment: TextInput.AlignVCenter
                                    }
                                }
                            }

                            Row{
                                spacing: 5

                                Text{
                                    text:qsTr("作者匹配： ")
                                    height: 20
                                    //font.family: "黑体"
                                    font.pixelSize: 15
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Rectangle{
                                    width: textInputWidth
                                    height:30
                                    border.color: "lightsteelblue"
                                    border.width: 2
                                    color: "lightgray"
                                    clip: true
                                    TextInput{
                                        id: authorRule
                                        anchors.fill:parent
                                        horizontalAlignment: TextInput.AlignHCenter
                                        verticalAlignment: TextInput.AlignVCenter


                                    }
                                }

                                Text{
                                    text:qsTr("    正文匹配：    ")
                                    height: 20
                                    //font.family: "黑体"
                                    font.pixelSize: 15
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }

                                Rectangle{
                                    width: textInputWidth
                                    height:30
                                    border.color: "lightsteelblue"
                                    border.width: 2
                                    color: "lightgray"
                                    clip: true
                                    TextInput{
                                        id: contentRule
                                        anchors.fill:parent
                                        horizontalAlignment: TextInput.AlignHCenter
                                        verticalAlignment: TextInput.AlignVCenter
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Row{
                Rectangle{
                    color: lineColor
                    width: rootColumn.width
                    height: 1
                }
            }

            Row{
                Rectangle{
                    width: rootColumn.width
                    height: 50
                    color: "lightsteelblue"
                    RowLayout{
                        anchors.centerIn: parent
                        spacing: 30
                        CheckBox {
                            id: check1
                            text: qsTr("导出TXT文件")
                            checked: true
                        }

                        CheckBox {
                            id:check2
                            checked: true
                            text: qsTr("记录匹配规则")
                        }

                        CheckBox {
                            id:check3
                            text: qsTr("导入Sqlite中")
                        }

                    }
                }
            }

            Row{
                Rectangle{
                    width: rootColumn.width
                    height: 50
                    color: "lightsteelblue"
                    RowLayout{
                        anchors.right: parent.right

                        spacing: 30

                        Button{
                            width: 85
                            height: 30
                            style: ButtonStyle{
                               background: Rectangle{
                                   implicitHeight: parent.height
                                   implicitWidth: parent.width
                                   border.width: 1
                                   border.color: "darkGray"
                                   color: "lightgray"
                               }
                               label: Rectangle{
                                   color: "lightgray"
                                   Text{
                                       anchors.fill: parent
                                       text: qsTr("确 定")
                                       font.pixelSize: 15
                                       horizontalAlignment: Text.AlignHCenter
                                       verticalAlignment: Text.AlignVCenter
                                   }
                               }
                            }

                            onClicked: {
                                handleMessage()
                            }
                        }

                        Button{
                            width: 85
                            height: 30
                            style: ButtonStyle{
                               background: Rectangle{
                                   implicitHeight: parent.height
                                   implicitWidth: parent.width
                                   border.width: 1
                                   border.color: "darkGray"
                                   color: "lightgray"


                               }
                               label: Rectangle{
                                  color: "lightgray"
                                  Text{
                                      anchors.fill: parent
                                      text: qsTr("取 消")
                                      font.pixelSize: 15
                                      horizontalAlignment: Text.AlignHCenter
                                      verticalAlignment: Text.AlignVCenter
                                  }
                               }
                            }

                            onClicked: {
                                Qt.quit()
                            }
                        }
                    }
                }
            }
    }


    function  handleMessage()
    {
        console.log("handleMessage");
        if (rd1.checked)
        {
            console.log("handleMessage1");
            messageManager.setMessage(0, booksUrl.text + "$" + booksRule.text + "$" +
                                      bookRule.text + "$" + bookNameRule.text + "$" + authorRule.text + "$" + contentRule.text,
                                      check1.checked, check2.checked, check3.checked);
        }
        else if(rd2.checked)
        {
            console.log("handleMessage2");
            messageManager.setMessage(1, bookUrl.text + "$" + bookRule.text + "$" +
                                      bookNameRule.text + "$" + authorRule.text + "$" + contentRule.tetx,
                                      check1.checked, check2.checked, check3.checked);
        }
        else if(rd3.checked)
        {
            console.log("handleMessage3");
            messageManager.setMessage(2, articleUrl.text + "$" + bookNameRule.text + "$" + authorRule.text + "$" + contentRule.tetx,
                                      check1.checked, check2.checked, check3.checked);
        }
    }

    MouseArea {
        id: dragRegion
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 610
        anchors.left: parent.left
        anchors.right: parent.right
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x,mouse.y)
            }
        onPositionChanged: {
        //鼠标偏移量
        var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
        //如果mainwindow继承自QWidget,用setPos
        mainwindow.setX(mainwindow.x+delta.x)
        mainwindow.setY(mainwindow.y+delta.y)
        }
    }

}
