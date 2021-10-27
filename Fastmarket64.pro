QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    funcoes_globais.cpp \
    main.cpp \
    mainwindow.cpp \
    window_editar_produto_venda.cpp \
    window_gerenciarestoque.cpp \
    window_gerenciarusuarios.cpp \
    window_gerenciarvenda.cpp \
    window_login.cpp \
    window_novavenda.cpp \
    window_pagamento.cpp \
    window_pesquisavenda.cpp

HEADERS += \
    connect.h \
    funcoes_globais.h \
    mainwindow.h \
    variaveis_globais.h \
    window_editar_produto_venda.h \
    window_gerenciarestoque.h \
    window_gerenciarusuarios.h \
    window_gerenciarvenda.h \
    window_login.h \
    window_novavenda.h \
    window_pagamento.h \
    window_pesquisavenda.h

FORMS += \
    mainwindow.ui \
    window_editar_produto_venda.ui \
    window_gerenciarestoque.ui \
    window_gerenciarusuarios.ui \
    window_gerenciarvenda.ui \
    window_login.ui \
    window_novavenda.ui \
    window_pagamento.ui \
    window_pesquisavenda.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recurssos.qrc

DISTFILES += \
    imagens/pagamento.png

RC_ICONS = icon.ico
