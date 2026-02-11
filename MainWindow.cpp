#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "widgets/WarehouseWidget.h"
#include "widgets/ReportsWidget.h"
#include "widgets/RequestsWidget.h"
#include "gui/RegistrationDialog.h"
#include "database/DatabaseManager.h"

#include <QStatusBar>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QDateTime>
#include <QIcon>

MainWindow::MainWindow(const User& user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_currentUser(user)
    , m_warehouseWidget(nullptr)
    , m_reportsWidget(nullptr)
    , m_requestsWidget(nullptr)
{
    ui->setupUi(this);
    
    setWindowTitle("Складская система HK - " + user.fullName());
    
    setupUi();
    setupMenuBar();
    setupToolBar();
    setupConnections();
    applyUserPermissions();
    
    statusBar()->showMessage(QString("Пользователь: %1 (%2) | %3")
        .arg(user.fullName())
        .arg(user.role())
        .arg(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUi()
{
    // Создаем виджеты
    m_warehouseWidget = new WarehouseWidget(m_currentUser, this);
    m_reportsWidget = new ReportsWidget(m_currentUser, this);
    m_requestsWidget = new RequestsWidget(m_currentUser, this);
    
    // Добавляем виджеты в stacked widget
    ui->stackedWidget->addWidget(m_warehouseWidget);
    ui->stackedWidget->addWidget(m_reportsWidget);
    ui->stackedWidget->addWidget(m_requestsWidget);
    
    // Показываем виджет склада по умолчанию
    ui->stackedWidget->setCurrentWidget(m_warehouseWidget);
    
    // Устанавливаем иконку
    setWindowIcon(QIcon(":/icons/warehouse.png"));
}

void MainWindow::setupMenuBar()
{
    // Меню Файл
    QMenu *fileMenu = menuBar()->addMenu("&Файл");
    
    QAction *exportAction = new QAction("Экспорт данных", this);
    exportAction->setShortcut(QKeySequence::Save);
    connect(exportAction, &QAction::triggered, this, [this]() {
        m_warehouseWidget->onExportDataClicked();
    });
    fileMenu->addAction(exportAction);
    
    fileMenu->addSeparator();
    
    QAction *exitAction = new QAction("Выход", this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitButtonClicked);
    fileMenu->addAction(exitAction);
    
    // Меню Правка
    QMenu *editMenu = menuBar()->addMenu("&Правка");
    
    QAction *addProductAction = new QAction("Добавить товар", this);
    addProductAction->setShortcut(QKeySequence::New);
    connect(addProductAction, &QAction::triggered, m_warehouseWidget, &WarehouseWidget::onAddProductClicked);
    editMenu->addAction(addProductAction);
    
    QAction *refreshAction = new QAction("Обновить", this);
    refreshAction->setShortcut(QKeySequence::Refresh);
    connect(refreshAction, &QAction::triggered, this, [this]() {
        QWidget *current = ui->stackedWidget->currentWidget();
        if (current == m_warehouseWidget) {
            m_warehouseWidget->refreshData();
        } else if (current == m_reportsWidget) {
            m_reportsWidget->refresh();
        } else if (current == m_requestsWidget) {
            m_requestsWidget->refresh();
        }
    });
    editMenu->addAction(refreshAction);
    
    // Меню Вид
    QMenu *viewMenu = menuBar()->addMenu("&Вид");
    
    QAction *warehouseAction = new QAction("Склад", this);
    connect(warehouseAction, &QAction::triggered, this, &MainWindow::onWarehouseButtonClicked);
    viewMenu->addAction(warehouseAction);
    
    QAction *requestsAction = new QAction("Заявки", this);
    connect(requestsAction, &QAction::triggered, this, &MainWindow::onRequestsButtonClicked);
    viewMenu->addAction(requestsAction);
    
    QAction *reportsAction = new QAction("Отчеты", this);
    connect(reportsAction, &QAction::triggered, this, &MainWindow::onReportsButtonClicked);
    viewMenu->addAction(reportsAction);
    
    // Меню Помощь
    QMenu *helpMenu = menuBar()->addMenu("&Помощь");
    
    QAction *aboutAction = new QAction("О программе", this);
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "О программе",
            "<h3>Складская система HK v2.0</h3>"
            "<p>Система управления складом с поддержкой QR-кодов</p>"
            "<p>Разработчик: WarehouseHK Team</p>"
            "<p>© 2024 Все права защищены</p>");
    });
    helpMenu->addAction(aboutAction);
}

void MainWindow::setupToolBar()
{
    QToolBar *mainToolBar = addToolBar("Основные функции");
    mainToolBar->setMovable(false);
    
    // Кнопка Склад
    QAction *warehouseAction = new QAction("📦 Склад", this);
    warehouseAction->setToolTip("Управление товарами и контейнерами");
    connect(warehouseAction, &QAction::triggered, this, &MainWindow::onWarehouseButtonClicked);
    mainToolBar->addAction(warehouseAction);
    
    // Кнопка Заявки
    QAction *requestsAction = new QAction("📋 Заявки", this);
    requestsAction->setToolTip("Управление заявками на перемещение");
    connect(requestsAction, &QAction::triggered, this, &MainWindow::onRequestsButtonClicked);
    mainToolBar->addAction(requestsAction);
    
    // Кнопка Отчеты
    QAction *reportsAction = new QAction("📊 Отчеты", this);
    reportsAction->setToolTip("Просмотр отчетов и аналитика");
    connect(reportsAction, &QAction::triggered, this, &MainWindow::onReportsButtonClicked);
    mainToolBar->addAction(reportsAction);
    
    mainToolBar->addSeparator();
    
    // Кнопка Пользователи (только для админа)
    if (m_currentUser.isAdmin()) {
        QAction *usersAction = new QAction("👥 Пользователи", this);
        usersAction->setToolTip("Управление пользователями системы");
        connect(usersAction, &QAction::triggered, this, &MainWindow::onUsersButtonClicked);
        mainToolBar->addAction(usersAction);
    }
    
    mainToolBar->addSeparator();
    
    // Кнопка Настройки
    QAction *settingsAction = new QAction("⚙️ Настройки", this);
    connect(settingsAction, &QAction::triggered, this, &MainWindow::onSettingsButtonClicked);
    mainToolBar->addAction(settingsAction);
    
    // Кнопка Выход
    QAction *exitAction = new QAction("🚪 Выход", this);
    exitAction->setToolTip("Выйти из системы");
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExitButtonClicked);
    mainToolBar->addAction(exitAction);
}

void MainWindow::setupConnections()
{
    connect(ui->warehouseButton, &QPushButton::clicked, this, &MainWindow::onWarehouseButtonClicked);
    connect(ui->reportsButton, &QPushButton::clicked, this, &MainWindow::onReportsButtonClicked);
    connect(ui->requestsButton, &QPushButton::clicked, this, &MainWindow::onRequestsButtonClicked);
    connect(ui->usersButton, &QPushButton::clicked, this, &MainWindow::onUsersButtonClicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsButtonClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::onExitButtonClicked);
}

void MainWindow::applyUserPermissions()
{
    QString role = m_currentUser.role();
    
    // Применяем ограничения
    if (role == "worker") {
        ui->usersButton->setEnabled(false);
        QList<QAction*> actions = findChildren<QAction*>();
        for (QAction* action : actions) {
            if (action->text().contains("Пользователи")) {
                action->setEnabled(false);
            }
        }
    }
}

void MainWindow::onWarehouseButtonClicked()
{
    ui->stackedWidget->setCurrentWidget(m_warehouseWidget);
    statusBar()->showMessage("Режим: Управление складом");
}

void MainWindow::onReportsButtonClicked()
{
    ui->stackedWidget->setCurrentWidget(m_reportsWidget);
    statusBar()->showMessage("Режим: Отчеты и аналитика");
}

void MainWindow::onRequestsButtonClicked()
{
    ui->stackedWidget->setCurrentWidget(m_requestsWidget);
    statusBar()->showMessage("Режим: Управление заявками");
}

void MainWindow::onUsersButtonClicked()
{
    RegistrationDialog dialog(this);
    dialog.setWindowTitle("Управление пользователями");
    
    if (dialog.exec() == QDialog::Accepted) {
        statusBar()->showMessage("Пользователи обновлены", 3000);
    }
}

void MainWindow::onSettingsButtonClicked()
{
    QMessageBox::information(this, "Настройки", 
        "Настройки системы будут доступны в следующей версии.");
}

void MainWindow::onExitButtonClicked()
{
    if (QMessageBox::question(this, "Подтверждение", 
        "Вы действительно хотите выйти из системы?",
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        close();
    }
}