# sae_VoitureAutonome

git clone https://github.com/victbar/sae_VoitureAutonome


modifier le fichier pro avec

```cpp


SOURCES += \
    WidgetVoiture.cpp \
    capteurtension.cpp \
    comportement.cpp \
    correcteur.cpp \
    correcteurproportionnel.cpp \
    drivermoteur.cpp \
    main.cpp \
    mainwindow.cpp \
    mastrategie.cpp \
    materiel.cpp \
    materielsimule.cpp \
    moyennedroitegauche.cpp \
    qi2cdevice.cpp \
    reculer.cpp \
    servo.cpp \
    stop.cpp \
    strategie.cpp \
    suivrebord.cpp \
    tcpclient.cpp \
    tcpserveur.cpp \
    widgetlidar.cpp

HEADERS += \
    WidgetVoiture.h \
    capteurtension.h \
    comportement.h \
    correcteur.h \
    correcteurproportionnel.h \
    drivermoteur.h \
    mainwindow.h \
    mastrategie.h \
    materiel.h \
    materielsimule.h \
    moyennedroitegauche.h \
    qi2cdevice.h \
    reculer.h \
    servo.h \
    stop.h \
    strategie.h \
    suivrebord.h \
    tcpclient.h \
    tcpserveur.h \
    widgetlidar.h

QT += core network
QT += network

```
```cpp

unix:!macx: LIBS += -L/opt/electronique/pi4TpInfo/sysroot/rplidar/rplidar_sdk/output/Linux/Release/ -lsl_lidar_sdk

INCLUDEPATH += /opt/electronique/pi4TpInfo/sysroot/rplidar/rplidar_sdk/sdk/include
INCLUDEPATH += /opt/electronique/pi4TpInfo/sysroot/rplidar/rplidar_sdk/sdk/src
DEPENDPATH += /opt/electronique/pi4TpInfo/sysroot/rplidar/rplidar_sdk/sdk/include

unix:!macx: PRE_TARGETDEPS += /opt/electronique/pi4TpInfo/sysroot/rplidar/rplidar_sdk/output/Linux/Release/libsl_lidar_sdk.a


```
