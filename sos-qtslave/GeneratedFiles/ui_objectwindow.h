/********************************************************************************
** Form generated from reading UI file 'objectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTWINDOW_H
#define UI_OBJECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ObjectWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTreeView *treeView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ObjectWindow)
    {
        if (ObjectWindow->objectName().isEmpty())
            ObjectWindow->setObjectName(QStringLiteral("ObjectWindow"));
        ObjectWindow->resize(466, 460);
        centralWidget = new QWidget(ObjectWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));

        gridLayout_2->addWidget(treeView, 1, 0, 1, 1);

        ObjectWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ObjectWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 466, 21));
        ObjectWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ObjectWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ObjectWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ObjectWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ObjectWindow->setStatusBar(statusBar);

        retranslateUi(ObjectWindow);

        QMetaObject::connectSlotsByName(ObjectWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ObjectWindow)
    {
        ObjectWindow->setWindowTitle(QApplication::translate("ObjectWindow", "ObjectWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class ObjectWindow: public Ui_ObjectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTWINDOW_H
