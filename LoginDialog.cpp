#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "database/DatabaseManager.h"
#include <QMessageBox>
#include <QSqlQuery>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowTitle("Авторизация - Складская система HK");
    setFixedSize(400, 200);
    
    // Установка стилей
    setStyleSheet(R"(
        QDialog {
            background-color: #e3f2fd;
            border: 2px solid #1976d2;
            border-radius: 8px;
        }
        QLabel {
            color: #0d47a1;
            font-weight: bold;
        }
        QLineEdit {
            border: 2px solid #bbdefb;
            border-radius: 4px;
            padding: 8px;
            font-size: 12pt;
        }
        QPushButton {
            background-color: #1976d2;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 4px;
            font-weight: bold;
            font-size: 11pt;
        }
        QPushButton:hover {
            background-color: #1565c0;
        }
        QPushButton#exitButton {
            background-color: #d32f2f;
        }
        QPushButton#exitButton:hover {
            background-color: #c62828;
        }
    )");
    
    ui->usernameEdit->setFocus();
    
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &QDialog::reject);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLoginButtonClicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя пользователя и пароль!");
        return;
    }
    
    if (authenticate(username, password)) {
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", "Неверное имя пользователя или пароль!");
        ui->passwordEdit->clear();
        ui->usernameEdit->setFocus();
    }
}

bool LoginDialog::authenticate(const QString& username, const QString& password)
{
    QSqlQuery query = DatabaseManager::instance().getUserByUsername(username);
    if (query.next()) {
        QString dbPassword = query.value("password").toString();
        if (dbPassword == password) {
            m_currentUser = User(
                query.value("id").toInt(),
                query.value("username").toString(),
                query.value("password").toString(),
                query.value("email").toString(),
                query.value("role").toString(),
                query.value("full_name").toString(),
                query.value("phone").toString(),
                query.value("created_at").toDateTime()
            );
            return true;
        }
    }
    
    return false;
}