#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QComboBox;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = nullptr);
    
    QString getUsername() const;

private slots:
    void onRegister();
    void validateForm();

private:
    void setupUi();
    bool isUsernameAvailable(const QString& username);
    bool isEmailAvailable(const QString& email);
    
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
    QLineEdit *m_confirmPasswordEdit;
    QLineEdit *m_emailEdit;
    QLineEdit *m_fullNameEdit;
    QLineEdit *m_phoneEdit;
    QComboBox *m_roleCombo;
    QPushButton *m_registerButton;
    QPushButton *m_cancelButton;
};

#endif // REGISTRATIONDIALOG_H