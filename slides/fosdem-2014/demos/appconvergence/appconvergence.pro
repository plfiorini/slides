QT += qml quick
TARGET = appconvergence
!android: !ios: !blackberry: qtHaveModule(widgets): QT += widgets
CONFIG += c++11

include(src/src.pri)

SOURCES += \
    qtquickcontrolsapplication.h

OTHER_FILES += \
    main.qml \
    content/ProgressBarPage.qml \
    content/MainView.qml \
    content/ButtonPage.qml \
    content/AndroidDelegate.qml \
    content/ListPage.qml \
    content/TabBarPage.qml \
    content/TextInputPage.qml \
    content/components/SwipeArea.qml \
    content/components/PageModel.qml \
    content/main.qml \
    content/+tablet/MainView.qml \
    content/+tablet/main.qml \
    content/SliderPage.qml \
    content/+touch/ProgressBarPage.qml \
    content/+touch/MainView.qml \
    content/+touch/TabBarPage.qml \
    content/+touch/ListPage.qml \
    content/+touch/ButtonPage.qml \
    content/+touch/AndroidDelegate.qml \
    content/+touch/SliderPage.qml \
    content/+touch/TextInputPage.qml \
    content/+phone/MainView.qml \
    content/+phone/main.qml \
