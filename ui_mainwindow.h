/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *Graphs;
    QGroupBox *Controls_group;
    QGroupBox *COM_group;
    QComboBox *com_combobox;
    QPushButton *com_button;
    QLabel *comstate_label;
    QLabel *echo_label;
    QPushButton *clearGraph_button;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1049, 671);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        Graphs = new QGroupBox(centralWidget);
        Graphs->setObjectName(QString::fromUtf8("Graphs"));
        Graphs->setGeometry(QRect(360, 10, 501, 391));
        sizePolicy1.setHeightForWidth(Graphs->sizePolicy().hasHeightForWidth());
        Graphs->setSizePolicy(sizePolicy1);
        Controls_group = new QGroupBox(centralWidget);
        Controls_group->setObjectName(QString::fromUtf8("Controls_group"));
        Controls_group->setGeometry(QRect(10, 10, 341, 421));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Controls_group->sizePolicy().hasHeightForWidth());
        Controls_group->setSizePolicy(sizePolicy2);
        Controls_group->setMinimumSize(QSize(341, 421));
        COM_group = new QGroupBox(Controls_group);
        COM_group->setObjectName(QString::fromUtf8("COM_group"));
        COM_group->setGeometry(QRect(10, 20, 191, 101));
        sizePolicy.setHeightForWidth(COM_group->sizePolicy().hasHeightForWidth());
        COM_group->setSizePolicy(sizePolicy);
        com_combobox = new QComboBox(COM_group);
        com_combobox->setObjectName(QString::fromUtf8("com_combobox"));
        com_combobox->setGeometry(QRect(10, 30, 69, 22));
        com_button = new QPushButton(COM_group);
        com_button->setObjectName(QString::fromUtf8("com_button"));
        com_button->setGeometry(QRect(100, 30, 75, 23));
        comstate_label = new QLabel(COM_group);
        comstate_label->setObjectName(QString::fromUtf8("comstate_label"));
        comstate_label->setGeometry(QRect(60, 70, 81, 20));
        comstate_label->setAlignment(Qt::AlignCenter);
        echo_label = new QLabel(Controls_group);
        echo_label->setObjectName(QString::fromUtf8("echo_label"));
        echo_label->setGeometry(QRect(220, 30, 101, 101));
        clearGraph_button = new QPushButton(centralWidget);
        clearGraph_button->setObjectName(QString::fromUtf8("clearGraph_button"));
        clearGraph_button->setGeometry(QRect(370, 410, 481, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1049, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Graphs->setTitle(QCoreApplication::translate("MainWindow", "Graphs", nullptr));
        Controls_group->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        COM_group->setTitle(QCoreApplication::translate("MainWindow", "COM connection", nullptr));
        com_button->setText(QCoreApplication::translate("MainWindow", "Open/Close", nullptr));
        comstate_label->setText(QCoreApplication::translate("MainWindow", "COM port state", nullptr));
        echo_label->setText(QCoreApplication::translate("MainWindow", "Echo", nullptr));
        clearGraph_button->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
