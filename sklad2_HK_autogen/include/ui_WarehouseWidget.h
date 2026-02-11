/********************************************************************************
** Form generated from reading UI file 'WarehouseWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAREHOUSEWIDGET_H
#define UI_WAREHOUSEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WarehouseWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *productsTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *searchEdit;
    QComboBox *filterCombo;
    QSpacerItem *horizontalSpacer;
    QTableView *productsTable;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addProductButton;
    QPushButton *editProductButton;
    QPushButton *deleteProductButton;
    QPushButton *generateQRButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *containersTab;
    QVBoxLayout *verticalLayout_3;
    QTableView *containersTable;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addContainerButton;
    QPushButton *generateContainerQRButton;
    QSpacerItem *horizontalSpacer_3;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *productsCountLabel;
    QLabel *containersCountLabel;
    QLabel *totalValueLabel;
    QLabel *lowStockLabel;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *refreshButton;
    QPushButton *generateAllQRButton;
    QPushButton *printQRButton;
    QPushButton *exportButton;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QWidget *WarehouseWidget)
    {
        if (WarehouseWidget->objectName().isEmpty())
            WarehouseWidget->setObjectName("WarehouseWidget");
        WarehouseWidget->resize(1000, 700);
        verticalLayout = new QVBoxLayout(WarehouseWidget);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(WarehouseWidget);
        tabWidget->setObjectName("tabWidget");
        productsTab = new QWidget();
        productsTab->setObjectName("productsTab");
        verticalLayout_2 = new QVBoxLayout(productsTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        searchEdit = new QLineEdit(productsTab);
        searchEdit->setObjectName("searchEdit");

        horizontalLayout->addWidget(searchEdit);

        filterCombo = new QComboBox(productsTab);
        filterCombo->addItem(QString());
        filterCombo->setObjectName("filterCombo");

        horizontalLayout->addWidget(filterCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        productsTable = new QTableView(productsTab);
        productsTable->setObjectName("productsTable");

        verticalLayout_2->addWidget(productsTable);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addProductButton = new QPushButton(productsTab);
        addProductButton->setObjectName("addProductButton");

        horizontalLayout_2->addWidget(addProductButton);

        editProductButton = new QPushButton(productsTab);
        editProductButton->setObjectName("editProductButton");

        horizontalLayout_2->addWidget(editProductButton);

        deleteProductButton = new QPushButton(productsTab);
        deleteProductButton->setObjectName("deleteProductButton");

        horizontalLayout_2->addWidget(deleteProductButton);

        generateQRButton = new QPushButton(productsTab);
        generateQRButton->setObjectName("generateQRButton");

        horizontalLayout_2->addWidget(generateQRButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        tabWidget->addTab(productsTab, QString());
        containersTab = new QWidget();
        containersTab->setObjectName("containersTab");
        verticalLayout_3 = new QVBoxLayout(containersTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        containersTable = new QTableView(containersTab);
        containersTable->setObjectName("containersTable");

        verticalLayout_3->addWidget(containersTable);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        addContainerButton = new QPushButton(containersTab);
        addContainerButton->setObjectName("addContainerButton");

        horizontalLayout_3->addWidget(addContainerButton);

        generateContainerQRButton = new QPushButton(containersTab);
        generateContainerQRButton->setObjectName("generateContainerQRButton");

        horizontalLayout_3->addWidget(generateContainerQRButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        tabWidget->addTab(containersTab, QString());

        verticalLayout->addWidget(tabWidget);

        groupBox = new QGroupBox(WarehouseWidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_4 = new QHBoxLayout(groupBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        productsCountLabel = new QLabel(groupBox);
        productsCountLabel->setObjectName("productsCountLabel");

        horizontalLayout_4->addWidget(productsCountLabel);

        containersCountLabel = new QLabel(groupBox);
        containersCountLabel->setObjectName("containersCountLabel");

        horizontalLayout_4->addWidget(containersCountLabel);

        totalValueLabel = new QLabel(groupBox);
        totalValueLabel->setObjectName("totalValueLabel");

        horizontalLayout_4->addWidget(totalValueLabel);

        lowStockLabel = new QLabel(groupBox);
        lowStockLabel->setObjectName("lowStockLabel");

        horizontalLayout_4->addWidget(lowStockLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        refreshButton = new QPushButton(WarehouseWidget);
        refreshButton->setObjectName("refreshButton");

        horizontalLayout_5->addWidget(refreshButton);

        generateAllQRButton = new QPushButton(WarehouseWidget);
        generateAllQRButton->setObjectName("generateAllQRButton");

        horizontalLayout_5->addWidget(generateAllQRButton);

        printQRButton = new QPushButton(WarehouseWidget);
        printQRButton->setObjectName("printQRButton");

        horizontalLayout_5->addWidget(printQRButton);

        exportButton = new QPushButton(WarehouseWidget);
        exportButton->setObjectName("exportButton");

        horizontalLayout_5->addWidget(exportButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_5);


        retranslateUi(WarehouseWidget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WarehouseWidget);
    } // setupUi

    void retranslateUi(QWidget *WarehouseWidget)
    {
        searchEdit->setPlaceholderText(QCoreApplication::translate("WarehouseWidget", "\320\237\320\276\320\270\321\201\320\272 \321\202\320\276\320\262\320\260\321\200\320\260...", nullptr));
        filterCombo->setItemText(0, QCoreApplication::translate("WarehouseWidget", "\320\222\321\201\320\265 \320\272\320\260\321\202\320\265\320\263\320\276\321\200\320\270\320\270", nullptr));

        addProductButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\320\262\320\260\321\200", nullptr));
        editProductButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        deleteProductButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        generateQRButton->setText(QCoreApplication::translate("WarehouseWidget", "QR-\320\272\320\276\320\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(productsTab), QCoreApplication::translate("WarehouseWidget", "\320\242\320\276\320\262\320\260\321\200\321\213", nullptr));
        addContainerButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\272\320\276\320\275\321\202\320\265\320\271\320\275\320\265\321\200", nullptr));
        generateContainerQRButton->setText(QCoreApplication::translate("WarehouseWidget", "QR-\320\272\320\276\320\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(containersTab), QCoreApplication::translate("WarehouseWidget", "\320\232\320\276\320\275\321\202\320\265\320\271\320\275\320\265\321\200\321\213", nullptr));
        groupBox->setTitle(QCoreApplication::translate("WarehouseWidget", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        productsCountLabel->setText(QCoreApplication::translate("WarehouseWidget", "\320\242\320\276\320\262\320\260\321\200\320\276\320\262: 0", nullptr));
        containersCountLabel->setText(QCoreApplication::translate("WarehouseWidget", "\320\232\320\276\320\275\321\202\320\265\320\271\320\275\320\265\321\200\320\276\320\262: 0", nullptr));
        totalValueLabel->setText(QCoreApplication::translate("WarehouseWidget", "\320\236\320\261\321\211\320\260\321\217 \321\201\321\202\320\276\320\270\320\274\320\276\321\201\321\202\321\214: 0 \342\202\275", nullptr));
        lowStockLabel->setText(QCoreApplication::translate("WarehouseWidget", "\320\235\320\270\320\267\320\272\320\270\320\271 \320\267\320\260\320\277\320\260\321\201: 0", nullptr));
        refreshButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
        generateAllQRButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\222\321\201\320\265 QR-\320\272\320\276\320\264\321\213", nullptr));
        printQRButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\237\320\265\321\207\320\260\321\202\321\214 QR", nullptr));
        exportButton->setText(QCoreApplication::translate("WarehouseWidget", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", nullptr));
        (void)WarehouseWidget;
    } // retranslateUi

};

namespace Ui {
    class WarehouseWidget: public Ui_WarehouseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAREHOUSEWIDGET_H
