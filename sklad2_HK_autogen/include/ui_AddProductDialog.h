/********************************************************************************
** Form generated from reading UI file 'AddProductDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPRODUCTDIALOG_H
#define UI_ADDPRODUCTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddProductDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelName;
    QLineEdit *nameEdit;
    QLabel *labelDescription;
    QTextEdit *descriptionEdit;
    QLabel *labelCategory;
    QComboBox *categoryCombo;
    QLabel *labelSku;
    QLineEdit *skuEdit;
    QLabel *labelBarcode;
    QLineEdit *barcodeEdit;
    QLabel *labelQuantity;
    QLineEdit *quantityEdit;
    QLabel *labelUnit;
    QComboBox *unitCombo;
    QLabel *labelPrice;
    QLineEdit *priceEdit;
    QLabel *labelMinQuantity;
    QLineEdit *minQuantityEdit;
    QLabel *labelLocation;
    QLineEdit *locationEdit;
    QHBoxLayout *hboxLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AddProductDialog)
    {
        if (AddProductDialog->objectName().isEmpty())
            AddProductDialog->setObjectName("AddProductDialog");
        AddProductDialog->resize(500, 600);
        verticalLayout = new QVBoxLayout(AddProductDialog);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        labelName = new QLabel(AddProductDialog);
        labelName->setObjectName("labelName");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelName);

        nameEdit = new QLineEdit(AddProductDialog);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        labelDescription = new QLabel(AddProductDialog);
        labelDescription->setObjectName("labelDescription");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelDescription);

        descriptionEdit = new QTextEdit(AddProductDialog);
        descriptionEdit->setObjectName("descriptionEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, descriptionEdit);

        labelCategory = new QLabel(AddProductDialog);
        labelCategory->setObjectName("labelCategory");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelCategory);

        categoryCombo = new QComboBox(AddProductDialog);
        categoryCombo->setObjectName("categoryCombo");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, categoryCombo);

        labelSku = new QLabel(AddProductDialog);
        labelSku->setObjectName("labelSku");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, labelSku);

        skuEdit = new QLineEdit(AddProductDialog);
        skuEdit->setObjectName("skuEdit");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, skuEdit);

        labelBarcode = new QLabel(AddProductDialog);
        labelBarcode->setObjectName("labelBarcode");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, labelBarcode);

        barcodeEdit = new QLineEdit(AddProductDialog);
        barcodeEdit->setObjectName("barcodeEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, barcodeEdit);

        labelQuantity = new QLabel(AddProductDialog);
        labelQuantity->setObjectName("labelQuantity");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, labelQuantity);

        quantityEdit = new QLineEdit(AddProductDialog);
        quantityEdit->setObjectName("quantityEdit");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, quantityEdit);

        labelUnit = new QLabel(AddProductDialog);
        labelUnit->setObjectName("labelUnit");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, labelUnit);

        unitCombo = new QComboBox(AddProductDialog);
        unitCombo->setObjectName("unitCombo");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, unitCombo);

        labelPrice = new QLabel(AddProductDialog);
        labelPrice->setObjectName("labelPrice");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, labelPrice);

        priceEdit = new QLineEdit(AddProductDialog);
        priceEdit->setObjectName("priceEdit");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, priceEdit);

        labelMinQuantity = new QLabel(AddProductDialog);
        labelMinQuantity->setObjectName("labelMinQuantity");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, labelMinQuantity);

        minQuantityEdit = new QLineEdit(AddProductDialog);
        minQuantityEdit->setObjectName("minQuantityEdit");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, minQuantityEdit);

        labelLocation = new QLabel(AddProductDialog);
        labelLocation->setObjectName("labelLocation");

        formLayout->setWidget(9, QFormLayout::ItemRole::LabelRole, labelLocation);

        locationEdit = new QLineEdit(AddProductDialog);
        locationEdit->setObjectName("locationEdit");

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, locationEdit);


        verticalLayout->addLayout(formLayout);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        horizontalSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(horizontalSpacer);

        addButton = new QPushButton(AddProductDialog);
        addButton->setObjectName("addButton");

        hboxLayout->addWidget(addButton);

        cancelButton = new QPushButton(AddProductDialog);
        cancelButton->setObjectName("cancelButton");

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(AddProductDialog);

        QMetaObject::connectSlotsByName(AddProductDialog);
    } // setupUi

    void retranslateUi(QDialog *AddProductDialog)
    {
        AddProductDialog->setWindowTitle(QCoreApplication::translate("AddProductDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\320\262\320\260\321\200", nullptr));
        labelName->setText(QCoreApplication::translate("AddProductDialog", "\320\235\320\260\320\270\320\274\320\265\320\275\320\276\320\262\320\260\320\275\320\270\320\265:", nullptr));
        labelDescription->setText(QCoreApplication::translate("AddProductDialog", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265:", nullptr));
        labelCategory->setText(QCoreApplication::translate("AddProductDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217:", nullptr));
        labelSku->setText(QCoreApplication::translate("AddProductDialog", "SKU:", nullptr));
        labelBarcode->setText(QCoreApplication::translate("AddProductDialog", "\320\250\321\202\321\200\320\270\321\205\320\272\320\276\320\264:", nullptr));
        labelQuantity->setText(QCoreApplication::translate("AddProductDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        labelUnit->setText(QCoreApplication::translate("AddProductDialog", "\320\225\320\264. \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217:", nullptr));
        labelPrice->setText(QCoreApplication::translate("AddProductDialog", "\320\246\320\265\320\275\320\260:", nullptr));
        labelMinQuantity->setText(QCoreApplication::translate("AddProductDialog", "\320\234\320\270\320\275. \320\267\320\260\320\277\320\260\321\201:", nullptr));
        labelLocation->setText(QCoreApplication::translate("AddProductDialog", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265:", nullptr));
        addButton->setText(QCoreApplication::translate("AddProductDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddProductDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddProductDialog: public Ui_AddProductDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPRODUCTDIALOG_H
