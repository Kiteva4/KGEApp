QT += quick core gui quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += std=c++17

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    ComponentsForm.cpp \
    HierarchyForm.cpp \
    TeeNode.cpp \
    TreeModelTest.cpp \
    TreeView.cpp \
    src/MainWindow.cpp \
    src/TreeItem.cpp \
    src/TreeModel.cpp \
    src/main.cpp \

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/include

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \ \
    ComponentsForm.h \
    HierarchyForm.h \
    TreeModelTest.h \
    TreeNode.h \
    TreeView.h \
    include/MainWindow.h \
    include/TreeItem.h \
    include/TreeModel.h

FORMS += \
    componentsform.ui \
    hierarchyform.ui \
    mainwindow.ui
