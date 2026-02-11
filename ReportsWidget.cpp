#include "ReportsWidget.h"
#include "database/DatabaseManager.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QFileDialog>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QDate>
#include <QDateTime>
#include <QMessageBox>
#include <QLabel>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFile>
#include <QIODevice>
#include <QFont>

ReportsWidget::ReportsWidget(const User& user, QWidget *parent)
    : QWidget(parent), m_currentUser(user)
{
    setupUi();
}

void ReportsWidget::setupUi() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Панель управления отчетами
    QHBoxLayout *toolbar = new QHBoxLayout();
    toolbar->setSpacing(10);

    // Выбор типа отчета
    m_reportTypeCombo = new QComboBox(this);
    m_reportTypeCombo->addItem("Инвентаризация", 0);
    m_reportTypeCombo->addItem("Движение товаров", 1);
    m_reportTypeCombo->addItem("Низкий запас", 2);
    m_reportTypeCombo->addItem("Контейнеры", 3);
    toolbar->addWidget(new QLabel("Тип отчета:", this));
    toolbar->addWidget(m_reportTypeCombo);
    
    // Период для отчетов с датами
    QWidget *dateWidget = new QWidget(this);
    QHBoxLayout *dateLayout = new QHBoxLayout(dateWidget);
    dateLayout->setContentsMargins(0, 0, 0, 0);
    dateLayout->setSpacing(5);
    
    m_dateFromEdit = new QDateEdit(QDate::currentDate().addDays(-30), this);
    m_dateToEdit = new QDateEdit(QDate::currentDate(), this);
    m_dateFromEdit->setCalendarPopup(true);
    m_dateToEdit->setCalendarPopup(true);
    m_dateFromEdit->setDisplayFormat("dd.MM.yyyy");
    m_dateToEdit->setDisplayFormat("dd.MM.yyyy");
    
    dateLayout->addWidget(new QLabel("С:", this));
    dateLayout->addWidget(m_dateFromEdit);
    dateLayout->addWidget(new QLabel("По:", this));
    dateLayout->addWidget(m_dateToEdit);
    
    toolbar->addWidget(dateWidget);

    // Кнопки управления
    m_generateButton = new QPushButton("Сгенерировать", this);
    m_generateButton->setMinimumWidth(120);
    m_exportButton = new QPushButton("Экспорт в CSV", this);
    m_exportButton->setMinimumWidth(120);
    m_printButton = new QPushButton("Печать", this);
    m_printButton->setMinimumWidth(120);
    
    toolbar->addWidget(m_generateButton);
    toolbar->addWidget(m_exportButton);
    toolbar->addWidget(m_printButton);
    
    mainLayout->addLayout(toolbar);

    // Основная область с таблицей и сводкой
    QHBoxLayout *contentLayout = new QHBoxLayout();
    contentLayout->setSpacing(10);
    
    // Таблица отчета
    m_reportTable = new QTableWidget(this);
    m_reportTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_reportTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_reportTable->setAlternatingRowColors(true);
    m_reportTable->setSortingEnabled(true);
    m_reportTable->horizontalHeader()->setStretchLastSection(true);
    m_reportTable->setMinimumWidth(600);
    
    contentLayout->addWidget(m_reportTable, 3); // 3 части из 4

    // Панель сводки (справа)
    QVBoxLayout *summaryLayout = new QVBoxLayout();
    summaryLayout->setSpacing(5);
    
    QLabel *summaryLabel = new QLabel("Сводка отчета", this);
    summaryLabel->setAlignment(Qt::AlignCenter);
    summaryLabel->setStyleSheet("font-weight: bold; font-size: 12pt;");
    summaryLayout->addWidget(summaryLabel);
    
    m_summaryTree = new QTreeWidget(this);
    m_summaryTree->setHeaderLabel("Параметры");
    m_summaryTree->setMaximumWidth(350);
    m_summaryTree->setColumnCount(2);
    m_summaryTree->setHeaderLabels(QStringList() << "Параметр" << "Значение");
    summaryLayout->addWidget(m_summaryTree);
    
    contentLayout->addLayout(summaryLayout, 1); // 1 часть из 4
    
    mainLayout->addLayout(contentLayout, 1);

    // Подключение сигналов
    connect(m_reportTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), 
            this, &ReportsWidget::onReportTypeChanged);
    connect(m_generateButton, &QPushButton::clicked, 
            this, &ReportsWidget::onGenerateReport);
    connect(m_exportButton, &QPushButton::clicked, 
            this, &ReportsWidget::onExportReport);
    connect(m_printButton, &QPushButton::clicked, 
            this, &ReportsWidget::onPrintReport);
    
    connect(m_dateFromEdit, &QDateEdit::dateChanged, 
            this, &ReportsWidget::onDateRangeChanged);
    connect(m_dateToEdit, &QDateEdit::dateChanged, 
            this, &ReportsWidget::onDateRangeChanged);

    // Начальное состояние
    m_exportButton->setEnabled(false);
    m_printButton->setEnabled(false);
    
    onReportTypeChanged(0); // Загружаем отчет по умолчанию
}

void ReportsWidget::refresh() { 
    onGenerateReport(); 
}

void ReportsWidget::onReportTypeChanged(int index) {
    // Управление видимостью элементов дат
    bool showDates = (index == 1); // Только для отчета "Движение товаров"
    m_dateFromEdit->setVisible(showDates);
    m_dateToEdit->setVisible(showDates);
    
    // Очищаем предыдущие данные
    m_reportTable->clear();
    m_summaryTree->clear();
    
    // Обновляем кнопки
    m_exportButton->setEnabled(false);
    m_printButton->setEnabled(false);
    
    // Автоматическая генерация отчета при смене типа (опционально)
    if (m_reportTypeCombo->currentIndex() != 1) { // Если не отчет по движению
        onGenerateReport();
    }
}

void ReportsWidget::onDateRangeChanged() {
    // Автоматическое обновление отчета при изменении дат
    if (m_reportTypeCombo->currentIndex() == 1) { // Только для движения товаров
        onGenerateReport();
    }
}

void ReportsWidget::onGenerateReport() {
    try {
        int reportType = m_reportTypeCombo->currentIndex();
        
        switch (reportType) {
        case 0: 
            generateInventoryReport(); 
            break;
        case 1: 
            generateMovementReport(); 
            break;
        case 2: 
            generateLowStockReport(); 
            break;
        case 3: 
            generateContainerReport(); 
            break;
        default:
            QMessageBox::warning(this, "Ошибка", "Неизвестный тип отчета");
            return;
        }
        
        updateSummary();
        m_exportButton->setEnabled(m_reportTable->rowCount() > 0);
        m_printButton->setEnabled(m_reportTable->rowCount() > 0);
        
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка генерации отчета", 
                            QString("Не удалось сгенерировать отчет: %1").arg(e.what()));
    }
}

void ReportsWidget::generateInventoryReport() {
    // Очистка и настройка таблицы
    m_reportTable->clear();
    m_reportTable->setColumnCount(7);
    m_reportTable->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Название" << "Категория" << "Кол-во" 
                      << "Ед. изм." << "Цена за ед." << "Общая стоимость");
    
    // Получение данных из БД
    QSqlQuery query = DatabaseManager::instance().getAllProducts();
    if (!query.isActive()) {
        throw std::runtime_error("Не удалось получить данные о товарах");
    }
    
    int row = 0;
    double totalValue = 0.0;
    int totalItems = 0;
    
    // Заполнение таблицы
    while (query.next()) {
        m_reportTable->insertRow(row);
        
        int id = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString category = query.value("category").toString();
        int quantity = query.value("quantity").toInt();
        QString unit = query.value("unit").toString();
        double price = query.value("price").toDouble();
        double itemTotal = quantity * price;
        
        totalValue += itemTotal;
        totalItems += quantity;
        
        // Заполнение ячеек
        m_reportTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        m_reportTable->setItem(row, 1, new QTableWidgetItem(name));
        m_reportTable->setItem(row, 2, new QTableWidgetItem(category));
        m_reportTable->setItem(row, 3, new QTableWidgetItem(QString::number(quantity)));
        m_reportTable->setItem(row, 4, new QTableWidgetItem(unit));
        m_reportTable->setItem(row, 5, new QTableWidgetItem(QString::number(price, 'f', 2)));
        m_reportTable->setItem(row, 6, new QTableWidgetItem(QString::number(itemTotal, 'f', 2)));
        
        // Цветовое выделение товаров с нулевым остатком
        if (quantity == 0) {
            for (int col = 0; col < m_reportTable->columnCount(); ++col) {
                QTableWidgetItem *item = m_reportTable->item(row, col);
                if (item) item->setBackground(QColor(255, 200, 200));
            }
        }
        
        row++;
    }
    
    // Добавление итоговой строки
    if (row > 0) {
        m_reportTable->insertRow(row);
        QTableWidgetItem *totalLabel = new QTableWidgetItem("ИТОГО:");
        totalLabel->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 1, totalLabel);
        
        QTableWidgetItem *totalQty = new QTableWidgetItem(QString::number(totalItems));
        totalQty->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 3, totalQty);
        
        QTableWidgetItem *totalVal = new QTableWidgetItem(QString::number(totalValue, 'f', 2));
        totalVal->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 6, totalVal);
        
        // Заливка итоговой строки
        for (int col = 0; col < m_reportTable->columnCount(); ++col) {
            QTableWidgetItem *item = m_reportTable->item(row, col);
            if (item) item->setBackground(QColor(200, 230, 255));
        }
    }
    
    m_reportTable->resizeColumnsToContents();
}

void ReportsWidget::generateMovementReport() {
    // Очистка и настройка таблицы
    m_reportTable->clear();
    m_reportTable->setColumnCount(7);
    m_reportTable->setHorizontalHeaderLabels(
        QStringList() << "Дата" << "Время" << "Товар" << "Тип операции" 
                      << "Изменение" << "Пользователь" << "Комментарий");
    
    // Получение данных за выбранный период
    QDate fromDate = m_dateFromEdit->date();
    QDate toDate = m_dateToEdit->date();
    
    // Проверка корректности диапазона дат
    if (fromDate > toDate) {
        QMessageBox::warning(this, "Ошибка", "Дата 'С' не может быть позже даты 'По'");
        return;
    }
    
    QSqlQuery query;
    query.prepare(
        "SELECT mh.*, p.name AS product_name, u.username, "
        "DATE(mh.created_at) as date_only, TIME(mh.created_at) as time_only "
        "FROM movement_history mh "
        "LEFT JOIN products p ON mh.product_id = p.id "
        "LEFT JOIN users u ON mh.user_id = u.id "
        "WHERE DATE(mh.created_at) BETWEEN ? AND ? "
        "ORDER BY mh.created_at DESC"
    );
    
    query.addBindValue(fromDate.toString("yyyy-MM-dd"));
    query.addBindValue(toDate.toString("yyyy-MM-dd"));
    
    if (!query.exec()) {
        throw std::runtime_error("Не удалось получить данные о движении товаров");
    }
    
    int row = 0;
    int totalIncoming = 0;
    int totalOutgoing = 0;
    
    // Заполнение таблицы
    while (query.next()) {
        m_reportTable->insertRow(row);
        
        QDateTime dateTime = query.value("created_at").toDateTime();
        QString productName = query.value("product_name").toString();
        QString movementType = query.value("movement_type").toString();
        int quantityChange = query.value("quantity_change").toInt();
        QString username = query.value("username").toString();
        QString notes = query.value("notes").toString();
        
        // Суммирование приходов/расходов
        if (movementType == "incoming") {
            totalIncoming += quantityChange;
        } else if (movementType == "outgoing") {
            totalOutgoing += quantityChange;
        }
        
        // Перевод типа операции
        QString typeDisplay;
        QColor typeColor;
        if (movementType == "incoming") {
            typeDisplay = "Приход";
            typeColor = QColor(200, 255, 200); // Зеленый
        } else {
            typeDisplay = "Расход";
            typeColor = QColor(255, 200, 200); // Красный
        }
        
        // Заполнение ячеек
        m_reportTable->setItem(row, 0, new QTableWidgetItem(dateTime.toString("dd.MM.yyyy")));
        m_reportTable->setItem(row, 1, new QTableWidgetItem(dateTime.toString("hh:mm")));
        m_reportTable->setItem(row, 2, new QTableWidgetItem(productName));
        
        QTableWidgetItem *typeItem = new QTableWidgetItem(typeDisplay);
        typeItem->setBackground(typeColor);
        m_reportTable->setItem(row, 3, typeItem);
        
        QTableWidgetItem *qtyItem = new QTableWidgetItem(
            QString("%1%2").arg(movementType == "incoming" ? "+" : "-")
                         .arg(quantityChange)
        );
        qtyItem->setForeground(movementType == "incoming" ? Qt::darkGreen : Qt::darkRed);
        m_reportTable->setItem(row, 4, qtyItem);
        
        m_reportTable->setItem(row, 5, new QTableWidgetItem(username));
        m_reportTable->setItem(row, 6, new QTableWidgetItem(notes));
        
        row++;
    }
    
    // Добавление итоговой строки
    if (row > 0) {
        m_reportTable->insertRow(row);
        
        QTableWidgetItem *totalLabel = new QTableWidgetItem("ИТОГО ЗА ПЕРИОД:");
        totalLabel->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 1, totalLabel);
        
        QTableWidgetItem *incomingItem = new QTableWidgetItem(QString("+%1").arg(totalIncoming));
        incomingItem->setFont(QFont("Arial", 10, QFont::Bold));
        incomingItem->setForeground(Qt::darkGreen);
        m_reportTable->setItem(row, 3, new QTableWidgetItem("Приход:"));
        m_reportTable->setItem(row, 4, incomingItem);
        
        m_reportTable->insertRow(row + 1);
        QTableWidgetItem *outgoingItem = new QTableWidgetItem(QString("-%1").arg(totalOutgoing));
        outgoingItem->setFont(QFont("Arial", 10, QFont::Bold));
        outgoingItem->setForeground(Qt::darkRed);
        m_reportTable->setItem(row + 1, 3, new QTableWidgetItem("Расход:"));
        m_reportTable->setItem(row + 1, 4, outgoingItem);
        
        m_reportTable->insertRow(row + 2);
        int netChange = totalIncoming - totalOutgoing;
        QTableWidgetItem *netItem = new QTableWidgetItem(
            QString("%1%2").arg(netChange >= 0 ? "+" : "").arg(netChange)
        );
        netItem->setFont(QFont("Arial", 10, QFont::Bold));
        netItem->setForeground(netChange >= 0 ? Qt::darkGreen : Qt::darkRed);
        m_reportTable->setItem(row + 2, 3, new QTableWidgetItem("Чистое изменение:"));
        m_reportTable->setItem(row + 2, 4, netItem);
    }
    
    m_reportTable->resizeColumnsToContents();
}

void ReportsWidget::generateLowStockReport() {
    // Очистка и настройка таблицы
    m_reportTable->clear();
    m_reportTable->setColumnCount(7);
    m_reportTable->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Название" << "Текущий" << "Минимальный" 
                      << "Ед. изм." << "Локация" << "Статус");
    
    QSqlQuery query = DatabaseManager::instance().getAllProducts();
    if (!query.isActive()) {
        throw std::runtime_error("Не удалось получить данные о товарах");
    }
    
    int row = 0;
    int criticalCount = 0;
    int warningCount = 0;
    
    while (query.next()) {
        int currentQty = query.value("quantity").toInt();
        int minQty = query.value("min_quantity").toInt();
        
        // Пропускаем товары без минимального количества
        if (minQty <= 0) continue;
        
        // Определяем статус
        QString status;
        QColor statusColor;
        
        if (currentQty == 0) {
            status = "НЕТ В НАЛИЧИИ";
            statusColor = QColor(255, 150, 150); // Красный
            criticalCount++;
        } else if (currentQty <= minQty * 0.3) {
            status = "КРИТИЧЕСКИЙ";
            statusColor = QColor(255, 200, 150); // Оранжевый
            criticalCount++;
        } else if (currentQty <= minQty) {
            status = "НИЗКИЙ";
            statusColor = QColor(255, 255, 150); // Желтый
            warningCount++;
        } else {
            continue; // Не показываем товары с достаточным запасом
        }
        
        m_reportTable->insertRow(row);
        
        // Заполнение ячеек
        m_reportTable->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        m_reportTable->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        m_reportTable->setItem(row, 2, new QTableWidgetItem(QString::number(currentQty)));
        m_reportTable->setItem(row, 3, new QTableWidgetItem(QString::number(minQty)));
        m_reportTable->setItem(row, 4, new QTableWidgetItem(query.value("unit").toString()));
        m_reportTable->setItem(row, 5, new QTableWidgetItem(query.value("location").toString()));
        
        QTableWidgetItem *statusItem = new QTableWidgetItem(status);
        statusItem->setBackground(statusColor);
        statusItem->setFont(QFont("Arial", 9, QFont::Bold));
        m_reportTable->setItem(row, 6, statusItem);
        
        row++;
    }
    
    // Статистика в заголовке
    if (row > 0) {
        m_reportTable->insertRow(row);
        QTableWidgetItem *statsItem = new QTableWidgetItem(
            QString("Найдено %1 товаров: %2 критических, %3 с низким запасом")
                .arg(row).arg(criticalCount).arg(warningCount)
        );
        statsItem->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 1, statsItem);
    }
    
    m_reportTable->resizeColumnsToContents();
}

void ReportsWidget::generateContainerReport() {
    // Очистка и настройка таблицы
    m_reportTable->clear();
    m_reportTable->setColumnCount(5);
    m_reportTable->setHorizontalHeaderLabels(
        QStringList() << "Код" << "Название" << "Вместимость" << "Текущая загрузка" << "Статус");
    
    QSqlQuery query = DatabaseManager::instance().getAllContainers();
    if (!query.isActive()) {
        throw std::runtime_error("Не удалось получить данные о контейнерах");
    }
    
    int row = 0;
    int totalCapacity = 0;
    int totalUsed = 0;
    
    while (query.next()) {
        m_reportTable->insertRow(row);
        
        QString code = query.value("code").toString();
        QString name = query.value("name").toString();
        int capacity = query.value("capacity").toInt();
        int currentLoad = query.value("current_load").toInt(); // Предполагаем, что такое поле есть
        QString status = query.value("status").toString();
        
        totalCapacity += capacity;
        totalUsed += currentLoad;
        
        // Расчет процента заполнения
        int usagePercent = capacity > 0 ? (currentLoad * 100) / capacity : 0;
        
        // Определение цвета статуса
        QString statusDisplay;
        QColor statusColor;
        
        if (status == "free") {
            statusDisplay = "Свободен";
            statusColor = QColor(200, 255, 200);
        } else if (status == "in_use") {
            statusDisplay = "Используется";
            statusColor = QColor(255, 255, 200);
        } else if (status == "full") {
            statusDisplay = "Полный";
            statusColor = QColor(255, 200, 200);
        } else if (status == "maintenance") {
            statusDisplay = "На обслуживании";
            statusColor = QColor(200, 200, 255);
        } else {
            statusDisplay = status;
            statusColor = Qt::lightGray;
        }
        
        // Заполнение ячеек
        m_reportTable->setItem(row, 0, new QTableWidgetItem(code));
        m_reportTable->setItem(row, 1, new QTableWidgetItem(name));
        m_reportTable->setItem(row, 2, new QTableWidgetItem(QString::number(capacity)));
        m_reportTable->setItem(row, 3, new QTableWidgetItem(
            QString("%1/%2 (%3%)").arg(currentLoad).arg(capacity).arg(usagePercent)
        ));
        
        QTableWidgetItem *statusItem = new QTableWidgetItem(statusDisplay);
        statusItem->setBackground(statusColor);
        m_reportTable->setItem(row, 4, statusItem);
        
        row++;
    }
    
    // Итоговая строка
    if (row > 0) {
        m_reportTable->insertRow(row);
        
        int totalUsagePercent = totalCapacity > 0 ? (totalUsed * 100) / totalCapacity : 0;
        
        QTableWidgetItem *totalLabel = new QTableWidgetItem("ИТОГО:");
        totalLabel->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 1, totalLabel);
        
        QTableWidgetItem *capacityItem = new QTableWidgetItem(QString::number(totalCapacity));
        capacityItem->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 2, capacityItem);
        
        QTableWidgetItem *usageItem = new QTableWidgetItem(
            QString("%1/%2 (%3%)").arg(totalUsed).arg(totalCapacity).arg(totalUsagePercent)
        );
        usageItem->setFont(QFont("Arial", 10, QFont::Bold));
        m_reportTable->setItem(row, 3, usageItem);
    }
    
    m_reportTable->resizeColumnsToContents();
}

void ReportsWidget::updateSummary() {
    m_summaryTree->clear();
    
    QTreeWidgetItem *reportInfo = new QTreeWidgetItem(m_summaryTree);
    reportInfo->setText(0, "Информация об отчете");
    
    // Общая информация
    new QTreeWidgetItem(reportInfo, QStringList() << "Тип отчета" << m_reportTypeCombo->currentText());
    new QTreeWidgetItem(reportInfo, QStringList() << "Дата генерации" << QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"));
    
    if (m_reportTypeCombo->currentIndex() == 1) { // Для отчета по движению
        new QTreeWidgetItem(reportInfo, QStringList() << "Период с" << m_dateFromEdit->date().toString("dd.MM.yyyy"));
        new QTreeWidgetItem(reportInfo, QStringList() << "Период по" << m_dateToEdit->date().toString("dd.MM.yyyy"));
    }
    
    new QTreeWidgetItem(reportInfo, QStringList() << "Всего записей" << QString::number(m_reportTable->rowCount()));
    
    // Статистика в зависимости от типа отчета
    QTreeWidgetItem *stats = new QTreeWidgetItem(m_summaryTree);
    stats->setText(0, "Статистика");
    
    switch (m_reportTypeCombo->currentIndex()) {
    case 0: { // Инвентаризация
        double totalValue = 0;
        int totalItems = 0;
        
        for (int row = 0; row < m_reportTable->rowCount() - 1; ++row) { // Исключаем итоговую строку
            QTableWidgetItem *qtyItem = m_reportTable->item(row, 3);
            QTableWidgetItem *valueItem = m_reportTable->item(row, 6);
            
            if (qtyItem && valueItem) {
                totalItems += qtyItem->text().toInt();
                totalValue += valueItem->text().toDouble();
            }
        }
        
        new QTreeWidgetItem(stats, QStringList() << "Общее количество" << QString::number(totalItems));
        new QTreeWidgetItem(stats, QStringList() << "Общая стоимость" << QString::number(totalValue, 'f', 2) + " ₽");
        break;
    }
    case 1: { // Движение товаров
        int incoming = 0, outgoing = 0;
        
        for (int row = 0; row < m_reportTable->rowCount(); ++row) {
            QTableWidgetItem *typeItem = m_reportTable->item(row, 3);
            QTableWidgetItem *qtyItem = m_reportTable->item(row, 4);
            
            if (typeItem && qtyItem) {
                QString qtyText = qtyItem->text();
                if (!qtyText.isEmpty()) {
                    if (typeItem->text() == "Приход") {
                        incoming += qtyText.toInt();
                    } else if (typeItem->text() == "Расход") {
                        outgoing += qtyText.toInt();
                    }
                }
            }
        }
        
        new QTreeWidgetItem(stats, QStringList() << "Приход" << QString::number(incoming));
        new QTreeWidgetItem(stats, QStringList() << "Расход" << QString::number(outgoing));
        new QTreeWidgetItem(stats, QStringList() << "Чистое изменение" << QString::number(incoming - outgoing));
        break;
    }
    case 2: { // Низкий запас
        int critical = 0, low = 0;
        
        for (int row = 0; row < m_reportTable->rowCount(); ++row) {
            QTableWidgetItem *statusItem = m_reportTable->item(row, 6);
            if (statusItem) {
                if (statusItem->text().contains("КРИТИЧЕСКИЙ") || statusItem->text().contains("НЕТ В НАЛИЧИИ")) {
                    critical++;
                } else if (statusItem->text().contains("НИЗКИЙ")) {
                    low++;
                }
            }
        }
        
        new QTreeWidgetItem(stats, QStringList() << "Критический уровень" << QString::number(critical));
        new QTreeWidgetItem(stats, QStringList() << "Низкий уровень" << QString::number(low));
        break;
    }
    case 3: { // Контейнеры
        int free = 0, inUse = 0, full = 0;
        
        for (int row = 0; row < m_reportTable->rowCount(); ++row) {
            QTableWidgetItem *statusItem = m_reportTable->item(row, 4);
            if (statusItem) {
                if (statusItem->text().contains("Свободен")) free++;
                else if (statusItem->text().contains("Используется")) inUse++;
                else if (statusItem->text().contains("Полный")) full++;
            }
        }
        
        new QTreeWidgetItem(stats, QStringList() << "Свободные" << QString::number(free));
        new QTreeWidgetItem(stats, QStringList() << "Используются" << QString::number(inUse));
        new QTreeWidgetItem(stats, QStringList() << "Полные" << QString::number(full));
        break;
    }
    }
    
    // Информация о пользователе
    QTreeWidgetItem *userInfo = new QTreeWidgetItem(m_summaryTree);
    userInfo->setText(0, "Пользователь");
    new QTreeWidgetItem(userInfo, QStringList() << "Имя" << m_currentUser.username());
    new QTreeWidgetItem(userInfo, QStringList() << "Роль" << m_currentUser.roleString());
    
    m_summaryTree->expandAll();
}

void ReportsWidget::onExportReport() {
    if (m_reportTable->rowCount() == 0) {
        QMessageBox::warning(this, "Экспорт", "Нет данных для экспорта");
        return;
    }
    
    QString fileName = QFileDialog::getSaveFileName(
        this, 
        "Экспорт отчета", 
        QString("Отчет_%1_%2.csv").arg(m_reportTypeCombo->currentText())
                                   .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmm")),
        "CSV файлы (*.csv);;Все файлы (*.*)"
    );
    
    if (fileName.isEmpty()) return;
    
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Ошибка", 
                            QString("Не удалось открыть файл для записи:\n%1").arg(file.errorString()));
        return;
    }
    
    QTextStream out(&file);
    out.setCodec("UTF-8");
    
    // Заголовок отчета
    out << "\"" << m_reportTypeCombo->currentText() << "\"\n";
    out << "\"Сгенерирован: " << QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm") << "\"\n";
    out << "\"Пользователь: " << m_currentUser.username() << "\"\n\n";
    
    // Заголовки столбцов
    for (int col = 0; col < m_reportTable->columnCount(); ++col) {
        if (col > 0) out << ";";
        out << "\"" << m_reportTable->horizontalHeaderItem(col)->text() << "\"";
    }
    out << "\n";
    
    // Данные
    for (int row = 0; row < m_reportTable->rowCount(); ++row) {
        for (int col = 0; col < m_reportTable->columnCount(); ++col) {
            if (col > 0) out << ";";
            QTableWidgetItem *item = m_reportTable->item(row, col);
            QString text = item ? item->text() : "";
            // Экранирование кавычек для CSV
            text.replace("\"", "\"\"");
            out << "\"" << text << "\"";
        }
        out << "\n";
    }
    
    file.close();
    QMessageBox::information(this, "Экспорт", 
                           QString("Отчет успешно экспортирован в файл:\n%1").arg(fileName));
}

void ReportsWidget::onPrintReport() {
    if (m_reportTable->rowCount() == 0) {
        QMessageBox::warning(this, "Печать", "Нет данных для печати");
        return;
    }
    
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageOrientation(QPageLayout::Landscape);
    
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() != QDialog::Accepted) {
        return;
    }
    
    QPainter painter(&printer);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Параметры страницы
    QRect pageRect = printer.pageRect(QPrinter::DevicePixel);
    int pageWidth = pageRect.width();
    int pageHeight = pageRect.height();
    
    QFont headerFont("Arial", 14, QFont::Bold);
    QFont titleFont("Arial", 12, QFont::Bold);
    QFont normalFont("Arial", 10);
    QFont smallFont("Arial", 8);
    
    int yPos = 50;
    
    // Заголовок отчета
    painter.setFont(headerFont);
    painter.drawText(0, yPos, pageWidth, 30, Qt::AlignCenter, m_reportTypeCombo->currentText());
    yPos += 40;
    
    // Информация об отчете
    painter.setFont(smallFont);
    QString reportInfo = QString("Сгенерирован: %1 | Пользователь: %2")
                        .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm"))
                        .arg(m_currentUser.username());
    
    if (m_reportTypeCombo->currentIndex() == 1) {
        reportInfo += QString(" | Период: %1 - %2")
                     .arg(m_dateFromEdit->date().toString("dd.MM.yyyy"))
                     .arg(m_dateToEdit->date().toString("dd.MM.yyyy"));
    }
    
    painter.drawText(0, yPos, pageWidth, 20, Qt::AlignCenter, reportInfo);
    yPos += 30;
    
    // Расчет ширины столбцов
    int colCount = m_reportTable->columnCount();
    int rowCount = m_reportTable->rowCount();
    
    if (colCount == 0) return;
    
    int colWidth = pageWidth / colCount;
    int rowHeight = 30;
    
    // Заголовки столбцов
    painter.setFont(titleFont);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(QColor(230, 230, 230)));
    
    for (int col = 0; col < colCount; ++col) {
        QRect headerRect(col * colWidth, yPos, colWidth, rowHeight);
        painter.drawRect(headerRect);
        painter.drawText(headerRect, Qt::AlignCenter, m_reportTable->horizontalHeaderItem(col)->text());
    }
    yPos += rowHeight;
    
    // Данные таблицы
    painter.setFont(normalFont);
    painter.setBrush(Qt::NoBrush);
    
    for (int row = 0; row < rowCount; ++row) {
        // Проверка на конец страницы
        if (yPos + rowHeight > pageHeight - 50) {
            printer.newPage();
            yPos = 50;
            
            // Повторяем заголовки на новой странице
            painter.setFont(titleFont);
            painter.setBrush(QBrush(QColor(230, 230, 230)));
            for (int col = 0; col < colCount; ++col) {
                QRect headerRect(col * colWidth, yPos, colWidth, rowHeight);
                painter.drawRect(headerRect);
                painter.drawText(headerRect, Qt::AlignCenter, m_reportTable->horizontalHeaderItem(col)->text());
            }
            yPos += rowHeight;
            painter.setFont(normalFont);
            painter.setBrush(Qt::NoBrush);
        }
        
        // Строка данных
        for (int col = 0; col < colCount; ++col) {
            QRect cellRect(col * colWidth, yPos, colWidth, rowHeight);
            painter.drawRect(cellRect);
            
            QTableWidgetItem *item = m_reportTable->item(row, col);
            QString text = item ? item->text() : "";
            
            // Выделение итоговых строк
            if (item && item->font().bold()) {
                painter.setFont(QFont("Arial", 10, QFont::Bold));
                painter.setBrush(QBrush(QColor(240, 240, 240)));
            }
            
            painter.drawText(cellRect.adjusted(5, 0, -5, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
            
            // Восстанавливаем стиль
            if (item && item->font().bold()) {
                painter.setFont(normalFont);
                painter.setBrush(Qt::NoBrush);
            }
        }
        yPos += rowHeight;
    }
    
    painter.end();
    QMessageBox::information(this, "Печать", "Отчет отправлен на печать");
}