#-------------------------------------------------
#
# Project created by QtCreator 2017-07-02T17:20:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PEW
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    pewwidget.cpp \
    worldinfo.cpp \
    timeline.cpp \
    Nodes/basenode.cpp \
    WidgetUtilities/styleloader.cpp \
    nodeview.cpp \
    Nodes/input.cpp \
    Nodes/output.cpp \
    Nodes/outnode.cpp \
    viewport.cpp \
    sceneobject.cpp \
    Model/model.cpp \
    Model/wireframemesh.cpp \
    Model/wireframemeshinstance.cpp \
    Model/simpletestmodel.cpp \
    CompulsorySceneObjects/camera.cpp \
    matrix.cpp \
    pointtransformations.cpp \
    Nodes/nodedata.cpp \
    Nodes/movable.cpp \
    Nodes/Data/intdata.cpp \
    Nodes/Data/floatdata.cpp \
    Nodes/Data/sceneobjectdata.cpp \
    WidgetUtilities/datastorageparser.cpp \
    WidgetUtilities/Parsers/colourfileparsing.cpp \
    nodedatamanager.cpp \
    UIManager/nodecolourmanager.cpp \
    Nodes/Data/booldata.cpp \
    Nodes/Data/vectordata.cpp \
    PropertiesWidgets/dataproperties.cpp \
    PropertiesWidgets/labeledinput.cpp \
    Nodes/datapin.cpp \
    Nodes/DataPinStates/datapinstate.cpp \
    Nodes/DataPinStates/readonlystate.cpp \
    Nodes/DataPinStates/writeonlystate.cpp \
    Nodes/DataPinStates/readwritestate.cpp \
    UIManager/arrowdrawingmanager.cpp \
    Nodes/nodeconnection.cpp \
    Nodes/Data/booldatawidget.cpp \
    Nodes/dataconnection.cpp \
    Nodes/externalvariable.cpp \
    Nodes/externalvariablefactory.cpp \
    Nodes/BasicNodes/testnode.cpp

HEADERS  += mainwindow.h \
    pewwidget.h \
    worldinfo.h \
    timeline.h \
    Nodes/basenode.h \
    WidgetUtilities/styleloader.h \
    nodeview.h \
    Nodes/input.h \
    Nodes/output.h \
    Nodes/outnode.h \
    viewport.h \
    sceneobject.h \
    tracinginfo.h \
    Model/model.h \
    Model/modelinfo.h \
    Model/wireframemesh.h \
    Model/wireframemeshinstance.h \
    Model/simpletestmodel.h \
    CompulsorySceneObjects/camera.h \
    matrix.h \
    pointtransformations.h \
    Nodes/nodedata.h \
    Nodes/movable.h \
    Nodes/Data/intdata.h \
    Nodes/Data/floatdata.h \
    Nodes/Data/sceneobjectdata.h \
    WidgetUtilities/datastorageparser.h \
    WidgetUtilities/Parsers/colourfileparsing.h \
    nodedatamanager.h \
    UIManager/nodecolourmanager.h \
    Nodes/Data/booldata.h \
    Nodes/Data/vectordata.h \
    PropertiesWidgets/dataproperties.h \
    PropertiesWidgets/labeledinput.h \
    Nodes/datapin.h \
    Nodes/DataPinStates/datapinstate.h \
    Nodes/DataPinStates/readonlystate.h \
    Nodes/pinproperties.h \
    Nodes/DataPinStates/writeonlystate.h \
    Nodes/DataPinStates/readwritestate.h \
    UIManager/arrowdrawingmanager.h \
    Nodes/nodeconnection.h \
    Nodes/Data/booldatawidget.h \
    Nodes/dataconnection.h \
    Nodes/externalvariable.h \
    Nodes/externalvariablefactory.h \
    Nodes/BasicNodes/testnode.h

FORMS    += mainwindow.ui
