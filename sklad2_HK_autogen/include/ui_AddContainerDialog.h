/********************************************************************************
** Form generated from reading UI file 'AddContainerDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCONTAINERDIALOG_H
#define UI_ADDCONTAINERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
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
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *nameEdit;
    QLabel *label_2;
    QTextEdit *descriptionEdit;
    QLabel *label_3;
    QComboBox *categoryCombo;
    QLabel *label_4;
    QLineEdit *skuEdit;
    QLabel *label_5;
    QLineEdit *barcodeEdit;
    QLabel *label_6;
    QLineEdit *quantityEdit;
    QLabel *label_7;
    QComboBox *unitCombo;
    QLabel *label_8;
    QLineEdit *priceEdit;
    QLabel *label_9;
    QLineEdit *minQuantityEdit;
    QLabel *label_10;
    QLineEdit *locationEdit;
    QLabel *noteLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *addButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *AddProductDialog)
    {
        if (AddProductDialog->objectName().isEmpty())
            AddProductDialog->setObjectName("AddProductDialog");
        AddProductDialog->resize(500, 500);
        verticalLayout = new QVBoxLayout(AddProductDialog);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(AddProductDialog);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        nameEdit = new QLineEdit(groupBox);
        nameEdit->setObjectName("nameEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, nameEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        descriptionEdit = new QTextEdit(groupBox);
        descriptionEdit->setObjectName("descriptionEdit");
        descriptionEdit->setMaximumHeight(80);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, descriptionEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        categoryCombo = new QComboBox(groupBox);
        categoryCombo->setObjectName("categoryCombo");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, categoryCombo);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);

        skuEdit = new QLineEdit(groupBox);
        skuEdit->setObjectName("skuEdit");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, skuEdit);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_5);

        barcodeEdit = new QLineEdit(groupBox);
        barcodeEdit->setObjectName("barcodeEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, barcodeEdit);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_6);

        quantityEdit = new QLineEdit(groupBox);
        quantityEdit->setObjectName("quantityEdit");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, quantityEdit);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_7);

        unitCombo = new QComboBox(groupBox);
        unitCombo->setObjectName("unitCombo");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, unitCombo);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, label_8);

        priceEdit = new QLineEdit(groupBox);
        priceEdit->setObjectName("priceEdit");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, priceEdit);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, label_9);

        minQuantityEdit = new QLineEdit(groupBox);
        minQuantityEdit->setObjectName("minQuantityEdit");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, minQuantityEdit);

        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");

        formLayout->setWidget(9, QFormLayout::ItemRole::LabelRole, label_10);

        locationEdit = new QLineEdit(groupBox);
        locationEdit->setObjectName("locationEdit");

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, locationEdit);


        verticalLayout->addWidget(groupBox);

        noteLabel = new QLabel(AddProductDialog);
        noteLabel->setObjectName("noteLabel");
        noteLabel->setAlignment(Qt::AlignRight);

        verticalLayout->addWidget(noteLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addButton = new QPushButton(AddProductDialog);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        cancelButton = new QPushButton(AddProductDialog);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(AddProductDialog);

        QMetaObject::connectSlotsByName(AddProductDialog);
    } // setupUi

    void retranslateUi(QDialog *AddProductDialog)
    {
        AddProductDialog->setWindowTitle(QCoreApplication::translate("AddProductDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\202\320\276\320\262\320\260\321\200", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AddProductDialog", "\320\230\320\275\321\204\320\276\321\200\320\274\320\260\321\206\320\270\321\217 \320\276 \321\202\320\276\320\262\320\260\321\200\320\265", nullptr));
        label->setText(QCoreApplication::translate("AddProductDialog", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265*:", nullptr));
        label_2->setText(QCoreApplication::translate("AddProductDialog", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265:", nullptr));
        label_3->setText(QCoreApplication::translate("AddProductDialog", "\320\232\320\260\321\202\320\265\320\263\320\276\321\200\320\270\321\217*:", nullptr));
        label_4->setText(QCoreApplication::translate("AddProductDialog", "SKU*:", nullptr));
        label_5->setText(QCoreApplication::translate("AddProductDialog", "\320\250\321\202\321\200\320\270\321\205-\320\272\320\276\320\264:", nullptr));
        label_6->setText(QCoreApplication::translate("AddProductDialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276*:", nullptr));
        quantityEdit->setText(QCoreApplication::translate("AddProductDialog", "0", nullptr));
        label_7->setText(QCoreApplication::translate("AddProductDialog", "\320\225\320\264\320\270\320\275\320\270\321\206\320\260 \320\270\320\267\320\274\320\265\321\200\320\265\320\275\320\270\321\217*:", nullptr));
        label_8->setText(QCoreApplication::translate("AddProductDialog", "\320\246\320\265\320\275\320\260*:", nullptr));
        label_9->setText(QCoreApplication::translate("AddProductDialog", "\320\234\320\270\320\275. \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276:", nullptr));
        minQuantityEdit->setText(QCoreApplication::translate("AddProductDialog", "0", nullptr));
        label_10->setText(QCoreApplication::translate("AddProductDialog", "\320\234\320\265\321\201\321\202\320\276\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265:", nullptr));
        noteLabel->setText(QCoreApplication::translate("AddProductDialog", "* - \320\276\320\261\321\217\320\267\320\260\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\277\320\276\320\273\321\217", nullptr));
        addButton->setText(QCoreApplication::translate("AddProductDialog", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        cancelButton->setText(QCoreApplication::translate("AddProductDialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddProductDialog: public Ui_AddProductDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCONTAINERDIALOG_H
