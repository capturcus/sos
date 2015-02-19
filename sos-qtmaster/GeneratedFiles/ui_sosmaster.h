/********************************************************************************
** Form generated from reading UI file 'sosmaster.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOSMASTER_H
#define UI_SOSMASTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SOSMasterClass
{
public:
    QAction *actionConnect_to_server;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout;
    QLabel *luaOutput;
    QLineEdit *luaInput;
    QLineEdit *serverAddress;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SOSMasterClass)
    {
        if (SOSMasterClass->objectName().isEmpty())
            SOSMasterClass->setObjectName(QStringLiteral("SOSMasterClass"));
        SOSMasterClass->resize(628, 616);
        actionConnect_to_server = new QAction(SOSMasterClass);
        actionConnect_to_server->setObjectName(QStringLiteral("actionConnect_to_server"));
        centralWidget = new QWidget(SOSMasterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        luaOutput = new QLabel(centralWidget);
        luaOutput->setObjectName(QStringLiteral("luaOutput"));
        luaOutput->setEnabled(true);
        luaOutput->setLayoutDirection(Qt::LeftToRight);
        luaOutput->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        luaOutput->setWordWrap(true);

        verticalLayout->addWidget(luaOutput);

        luaInput = new QLineEdit(centralWidget);
        luaInput->setObjectName(QStringLiteral("luaInput"));

        verticalLayout->addWidget(luaInput);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        serverAddress = new QLineEdit(centralWidget);
        serverAddress->setObjectName(QStringLiteral("serverAddress"));

        gridLayout->addWidget(serverAddress, 1, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        SOSMasterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SOSMasterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 628, 21));
        SOSMasterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SOSMasterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SOSMasterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SOSMasterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SOSMasterClass->setStatusBar(statusBar);

        retranslateUi(SOSMasterClass);

        QMetaObject::connectSlotsByName(SOSMasterClass);
    } // setupUi

    void retranslateUi(QMainWindow *SOSMasterClass)
    {
        SOSMasterClass->setWindowTitle(QApplication::translate("SOSMasterClass", "SOSMaster", 0));
        actionConnect_to_server->setText(QApplication::translate("SOSMasterClass", "Connect to server...", 0));
        luaOutput->setText(QString());
        label->setText(QApplication::translate("SOSMasterClass", "Type in the server address and press ENTER:", 0));
    } // retranslateUi

};

namespace Ui {
    class SOSMasterClass: public Ui_SOSMasterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOSMASTER_H
