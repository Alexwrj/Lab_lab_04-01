QT += charts

SOURCES += \
    main.cpp \
    model.cpp \
    chart.cpp \
    chartview.cpp

target.path = $$[QT_INSTALL_EXAMPLES]/charts/splinechart
INSTALLS += target

HEADERS += \
    model.h \
    ../dynamicspline/chart_копия.h \
    chart.h \
    chartview.h
