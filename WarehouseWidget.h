#ifndef WAREHOUSEWIDGET_H
#define WAREHOUSEWIDGET_H

#include <QWidget>
#include "models/User.h"

namespace Ui {
class WarehouseWidget;
}

class QrGenerator;

/*
 * WarehouseWidget
 * Виджет управления складом.
 * Отвечает за:
 *  - отображение товаров и контейнеров
 *  - фильтрацию и поиск
 *  - генерацию QR-кодов
 *  - экспорт данных
 *  - отображение статистики
 */

class WarehouseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WarehouseWidget(const User& user, QWidget *parent = nullptr);
    ~WarehouseWidget();

    // ===== ПУБЛИЧНЫЙ API (можно вызывать из MainWindow) =====
    void refreshData();
    void addProduct();          // вызывается из меню
    void editProduct();
    void deleteProduct();

signals:
    void statisticsUpdated();   // сигнал обновления статистики

private slots:
    // ===== ВНУТРЕННИЕ СЛОТЫ UI =====
    void onAddProductClicked();
    void onEditProductClicked();
    void onDeleteProductClicked();

    void onGenerateProductQRClicked();
    void onGenerateAllQRCodesClicked();

    void onAddContainerClicked();
    void onDeleteContainerClicked();
    void onGenerateContainerQRClicked();

    void onExportDataClicked();
    void onSearchTextChanged(const QString& text);
    void onFilterComboChanged(int index);

private:
    // ===== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =====
    void setupUi();
    void setupConnections();

    void loadProducts();
    void loadContainers();
    void updateStatistics();

    void generateQRForProduct(int row);
    void generateAllQRCodes();

    bool checkUserPermissions() const;

private:
    Ui::WarehouseWidget* ui;
    User m_currentUser;
    QrGenerator* m_qrGenerator;
};

#endif // WAREHOUSEWIDGET_H
