/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *warehouseButton;
    QPushButton *requestsButton;
    QPushButton *reportsButton;
    QPushButton *usersButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f0f5ff;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");

        verticalLayout->addWidget(stackedWidget);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        warehouseButton = new QPushButton(groupBox);
        warehouseButton->setObjectName("warehouseButton");
        warehouseButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1976d2;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 24px;\n"
"    border-radius: 6px;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1565c0;\n"
"}"));

        horizontalLayout->addWidget(warehouseButton);

        requestsButton = new QPushButton(groupBox);
        requestsButton->setObjectName("requestsButton");
        requestsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1976d2;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 24px;\n"
"    border-radius: 6px;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1565c0;\n"
"}"));

        horizontalLayout->addWidget(requestsButton);

        reportsButton = new QPushButton(groupBox);
        reportsButton->setObjectName("reportsButton");
        reportsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1976d2;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 24px;\n"
"    border-radius: 6px;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1565c0;\n"
"}"));

        horizontalLayout->addWidget(reportsButton);

        usersButton = new QPushButton(groupBox);
        usersButton->setObjectName("usersButton");
        usersButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1976d2;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 24px;\n"
"    border-radius: 6px;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1565c0;\n"
"}"));

        horizontalLayout->addWidget(usersButton);

        settingsButton = new QPushButton(groupBox);
        settingsButton->setObjectName("settingsButton");
        settingsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1976d2;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 24px;\n"
"    border-radius: 6px;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #1565c0;\n"
"}"));

        horizontalLayout->addWidget(settingsButton);

        exitButton = new QPushButton(groupBox);
        exitButton->setObjectName("exitButton");
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #d32f2f;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px 24px;\n"
"    border-radius: 6px;\n"
"    font-size: 12pt;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #c62828;\n"
"}"));

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addWidget(groupBox);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\273\320\260\320\264\321\201\320\272\320\260\321\217 \321\201\320\270\321\201\321\202\320\265\320\274\320\260 HK", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\221\321\213\321\201\321\202\321\200\321\213\320\271 \320\264\320\276\321\201\321\202\321\203\320\277", nullptr));
        warehouseButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\246 \320\241\320\272\320\273\320\260\320\264", nullptr));
        requestsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\213 \320\227\320\260\321\217\320\262\320\272\320\270", nullptr));
        reportsButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 \320\236\321\202\321\207\320\265\321\202\321\213", nullptr));
        usersButton->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245 \320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "\342\232\231\357\270\217 \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "\360\237\232\252 \320\222\321\213\321\205\320\276\320\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
