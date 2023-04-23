QT += quick dbus
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    ./src \
    ./src/common \
    ./src/controller \
    ./src/model

HEADERS += \
    src/appengine.h \
    src/common/appdefines.h \
    src/common/loghelper.h \
    src/controller/d_buscontroller.h \
    src/controller/screencontroller.h \
    src/controller/translatorcontroller.h \
    src/model/d_busmodel.h \
    src/model/jsonmodel.h \
    src/model/screenmodel.h \
    src/model/translatormodel.h

SOURCES += \
    src/appengine.cpp \
    src/controller/d_buscontroller.cpp \
    src/controller/screencontroller.cpp \
    src/controller/translatorcontroller.cpp \
    src/main.cpp \
    src/model/d_busmodel.cpp \
    src/model/jsonmodel.cpp \
    src/model/screenmodel.cpp \
    src/model/translatormodel.cpp

RESOURCES += \
    images.qrc \
    localization.qrc \
    qml.qrc

TRANSLATIONS += \
    localization/AppLanguage_en.ts \
    localization/AppLanguage_vi.ts

DBUS_ADAPTORS += ../../QtMock/temp/d_busModel.xml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
