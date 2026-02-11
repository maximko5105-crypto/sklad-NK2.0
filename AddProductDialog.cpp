#include "AddProductDialog.h"
#include "ui_AddProductDialog.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QPushButton>

AddProductDialog::AddProductDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddProductDialog),
      m_isValid(false)
{
    ui->setupUi(this);
    setWindowTitle("Добавить товар");

    // ================= СТИЛИ =================
    setStyleSheet(R"(
        QDialog {
            background-color: #e3f2fd;
        }
        QLabel {
            color: #0d47a1;
            font-weight: bold;
        }
        QLineEdit, QTextEdit, QComboBox {
            border: 2px solid #bbdefb;
            border-radius: 4px;
            padding: 6px;
            background-color: white;
        }
        QPushButton {
            background-color: #1976d2;
            color: white;
            border: none;
            padding: 8px 16px;
            border-radius: 4px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #1565c0;
        }
        QPushButton:disabled {
            background-color: #b0bec5;
        }
    )");

    // ================= ВАЛИДАТОРЫ =================

    // Количество (только целые >= 0)
    ui->quantityEdit->setValidator(new QIntValidator(0, 999999, this));

    // Минимальный запас
    ui->minQuantityEdit->setValidator(new QIntValidator(0, 999999, this));

    // Цена (2 знака после запятой)
    auto *priceValidator = new QDoubleValidator(0.0, 999999.99, 2, this);
    priceValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->priceEdit->setValidator(priceValidator);

    // ================= СПРАВОЧНИКИ =================

    QStringList categories = {
        "Электроника", "Аксессуары", "Аудио", "Хранение данных",
        "Сетевое оборудование", "Кабели", "Офис",
        "Производство", "Другое"
    };
    ui->categoryCombo->addItems(categories);

    QStringList units = {
        "шт.", "кг", "г", "л", "м", "м²", "м³", "уп.", "пачка"
    };
    ui->unitCombo->addItems(units);

    // ================= СИГНАЛЫ =================

    connect(ui->addButton, &QPushButton::clicked,
            this, &AddProductDialog::onAddButtonClicked);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &AddProductDialog::onCancelButtonClicked);

    // Автоматическая проверка формы
    connect(ui->nameEdit, &QLineEdit::textChanged,
            this, &AddProductDialog::validateForm);

    connect(ui->skuEdit, &QLineEdit::textChanged,
            this, &AddProductDialog::validateForm);

    connect(ui->quantityEdit, &QLineEdit::textChanged,
            this, &AddProductDialog::validateForm);

    connect(ui->priceEdit, &QLineEdit::textChanged,
            this, &AddProductDialog::validateForm);

    validateForm(); // первичная проверка
}

AddProductDialog::~AddProductDialog()
{
    delete ui;
}

// =====================================================
// КНОПКА ДОБАВИТЬ
// =====================================================
void AddProductDialog::onAddButtonClicked()
{
    if (!m_isValid) {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Заполните все обязательные поля корректно!");
        return;
    }

    accept();  // Закрываем диалог с QDialog::Accepted
}

// =====================================================
// КНОПКА ОТМЕНА
// =====================================================
void AddProductDialog::onCancelButtonClicked()
{
    reject();  // Закрываем диалог с QDialog::Rejected
}

// =====================================================
// ВАЛИДАЦИЯ ФОРМЫ
// =====================================================
void AddProductDialog::validateForm()
{
    m_isValid = true;

    // Название
    if (ui->nameEdit->text().trimmed().isEmpty())
        m_isValid = false;

    // SKU
    if (ui->skuEdit->text().trimmed().isEmpty())
        m_isValid = false;

    // Количество
    bool quantityOk = false;
    int quantity = ui->quantityEdit->text().toInt(&quantityOk);
    if (!quantityOk || quantity < 0)
        m_isValid = false;

    // Цена
    bool priceOk = false;
    double price = ui->priceEdit->text().toDouble(&priceOk);
    if (!priceOk || price <= 0.0)
        m_isValid = false;

    // Категория
    if (ui->categoryCombo->currentText().isEmpty())
        m_isValid = false;

    // Единица измерения
    if (ui->unitCombo->currentText().isEmpty())
        m_isValid = false;

    // Активируем/деактивируем кнопку
    ui->addButton->setEnabled(m_isValid);
}

// =====================================================
// ГЕТТЕРЫ
// =====================================================

QString AddProductDialog::getProductName() const
{
    return ui->nameEdit->text().trimmed();
}

QString AddProductDialog::getDescription() const
{
    return ui->descriptionEdit->toPlainText().trimmed();
}

QString AddProductDialog::getCategory() const
{
    return ui->categoryCombo->currentText();
}

QString AddProductDialog::getSku() const
{
    return ui->skuEdit->text().trimmed();
}

QString AddProductDialog::getBarcode() const
{
    return ui->barcodeEdit->text().trimmed();
}

int AddProductDialog::getQuantity() const
{
    return ui->quantityEdit->text().toInt();
}

QString AddProductDialog::getUnit() const
{
    return ui->unitCombo->currentText();
}

double AddProductDialog::getPrice() const
{
    return ui->priceEdit->text().toDouble();
}

int AddProductDialog::getMinQuantity() const
{
    return ui->minQuantityEdit->text().toInt();
}

QString AddProductDialog::getLocation() const
{
    return ui->locationEdit->text().trimmed();
}
