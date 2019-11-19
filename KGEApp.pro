QT += quick core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += std=c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/forms/ComponentsForm.cpp \
    src/forms/HierarchyForm.cpp \
    src/models/TreeModelTest.cpp \
    src/models/TreeModel.cpp \
    src/TreeView.cpp \
    src/TeeNode.cpp \
    src/TreeItem.cpp \
    src/MainWindow.cpp \
    src/main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += \
        $$PWD/include \
        $$PWD/include/models \
        $$PWD/include/forms \
        $$PWD/ui

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/forms/ComponentsForm.h \
    include/forms/HierarchyForm.h \
    include/models/TreeModelTest.h \
    include/models/TreeModel.h \
    include/models/TreeNode.h \
    include/TreeView.h \
    include/MainWindow.h \
    include/TreeItem.h

FORMS += \
    ui/componentsform.ui \
    ui/hierarchyform.ui \
    ui/mainwindow.ui

DISTFILES += \
    qml/main.qml \
    qtquickcontrols2.conf
