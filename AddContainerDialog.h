#ifndef ADDCONTAINERDIALOG_H
#define ADDCONTAINERDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddContainerDialog;   // ← правильное объявление!
}
QT_END_NAMESPACE

class AddContainerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddContainerDialog(QWidget *parent = nullptr);
    ~AddContainerDialog();

    QString getContainerCode() const;
    QString getContainerName() const;
    QString getLocation() const;
    int getCapacity() const;
    int getCurrentLoad() const;
    QString getStatus() const;
    int getProductId() const;

private:
    Ui::AddContainerDialog *ui;
    bool m_isValid;

    void validateForm();
};

#endif
