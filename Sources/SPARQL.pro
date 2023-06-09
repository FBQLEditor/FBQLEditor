QT       += core gui network script webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DiagramItems/DiagramArrow/diagramarrow.cpp \
    DiagramItems/DiagramBlocks/AtomBlock/atomblocksettings.cpp \
    DiagramItems/DiagramBlocks/AtomBlock/diagramitematom.cpp \
    DiagramItems/DiagramBlocks/BasicBlock/basicblocksettings.cpp \
    DiagramItems/DiagramBlocks/BasicBlock/basicblockwindow.cpp \
    DiagramItems/DiagramBlocks/BasicBlock/diagramitembasic.cpp \
    DiagramItems/DiagramBlocks/CompositeBlock/compositeblocksettings.cpp \
    DiagramItems/DiagramBlocks/CompositeBlock/compositeblockwindow.cpp \
    DiagramItems/DiagramBlocks/CompositeBlock/diagramitemcomposite.cpp \
    DiagramItems/DiagramBlocks/IOBlock/diagramitemio.cpp \
    DiagramItems/DiagramBlocks/IOBlock/ioblocksettings.cpp \
    DiagramItems/DiagramBlocks/SparqlBlock/diagramitemsparql.cpp \
    DiagramItems/DiagramBlocks/SparqlBlock/sparqlblocksettings.cpp \
    DiagramItems/DiagramBlocks/SparqlBlock/sparqlblockwindow.cpp \
    DiagramItems/DiagramBlocks/blockslibrary.cpp \
    DiagramItems/DiagramExecutor/apijs.cpp \
    DiagramItems/DiagramExecutor/blocksexec.cpp \
    DiagramItems/DiagramExecutor/diagramexecutor.cpp \
    DiagramItems/DiagramExecutor/snetwork.cpp \
    DiagramItems/DiagramItem/diagramitem.cpp \
    DiagramItems/DiagramItemSettings/diagramitemsettings.cpp \
    DiagramItems/DiagramScene/diagramscene.cpp \
    DiagramItems/FusekiServerWindow/downloader.cpp \
    DiagramItems/FusekiServerWindow/fusekiserversetting.cpp \
    DiagramItems/DiagramWindows/projectwindow.cpp \
    DiagramItems/DiagramWindows/projectwindowsettings.cpp \
    DiagramItems/FusekiServerWindow/myprocess.cpp \
    MainForm/mainpage.cpp \
    SWidgets/SGraphicsView/sgraphicsview.cpp \
    SWidgets/SOpenProcessor/sopensaveprocessor.cpp \
    SWidgets/STabWidget/stabwidget.cpp \
    SWidgets/SToolBar/stoolbar.cpp \
    SWidgets/SToolBox/stoolbox.cpp \
    SWidgets/swidget.cpp \
    main.cpp \
    MainForm/mainwindow.cpp \
    SWidgets/SMenuBar/smenubar.cpp

HEADERS += \
    DiagramItems/DiagramArrow/diagramarrow.h \
    DiagramItems/DiagramBlocks/AtomBlock/atomblocksettings.h \
    DiagramItems/DiagramBlocks/AtomBlock/diagramitematom.h \
    DiagramItems/DiagramBlocks/BasicBlock/basicblocksettings.h \
    DiagramItems/DiagramBlocks/BasicBlock/basicblockwindow.h \
    DiagramItems/DiagramBlocks/BasicBlock/diagramitembasic.h \
    DiagramItems/DiagramBlocks/CompositeBlock/compositeblocksettings.h \
    DiagramItems/DiagramBlocks/CompositeBlock/compositeblockwindow.h \
    DiagramItems/DiagramBlocks/CompositeBlock/diagramitemcomposite.h \
    DiagramItems/DiagramBlocks/IOBlock/diagramitemio.h \
    DiagramItems/DiagramBlocks/IOBlock/ioblocksettings.h \
    DiagramItems/DiagramBlocks/SparqlBlock/diagramitemsparql.h \
    DiagramItems/DiagramBlocks/SparqlBlock/sparqlblocksettings.h \
    DiagramItems/DiagramBlocks/SparqlBlock/sparqlblockwindow.h \
    DiagramItems/DiagramBlocks/blockslibrary.h \
    DiagramItems/DiagramExecutor/apijs.h \
    DiagramItems/DiagramExecutor/blocksexec.h \
    DiagramItems/DiagramExecutor/diagramexecutor.h \
    DiagramItems/DiagramExecutor/snetwork.h \
    DiagramItems/DiagramItem/diagramitem.h \
    DiagramItems/DiagramItemSettings/diagramitemsettings.h \
    DiagramItems/DiagramScene/diagramscene.h \
    DiagramItems/FusekiServerWindow/downloader.h \
    DiagramItems/FusekiServerWindow/fusekiserversetting.h \
    DiagramItems/DiagramWindows/projectwindow.h \
    DiagramItems/DiagramWindows/projectwindowsettings.h \
    DiagramItems/FusekiServerWindow/myprocess.h \
    MainForm/mainpage.h \
    MainForm/mainsettings.h \
    MainForm/mainwindow.h \
    SWidgets/SGraphicsView/sgraphicsview.h \
    SWidgets/SOpenProcessor/sopensaveprocessor.h \
    SWidgets/STabWidget/stabwidget.h \
    SWidgets/SToolBar/stoolbar.h \
    SWidgets/SMenuBar/smenubar.h \
    SWidgets/SToolBox/stoolbox.h \
    SWidgets/swidget.h

FORMS += \
    MainForm/mainwindow.ui

INCLUDEPATH += \
    MainForm \
    SWidgets \
    SWidgets/SToolBar \
    SWidgets/SMenuBar \
    SWidgets/SToolBox \
    SWidgets/STabWidget \
    SWidgets/SGraphicsView \
    SWidgets/SOpenProcessor \
    DiagramItems/DiagramWindows \
    DiagramItems/DiagramItem \
    DiagramItems/DiagramArrow \
    DiagramItems/DiagramScene \
    DiagramItems/DiagramItemSettings \
    DiagramItems/DiagramBlocks/BasicBlock \
    DiagramItems/DiagramBlocks/CompositeBlock \
    DiagramItems/DiagramBlocks/SparqlBlock \
    DiagramItems/DiagramBlocks/AtomBlock \
    DiagramItems/DiagramBlocks/IOBlock \
    DiagramItems/DiagramBlocks \
    DiagramItems/DiagramExecutor \
    DiagramItems/FusekiServerWindow \
    "C:\Program Files\Graphviz\include" \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    sources.qrc

LIBS += -L"C:\Program Files\Graphviz\lib" -lgvc -lcgraph
RC_FILE = appIcon.rc
