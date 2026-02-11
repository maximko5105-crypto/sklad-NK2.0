#include "RegistrationDialog.h"
#include "database/DatabaseManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlQuery>

RegistrationDialog::RegistrationDialog(QWidget *parent)
    : QDialog(parent)
    , m_usernameEdit(nullptr)
    , m_passwordEdit(nullptr)
    , m_confirmPasswordEdit(nullptr)
    , m_emailEdit(nullptr)
    , m_fullNameEdit(nullptr)
    , m_phoneEdit(nullptr)
    , m_roleCombo(nullptr)
    , m_registerButton(nullptr)
    , m_cancelButton(nullptr)
{
    setupUi();
    
    setWindowTitle("Регистрация нового пользователя");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setModal(true);
}

void RegistrationDialog::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(5);
    
    // Форма регистрации
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setSpacing(5);
    
    m_usernameEdit = new QLineEdit(this);
    m_usernameEdit->setPlaceholderText("Введите имя пользователя (3-20 символов)");
    m_usernameEdit->setMinimumWidth(300);
    connect(m_usernameEdit, &QLineEdit::textChanged, this, &RegistrationDialog::validateForm);
    formLayout->addRow("Имя пользователя*:", m_usernameEdit);
    
    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setPlaceholderText("Введите пароль (минимум 6 символов)");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    connect(m_passwordEdit, &QLineEdit::textChanged, this, &RegistrationDialog::validateForm);
    formLayout->addRow("Пароль*:", m_passwordEdit);
    
    m_confirmPasswordEdit = new QLineEdit(this);
    m_confirmPasswordEdit->setPlaceholderText("Повторите пароль");
    m_confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    connect(m_confirmPasswordEdit, &QLineEdit::textChanged, this, &RegistrationDialog::validateForm);
    formLayout->addRow("Подтверждение пароля*:", m_confirmPasswordEdit);
    
    m_emailEdit = new QLineEdit(this);
    m_emailEdit->setPlaceholderText("example@domain.com");
    connect(m_emailEdit, &QLineEdit::textChanged, this, &RegistrationDialog::validateForm);
    formLayout->addRow("Email:", m_emailEdit);
    
    m_fullNameEdit = new QLineEdit(this);
    m_fullNameEdit->setPlaceholderText("Иванов Иван Иванович");
    connect(m_fullNameEdit, &QLineEdit::textChanged, this, &RegistrationDialog::validateForm);
    formLayout->addRow("Полное имя*:", m_fullNameEdit);
    
    m_phoneEdit = new QLineEdit(this);
    m_phoneEdit->setPlaceholderText("+7 999 123 45 67");
    QRegularExpression phoneRegex("^\\+?[0-9\\s\\-\\(\\)]{10,20}$");
    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(phoneRegex, this);
    m_phoneEdit->setValidator(phoneValidator);
    formLayout->addRow("Телефон:", m_phoneEdit);
    
    m_roleCombo = new QComboBox(this);
    m_roleCombo->addItem("Работник", "worker");
    m_roleCombo->addItem("Менеджер", "manager");
    m_roleCombo->addItem("Администратор", "admin");
    formLayout->addRow("Роль:", m_roleCombo);
    
    mainLayout->addLayout(formLayout);
    
    // Примечание
    QLabel *noteLabel = new QLabel("* - обязательные поля", this);
    noteLabel->setStyleSheet("color: gray; font-size: 10px; padding: 5px;");
    noteLabel->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(noteLabel);
    
    // Кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);
    
    m_registerButton = new QPushButton("Зарегистрировать", this);
    m_registerButton->setDefault(true);
    m_registerButton->setMinimumWidth(120);
    m_registerButton->setEnabled(false);
    connect(m_registerButton, &QPushButton::clicked, this, &RegistrationDialog::onRegister);
    
    m_cancelButton = new QPushButton("Отмена", this);
    m_cancelButton->setMinimumWidth(100);
    connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_registerButton);
    buttonLayout->addWidget(m_cancelButton);
    
    mainLayout->addLayout(buttonLayout);
    
    // Установка фиксированного размера
    setFixedSize(520, 380);
}

void RegistrationDialog::onRegister() {
    QString username = m_usernameEdit->text().trimmed();
    QString password = m_passwordEdit->text();
    QString email = m_emailEdit->text().trimmed();
    QString fullName = m_fullNameEdit->text().trimmed();
    QString phone = m_phoneEdit->text().trimmed();
    QString role = m_roleCombo->currentData().toString();
    
    // Дополнительная валидация
    if (!isUsernameAvailable(username)) {
        QMessageBox::warning(this, "Ошибка", 
            "Имя пользователя уже занято!");
        m_usernameEdit->setFocus();
        m_usernameEdit->selectAll();
        return;
    }
    
    if (!email.isEmpty() && !isEmailAvailable(email)) {
        QMessageBox::warning(this, "Ошибка", 
            "Email уже зарегистрирован!");
        m_emailEdit->setFocus();
        m_emailEdit->selectAll();
        return;
    }
    
    // Регистрация пользователя
    if (DatabaseManager::instance().addUser(username, password, email, 
                                            role, fullName, phone)) {
        QMessageBox::information(this, "Успех", 
            "Пользователь успешно зарегистрирован!");
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка", 
            "Не удалось зарегистрировать пользователя!");
    }
}

void RegistrationDialog::validateForm() {
    bool valid = true;
    
    QString username = m_usernameEdit->text().trimmed();
    QString password = m_passwordEdit->text();
    QString confirmPassword = m_confirmPasswordEdit->text();
    QString email = m_emailEdit->text().trimmed();
    QString fullName = m_fullNameEdit->text().trimmed();
    
    // Проверка имени пользователя
    if (username.length() < 3 || username.length() > 20) {
        valid = false;
    }
    
    // Проверка пароля
    if (password.length() < 6) {
        valid = false;
    }
    
    // Проверка совпадения паролей
    if (password != confirmPassword) {
        valid = false;
    }
    
    // Проверка email
    if (!email.isEmpty()) {
        QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        if (!emailRegex.match(email).hasMatch()) {
            valid = false;
        }
    }
    
    // Проверка полного имени
    if (fullName.isEmpty()) {
        valid = false;
    }
    
    m_registerButton->setEnabled(valid);
}

bool RegistrationDialog::isUsernameAvailable(const QString& username) {
    QSqlQuery query = DatabaseManager::instance().getUserByUsername(username);
    return !query.next();
}

bool RegistrationDialog::isEmailAvailable(const QString& email) {
    if (email.isEmpty()) {
        return true;
    }
    
    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE email = :email");
    query.bindValue(":email", email);
    query.exec();
    return !query.next();
}

QString RegistrationDialog::getUsername() const {
    return m_usernameEdit->text().trimmed();
}