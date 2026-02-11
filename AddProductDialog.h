#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = nullptr);
    ~AddProductDialog();

    QString getProductName() const;
    QString getDescription() const;
    QString getCategory() const;
    QString getSku() const;
    QString getBarcode() const;
    int getQuantity() const;
    QString getUnit() const;
    double getPrice() const;
    int getMinQuantity() const;
    QString getLocation() const;

private slots:
    void onAddButtonClicked();
    void onCancelButtonClicked();
    void validateForm();

private:
    Ui::AddProductDialog *ui;
    bool m_isValid;
};

#endif // ADDPRODUCTDIALOG_H