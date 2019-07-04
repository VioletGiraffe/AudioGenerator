QT = core gui widgets charts

TARGET = WaveformGenerator
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
	mainwindow.cpp \
	sourcecodedialog/generatedsourcecodedialog.cpp \
	waveformgenerator.cpp \
	generators/sinegenerator.cpp \
	generators/squaregenerator.cpp \
	generators/trianglegenerator.cpp

HEADERS  += mainwindow.h \
	sourcecodedialog/generatedsourcecodedialog.h \
	waveformgenerator.h \
	generators/sinegenerator.h \
	generators/squaregenerator.h \
	generators/trianglegenerator.h

FORMS += mainwindow.ui \
	sourcecodedialog/generatedsourcecodedialog.ui
