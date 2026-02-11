#include "AddContainerDialog.h"
#include "gui/AddContainerDialog.ui"

#include <QMessageBox>
#include <QIntValidator>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>

#include "database/DatabaseManager.h"

AddContainerDialog::AddContainerDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddContainerDialog),
      m_isValid(false)
{
    ui->setupUi(this);
    setWindowTitle("Добавить контейнер");

    // ================= ВАЛИДАТОРЫ =================

    ui->capacityEdit->setValidator(new QIntValidator(1, 999999, this));
    ui->currentLoadEdit->setValidator(new QIntValidator(0, 999999, this));

    // ================= СТАТУСЫ =================

    QStringList statuses = {"empty", "partial", "full", "reserved"};
    ui->statusCombo->addItems(statuses);

    // ================= ЗАГРУЗКА ТОВАРОВ =================

    ui->productCombo->addItem("Не выбрано", -1);

    QSqlQuery query = DatabaseManager::instance().getAllProducts();

    if (!query.isActive()) {
        qDebug() << "Ошибка запроса:" << query.lastError().text();
    } else {
        while (query.next()) {
            int id = query.value("id").toInt();
            QString name = query.value("name").toString();
            ui->productCombo->addItem(name, id);
        }
    }

    // ================= СИГНАЛЫ =================

    connect(ui->addButton, &QPushButton::clicked,
            this, &AddContainerDialog::onAddButtonClicked);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &AddContainerDialog::onCancelButtonClicked);

    connect(ui->codeEdit, &QLineEdit::textChanged,
            this, &AddContainerDialog::validateForm);

    connect(ui->nameEdit, &QLineEdit::textChanged,
            this, &AddContainerDialog::validateForm);

    connect(ui->locationEdit, &QLineEdit::textChanged,
            this, &AddContainerDialog::validateForm);

    connect(ui->capacityEdit, &QLineEdit::textChanged,
            this, &AddContainerDialog::validateForm);

    connect(ui->currentLoadEdit, &QLineEdit::textChanged,
            this, &AddContainerDialog::validateForm);

    validateForm();
}

AddContainerDialog::~AddContainerDialog()
{
    delete ui;
}

// =====================================================
// КНОПКА ДОБАВИТЬ
// =====================================================
void AddContainerDialog::onAddButtonClicked()
{
    if (!m_isValid) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните все обязательные поля корректно!");
        return;
    }

    accept();
}

// =====================================================
// КНОПКА ОТМЕНА
// =====================================================
void AddContainerDialog::onCancelButtonClicked()
{
    reject();
}

// =====================================================
// ВАЛИДАЦИЯ ФОРМЫ
// =====================================================
void AddContainerDialog::validateForm()
{
    m_isValid = true;

    // Код контейнера
    if (ui->codeEdit->text().trimmed().isEmpty())
        m_isValid = false;

    // Название
    if (ui->nameEdit->text().trimmed().isEmpty())
        m_isValid = false;

    // Локация
    if (ui->locationEdit->text().trimmed().isEmpty())
        m_isValid = false;

    // Вместимость
    bool capacityOk = false;
    int capacity = ui->capacityEdit->text().toInt(&capacityOk);
    if (!capacityOk || capacity <= 0)
        m_isValid = false;

    // Текущая загрузка
    bool loadOk = false;
    int currentLoad = ui->currentLoadEdit->text().toInt(&loadOk);
    if (!loadOk || currentLoad < 0)
        m_isValid = false;

    // Проверка превышения вместимости
    if (capacityOk && loadOk && currentLoad > capacity) {
        m_isValid = false;
        ui->currentLoadEdit->setStyleSheet("border: 2px solid red;");
    } else {
        ui->currentLoadEdit->setStyleSheet("");
    }

    ui->addButton->setEnabled(m_isValid);
}

// =====================================================
// ГЕТТЕРЫ
// =====================================================

QString AddContainerDialog::getContainerCode() const
{
    return ui->codeEdit->text().trimmed();
}

QString AddContainerDialog::getContainerName() const
{
    return ui->nameEdit->text().trimmed();
}

QString AddContainerDialog::getLocation() const
{
    return ui->locationEdit->text().trimmed();
}

int AddContainerDialog::getCapacity() const
{
    return ui->capacityEdit->text().toInt();
}

int AddContainerDialog::getCurrentLoad() const
{
    return ui->currentLoadEdit->text().toInt();
}

QString AddContainerDialog::getStatus() const
{
    return ui->statusCombo->currentText();
}

int AddContainerDialog::getProductId() const
{
    return ui->productCombo->currentData().toInt();
}
