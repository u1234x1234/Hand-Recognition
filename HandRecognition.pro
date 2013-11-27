TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /home/12341234/Downloads/OpenNI-Bin-Dev-Linux-x64-v1.5.4.0/Include
LIBS += -lopencv_video -lopencv_photo -lopencv_ml -lopencv_contrib -lopencv_objdetect -lopencv_imgproc -lopencv_highgui -lopencv_core -lGL -lglut -lGLU -lGLEW -lOpenNI
LIBS += -lX11 -lXtst

SOURCES += main.cpp \
    OpenNIContext.cpp \
    HandDetector.cpp \
    SVMHandDetector.cpp

HEADERS += \
    OpenNIContext.h \
    HandDetector.h \
    SVMHandDetector.h

