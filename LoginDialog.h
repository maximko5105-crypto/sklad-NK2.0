#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "models/User.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    const User& getCurrentUser() const { return m_currentUser; }

private slots:
    void onLoginButtonClicked();

private:
    bool authenticate(const QString& username, const QString& password);

    Ui::LoginDialog *ui;
    User m_currentUser;
};

#endif // LOGINDIALOG_H