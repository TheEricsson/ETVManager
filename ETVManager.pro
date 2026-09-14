QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    agendadialog.cpp \
    agendaitemsettings.cpp \
    agendaoptionsdialog.cpp \
    agendasettings.cpp \
    agendatab.cpp \
    agendatablecontextmenu.cpp \
    agendawizard.cpp \
    connectionwidget.cpp \
    databaseimpl.cpp \
    decissionitemsettings.cpp \
    decissionlibraryeditdialog.cpp \
    decissionlibrarytab.cpp \
    editadvisersdialog.cpp \
    generatorWidget.cpp \
    global.cpp \
    main.cpp \
    mainwindow.cpp \
    orderitemsettings.cpp \
    ordertab.cpp \
    patterneditor.cpp \
    patterneditorreport.cpp \
    patterneditorreportitemsettings.cpp \
    patternitemsettings.cpp \
    presencechangedialog.cpp \
    propertyMainView.cpp \
    propertylistdialog.cpp \
    propertysettings.cpp \
    propertytab.cpp \
    protocolDecissionGenerator.cpp \
    qsqlconnectiondialog.cpp \
    qsqlquerymodelImpl.cpp \
    qsqlquerymodelagendaview.cpp \
    qsqlquerymodelpropertyview.cpp \
    qsqlquerymodelprotocolgeneratorview.cpp \
    qstandarditemmodelpropertyoverview.cpp \
    stringreplacer.cpp \
    systemsettings.cpp \
    votingdialog.cpp \
    wizarddialogbox.cpp

HEADERS += \
    PatternItemSettings.h \
    QSqlQueryModelImpl.h \
    agendadialog.h \
    agendaitemsettings.h \
    agendaoptionsdialog.h \
    agendasettings.h \
    agendatab.h \
    agendatablecontextmenu.h \
    agendawizard.h \
    connectionwidget.h \
    databaseimpl.h \
    decissionitemsettings.h \
    decissionlibraryeditdialog.h \
    decissionlibrarytab.h \
    editadvisersdialog.h \
    generatorWidget.h \
    global.h \
    mainwindow.h \
    orderitemsettings.h \
    ordertab.h \
    patterneditor.h \
    patterneditorreport.h \
    patterneditorreportitemsettings.h \
    presencechangedialog.h \
    propertyMainView.h \
    propertylistdialog.h \
    propertysettings.h \
    propertytab.h \
    protocolDecissionGenerator.h \
    qsqlconnectiondialog.h \
    qsqlquerymodelagendaview.h \
    qsqlquerymodelpropertyview.h \
    qsqlquerymodelprotocolgeneratorview.h \
    qstandarditemmodelpropertyoverview.h \
    stringreplacer.h \
    systemsettings.h \
    votingdialog.h \
    wizarddialogbox.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32 {
  Release:DESTDIR = ../../../bin/win/release
  Debug:DESTDIR = ../../../bin/win/debug
} else {
  Release:DESTDIR = ../../../bin/linux/release
  Debug:DESTDIR = ../../../bin/linux/debug
}

FORMS += \
    agendadialog.ui \
    agendaitemcontextmenu.ui \
    agendaitemsettings.ui \
    agendaoptionsdialog.ui \
    agendasettings.ui \
    agendatab.ui \
    decissionitemsettings.ui \
    decissionlibraryeditdialog.ui \
    decissionlibrarytab.ui \
    editadvisersdialog.ui \
    generatorwidget.ui \
    mainwindow.ui \
    orderitemsettings.ui \
    ordertab.ui \
    patterneditor.ui \
    patterneditorreport.ui \
    patterneditorreportitemsettings.ui \
    patternitemsettings.ui \
    presencechangedialog.ui \
    propertymainview.ui \
    propertyoverview.ui \
    propertysettings.ui \
    propertytab.ui \
    protocolDecissionGenerator.ui \
    qsqlconnectiondialog.ui \
    simpleListDialog.ui \
    systemsettings.ui \
    votingdialog.ui

RESOURCES += \
    resources.qrc
