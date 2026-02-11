#ifndef QRDISPLAYDIALOG_H
#define QRDISPLAYDIALOG_H

#include <QDialog>

namespace Ui {
class QrDisplayDialog;
}

class QrDisplayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QrDisplayDialog(QWidget *parent = nullptr);
    ~QrDisplayDialog();

private:
    Ui::QrDisplayDialog *ui;
};

#endif // QRDISPLAYDIALOG_H