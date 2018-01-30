QT       += widgets

QMAKE_CXXFLAGS += -Wno-reorder


TARGET = video_compress
TEMPLATE = app


SOURCES +=  main.cpp \
            ../common/commonFunctions.cpp \
            ../common/VideoCapturePlusQt.cpp \
            ../common//VideoWriterPlusQt.cpp \
            ../common/Region.cpp \
            ../common/RegionCollection.cpp \
            ../common/ImageLabel.cpp \
            MainWindow.cpp

HEADERS +=  \
            ../common/commonFunctions.h \
            ../common/VideoCapturePlusQt.h \
            ../common/VideoWriterPlusQt.h \
            ../common/Region.h \
            ../common/RegionCollection.h \
            ../common/VideoWriterPlusQt.h \
            ../common/ImageLabel.h \
            MainWindow.h

FORMS +=    mainwindow.ui

INCLUDEPATH +=  "C:/Users/m/Box Sync/Sickle Cell Work - Shared/Red Blood Cell Tracking/Code/Qt/common/build/include"

LIBS += -L"C:/Users/m/Box Sync/Sickle Cell Work - Shared/Red Blood Cell Tracking/Code/Qt/common/build/x86/mingw/lib" \
        -lopencv_highgui310 \
        -lopencv_core310 \
        -lopencv_imgproc310 \
        -lopencv_features2d310 \
        -lopencv_imgcodecs310 \
        -lopencv_videoio310 \
        -lopencv_video310
