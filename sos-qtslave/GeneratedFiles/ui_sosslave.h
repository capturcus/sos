/********************************************************************************
** Form generated from reading UI file 'sosslave.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOSSLAVE_H
#define UI_SOSSLAVE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SOSSlaveClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SOSSlaveClass)
    {
        if (SOSSlaveClass->objectName().isEmpty())
            SOSSlaveClass->setObjectName(QStringLiteral("SOSSlaveClass"));
        SOSSlaveClass->resize(432, 400);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SOSSlaveClass->sizePolicy().hasHeightForWidth());
        SOSSlaveClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(SOSSlaveClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);

        verticalLayout_2->addLayout(verticalLayout);

        SOSSlaveClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SOSSlaveClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 432, 21));
        SOSSlaveClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SOSSlaveClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SOSSlaveClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SOSSlaveClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SOSSlaveClass->setStatusBar(statusBar);

        retranslateUi(SOSSlaveClass);

        QMetaObject::connectSlotsByName(SOSSlaveClass);
    } // setupUi

    void retranslateUi(QMainWindow *SOSSlaveClass)
    {
        SOSSlaveClass->setWindowTitle(QApplication::translate("SOSSlaveClass", "SOSSlave", 0));
    } // retranslateUi

};

namespace Ui {
    class SOSSlaveClass: public Ui_SOSSlaveClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOSSLAVE_H
