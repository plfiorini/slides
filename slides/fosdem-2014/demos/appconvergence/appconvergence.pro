QT += qml quick
TARGET = appconvergence
!android: !ios: !blackberry: qtHaveModule(widgets): QT += widgets

include(src/src.pri)

SOURCES += \
    qtquickcontrolsapplication.h

OTHER_FILES += \
    main.qml \
    content/AndroidDelegate.qml \
    content/ButtonPage.qml \
    content/ListPage.qml \
    content/ProgressBarPage.qml \
    content/SliderPage.qml \
    content/TabBarPage.qml \
    content/TextInputPage.qml

RESOURCES += \
    resources.qrc
