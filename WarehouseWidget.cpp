#include "WarehouseWidget.h"
#include "ui_WarehouseWidget.h"

#include <QMessageBox>

WarehouseWidget::WarehouseWidget(const User& user, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::WarehouseWidget),
      m_currentUser(user),
      m_qrGenerator(nullptr)
{
    ui->setupUi(this);

    setupConnections();
    refreshData();
}

WarehouseWidget::~WarehouseWidget()
{
    delete ui;
}

// ========================
// ПУБЛИЧНЫЕ МЕТОДЫ
// ========================

void WarehouseWidget::refreshData()
{
    loadProducts();
    loadContainers();
    updateStatistics();
}

void WarehouseWidget::addProduct()
{
    onAddProductClicked();
}

void WarehouseWidget::editProduct()
{
    onEditProductClicked();
}

void WarehouseWidget::deleteProduct()
{
    onDeleteProductClicked();
}

// ========================
// СЛОТЫ
// ========================

void WarehouseWidget::onAddProductClicked()
{
    if (!checkUserPermissions()) {
        QMessageBox::warning(this, "Ошибка", "Недостаточно прав.");
        return;
    }

    QMessageBox::information(this, "Добавление", "Открытие диалога добавления товара...");
    // TODO: открыть AddProductDialog
}

void WarehouseWidget::onEditProductClicked()
{
    QMessageBox::information(this, "Редактирование", "Редактирование товара...");
}

void WarehouseWidget::onDeleteProductClicked()
{
    QMessageBox::information(this, "Удаление", "Удаление товара...");
}

void WarehouseWidget::onGenerateProductQRClicked()
{
    QMessageBox::information(this, "QR", "Генерация QR для товара...");
}

void WarehouseWidget::onGenerateAllQRCodesClicked()
{
    generateAllQRCodes();
}

void WarehouseWidget::onAddContainerClicked()
{
    QMessageBox::information(this, "Контейнер", "Добавление контейнера...");
}

void WarehouseWidget::onDeleteContainerClicked()
{
    QMessageBox::information(this, "Контейнер", "Удаление контейнера...");
}

void WarehouseWidget::onGenerateContainerQRClicked()
{
    QMessageBox::information(this, "QR", "Генерация QR контейнера...");
}

void WarehouseWidget::onExportDataClicked()
{
    QMessageBox::information(this, "Экспорт", "Экспорт данных...");
}

void WarehouseWidget::onSearchTextChanged(const QString& text)
{
    Q_UNUSED(text);
    loadProducts();
}

void WarehouseWidget::onFilterComboChanged(int index)
{
    Q_UNUSED(index);
    loadProducts();
}

// ========================
// PRIVATE
// ========================

void WarehouseWidget::setupConnections()
{
    // Пример подключения кнопки:
    // connect(ui->addProductButton, &QPushButton::clicked,
    //         this, &WarehouseWidget::onAddProductClicked);
}

void WarehouseWidget::loadProducts()
{
    // TODO: загрузка товаров из БД
}

void WarehouseWidget::loadContainers()
{
    // TODO: загрузка контейнеров из БД
}

void WarehouseWidget::updateStatistics()
{
    emit statisticsUpdated();
}

void WarehouseWidget::generateQRForProduct(int row)
{
    Q_UNUSED(row);
}

void WarehouseWidget::generateAllQRCodes()
{
    QMessageBox::information(this, "QR", "Генерация всех QR-кодов...");
}

bool WarehouseWidget::checkUserPermissions() const
{
    // TODO: проверить роль пользователя
    return true;
}
