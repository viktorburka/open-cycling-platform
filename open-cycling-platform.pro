QT += quick bluetooth

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        phonecommunication.cpp \
        settings.cpp \
        workoutcontroller.cpp

RESOURCES += qml.qrc

# Default rules for deployment.
linux {
    target.path = /home/pi/
}
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    phonecommunication.h \
    settings.h \
    workoutcontroller.h
